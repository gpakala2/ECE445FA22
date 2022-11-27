#include "common/xf_headers.hpp"
#include "xf_stitch_config.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: <executable> <input image path>\n");
        return -1;
    }

    cv::Mat in_img1, in_img2, in_img3, key1_img, key2_img, key3_img;
    cv::Mat descriptors1, descriptors2, descriptors3;

    vector<cv::KeyPoint> keypoints1, keypoints2, keypoints3;

    in_img1 = cv::imread(argv[1], 0); // reading in gray image
    in_img2 = cv::imread(argv[2], 0);
    in_img3 = cv::imread(argv[3], 0);

    if (!in_img1.data || !in_img2.data || !in_img3.data) {
        fprintf(stderr, "Failed to load the image ... !!!\n ");
        return -1;
    }

    key1_img.create(in_img1.rows, in_img1.cols, CV_8UC1); //allocate memory for output gray image of fast accel
    key2_img.create(in_img1.rows, in_img1.cols, CV_8UC1); //allocate memory for output gray image of fast accel
    key3_img.create(in_img1.rows, in_img1.cols, CV_8UC1);

    int height = in_img1.rows;
    int width = in_img1.cols;
    unsigned char threshold = 110;

    printf("\ntest point 0\n");

    // Call the top function
    fast_accel((ap_uint<INPUT_PTR_WIDTH>*)in_img1.data, threshold, (ap_uint<OUTPUT_PTR_WIDTH>*)key1_img.data, height, width);
    fast_accel((ap_uint<INPUT_PTR_WIDTH>*)in_img2.data, threshold, (ap_uint<OUTPUT_PTR_WIDTH>*)key2_img.data, height, width);
    fast_accel((ap_uint<INPUT_PTR_WIDTH>*)in_img3.data, threshold, (ap_uint<OUTPUT_PTR_WIDTH>*)key3_img.data, height, width);

    printf("test point 0.1\n");

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
            int value3 = (int) key3_img.at<uchar>(i, j); 
            if (value2==255){
                cv::KeyPoint key(j, i, 1); 
                keypoints3.push_back(key);
            }
        }
    }

    // key1_img.deallocate();
    // key2_img.deallocate();

    cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
    extractor->compute(in_img1, keypoints1, descriptors1);
    extractor->compute(in_img2, keypoints2, descriptors2);
    extractor->compute(in_img3, keypoints3, descriptors3);

    int nkp1 = descriptors1.rows;
    int nkp2 = descriptors2.rows;
    int16_t tmp_good_matches[nkp1];

    printf("\n size: %d\n", nkp1);

    // bfmatcher_accel((ap_uint<INPUT_PTR_WIDTH>*)descriptors1.data, (ap_uint<INPUT_PTR_WIDTH>*)descriptors2.data,
    //                 (ap_int<BF_OUTPUT_PTR_WIDTH>*)tmp_good_matches, nkp1, nkp2, 0.7f);
	
    vector<cv::DMatch> good_matches_l, good_matches_r;
    cv::BFMatcher matcher = cv::BFMatcher(cv::NORM_L2, true);
    matcher.match(descriptors2, descriptors1, good_matches_l);
    matcher.match(descriptors2, descriptors3, good_matches_r);	
    	
    // descriptors1.deallocate();
    // descriptors2.deallocate();

//     vector<cv::DMatch> good_matches;

//     int rev_matches = 0;
//     for (int i = 0; i < nkp1; i++) {
//         if ((int)tmp_good_matches[i] >= 0) rev_matches++;
//     }

//     good_matches.resize(rev_matches);
//     rev_matches = 0;
//     for (int i = 0; i < nkp1; i++) {
//         if ((int)tmp_good_matches[i] >= 0) {
//             good_matches[rev_matches].queryIdx = i;
//             good_matches[rev_matches].trainIdx = (int)tmp_good_matches[i];
//             rev_matches++;
//         }
//     }

    // cv::drawMatches(in_img1, keypoints1, in_img2, keypoints2, good_matches, ocv_ref, cv::Scalar::all(-1),
    //                 cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    vector< cv::Point2f > src_l, dest_l, src_r, dest_r;
    cv::Mat H_l, H_r;

    for (int i = 0; i < good_matches_l.size(); i++){
		src_l.push_back(keypoints2[good_matches_l[i].queryIdx].pt);
		dest_l.push_back(keypoints1[good_matches_l[i].trainIdx].pt);
	}

    for (int i = 0; i < good_matches_r.size(); i++){
		src_r.push_back(keypoints2[good_matches_r[i].queryIdx].pt);
		dest_r.push_back(keypoints3[good_matches_r[i].trainIdx].pt);
	}

    H_l = cv::findHomography(dest_l,src_l,cv::RANSAC, 5.0);
    H_r = cv::findHomography(dest_r,src_r,cv::RANSAC, 5.0);
    double translation[] = { 1, 0, in_img1.cols,
                             0, 1, in_img1.rows,
                             0, 0, 1            };
    cv::Mat translation_matrix(3, 3, CV_64FC1, translation);

    cv::Mat H_fl = translation_matrix * H_l;
    cv::Mat H_fr = translation_matrix * H_r;

    // cout << "M = " << endl << " "  << translation_matrix << endl << endl;
    cv::Mat result(in_img1.rows * 3, in_img1.cols * 3, CV_8UC1);
    cv::Mat result_r(in_img1.rows * 3, in_img1.cols * 3, CV_8UC1); //allocate memory for output gray image of fast accel
    cv::Mat test_l(cv::Size(in_img1.cols * 3, in_img1.rows * 3), CV_8UC1);
    cv::Mat test_r(cv::Size(in_img1.cols * 3, in_img1.rows * 3), CV_8UC1);

    printf("error point 1\n");

    in_img1.copyTo(test_l(cv::Rect(0, 0, in_img1.cols, in_img1.rows)));
    in_img3.copyTo(test_r(cv::Rect(0, 0, in_img1.cols, in_img1.rows)));

    printf("test point 4\n");

	cv::warpPerspective(test_l, result, H_fl, cv::Size(in_img1.cols * 3, in_img1.rows * 3));
    cv::warpPerspective(test_r, result_r, H_fr, cv::Size(in_img1.cols * 3, in_img1.rows * 3));

    printf("test point 5\n");

    result += result_r;
	in_img2.copyTo(result(cv::Rect(in_img1.cols, in_img1.rows, in_img1.cols, in_img1.rows)));

    cv::imwrite("ref.jpg", result);
    
    return 0;
}
