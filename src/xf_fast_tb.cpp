#include "common/xf_headers.hpp"
#include "xf_stitch_config.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: <executable> <input image path>\n");
        return -1;
    }

    cv::Mat in_img1, in_img2, key1_img, key2_img;
    cv::Mat descriptors1, descriptors2;

    vector<cv::KeyPoint> keypoints1, keypoints2;

    in_img1 = cv::imread(argv[1], 0); // reading in gray image
    in_img2 = cv::imread(argv[2], 0);

    if (!in_img1.data || !in_img2.data) {
        fprintf(stderr, "Failed to load the image ... !!!\n ");
        return -1;
    }

    key1_img.create(in_img1.rows, in_img1.cols, CV_8UC1); //allocate memory for output gray image of fast accel
    key2_img.create(in_img1.rows, in_img1.cols, CV_8UC1); //allocate memory for output gray image of fast accel

    int height = in_img1.rows;
    int width = in_img1.cols;
    unsigned char threshold = 110;

    // Call the top function
    fast_accel((ap_uint<INPUT_PTR_WIDTH>*)in_img1.data, threshold, (ap_uint<OUTPUT_PTR_WIDTH>*)key1_img.data, height, width);
    fast_accel((ap_uint<INPUT_PTR_WIDTH>*)in_img2.data, threshold, (ap_uint<OUTPUT_PTR_WIDTH>*)key2_img.data, height, width);

    for(int i = 0 ;i < in_img1.rows; i++){
        for(int j = 0; j< in_img1.cols; j++){
            int value1 = (int) key1_img.at<uchar>(i, j); 
            if(value1==255){
                cv::KeyPoint key(j, i, 1); 
                keypoints1.push_back(key);
            }
            int value2 = (int) key2_img.at<uchar>(i, j); 
            if (value2==255){
                cv::KeyPoint key(j, i, 1); 
                keypoints2.push_back(key);
            }
        }
    }

    // key1_img.deallocate();
    // key2_img.deallocate();

    cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
    extractor->compute(in_img1, keypoints1, descriptors1);
    extractor->compute(in_img2, keypoints2, descriptors2);

    int nkp1 = descriptors1.rows;
    int nkp2 = descriptors2.rows;
    int16_t tmp_good_matches[nkp1];

    printf("\n size: %d\n", nkp1);

    bfmatcher_accel((ap_uint<INPUT_PTR_WIDTH>*)descriptors1.data, (ap_uint<INPUT_PTR_WIDTH>*)descriptors2.data,
                    (ap_int<BF_OUTPUT_PTR_WIDTH>*)tmp_good_matches, nkp1, nkp2, 0.7f);

    // descriptors1.deallocate();
    // descriptors2.deallocate();

    vector<cv::DMatch> good_matches;

    int rev_matches = 0;
    for (int i = 0; i < nkp1; i++) {
        if ((int)tmp_good_matches[i] >= 0) rev_matches++;
    }

    good_matches.resize(rev_matches);
    rev_matches = 0;
    for (int i = 0; i < nkp1; i++) {
        if ((int)tmp_good_matches[i] >= 0) {
            good_matches[rev_matches].queryIdx = i;
            good_matches[rev_matches].trainIdx = (int)tmp_good_matches[i];
            rev_matches++;
        }
    }

    // cv::drawMatches(in_img1, keypoints1, in_img2, keypoints2, good_matches, ocv_ref, cv::Scalar::all(-1),
    //                 cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    vector< cv::Point2f > src, dest;
    cv::Mat H;

    for (int i = 0; i < good_matches.size(); i++){
		src.push_back(keypoints1[good_matches[i].queryIdx].pt);
		dest.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

    H = cv::findHomography(dest,src,cv::RANSAC, 5.0);

    cv::Mat result(in_img1.rows, in_img1.cols + in_img2.cols, CV_8UC1); //allocate memory for output gray image of fast accel

    cv::Mat test(cv::Size(in_img1.cols + in_img1.cols, in_img1.rows), CV_8UC1); 
    in_img2.copyTo(test(cv::Rect(0, 0, in_img1.cols, in_img1.rows)));

	cv::warpPerspective(test, result, H, cv::Size(in_img1.cols + in_img2.cols, in_img1.rows));

	in_img1.copyTo(result(cv::Rect(0, 0, in_img1.cols, in_img1.rows)));

    cv::imwrite("ref.jpg", result);
    
    return 0;
}
