#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/calib3d.hpp>

#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>


#include "ap_int.h"
#include "myled.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
 start_leds(0);

  int imageLoop = 1;
  run_leds_mode(15);
  int status = 0;

  while(1) {
	   vector<KeyPoint> keypoints1, keypoints2, keypoints3;

	   Mat in_image1, in_image2, in_image3;
	   Mat grey_image1, grey_image2, grey_image3;
	   Mat descriptors1, descriptors2, descriptors3;
	   string inFile1 = "";
	   string inFile2 = "";
	   string inFile3 = "";
	   //If arguments were defined, load in images from args
  if( argc == 5 ) {
    inFile1 = argv[2];
    inFile2 = argv[3];
    inFile3 = argv[4];
   }
  //Else, save images from the camera to the data folder
  else {
    //wait for button input and enable flash, and set led to show iteration
	//Value 9 is far left button
	while(run_buttons_mode() != 9){}
    system("python3 /etc/takepicture.py /mnt/sd-mmcblk0p1/data/left.jpg");
	//Once picture is saved, set LED to show picture complete
	run_leds_mode(8);
	while(run_buttons_mode() != 5){}
    system("python3 /etc/takepicture.py /mnt/sd-mmcblk0p1/data/middle.jpg");
	run_leds_mode(4);
	while(run_buttons_mode() != 3){}
    system("python3 /etc/takepicture.py /mnt/sd-mmcblk0p1/data/right.jpg");
	run_leds_mode(2);
    inFile1 = "left.jpg";
    inFile2 = "middle.jpg";
    inFile3 = "right.jpg";
  }

  cout << "Stiching images: "<< inFile1 << " and image: "
      << inFile2 << " and image: " << inFile3 << endl;
  string img_path1 = "data/" + inFile1;
  string img_path2 = "data/" + inFile2;
  string img_path3 = "data/" + inFile3;

  in_image1=imread(img_path1 ,1);
  in_image2=imread(img_path2,1);
  in_image3=imread(img_path3,1);

  if (!in_image1.data || !in_image2.data || !in_image3.data) {
    cout << "Could not open an image, check either camera or args" << endl;
    return -1;
  };

  unsigned int DATA_SIZE = in_image1.rows * in_image1.cols;
  size_t size_in_bytes = DATA_SIZE * sizeof(unsigned char);

  cvtColor(in_image1, grey_image1, cv::COLOR_BGR2GRAY);
  cvtColor(in_image2, grey_image2, cv::COLOR_BGR2GRAY);
  cvtColor(in_image3, grey_image3, cv::COLOR_BGR2GRAY);

  Mat key1_img, key2_img, key3_img;
  key1_img = grey_image1.clone();
  key2_img = grey_image2.clone();
  key3_img = grey_image3.clone();
  int height = in_image1.rows;
  int width = in_image1.cols;
  unsigned char threshold_value = 20;
  //unsigned int max_binary_value = 255;

  //std::cout << " size_in_bytes = '" << size_in_bytes << "'\n";

  char* xclbinFilename = argv[1];
  std::vector<cl::Device> devices;
  cl::Device device;
  std::vector<cl::Platform> platforms;
  bool found_device = false;
  cl::Platform::get(&platforms);
  for(size_t i = 0; (i < platforms.size() ) & (found_device == false) ;i++){
  	cl::Platform platform = platforms[i];
    std::string platformName = platform.getInfo<CL_PLATFORM_NAME>();
    if ( platformName == "Xilinx"){
     	devices.clear();
     	platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
      if (devices.size()){
        device = devices[0];
        found_device = true;
        break;
      }
    }
  }
  if (found_device == false){
    std::cout << "Error: Unable to find Target Device "
             << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    return EXIT_FAILURE;
  }



  cl::Context context(device);
  cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);


  std::cout << "Loading: '" << xclbinFilename << "'\n";
  std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
  bin_file.seekg (0, bin_file.end);
  unsigned nb = bin_file.tellg();
  bin_file.seekg (0, bin_file.beg);
  char *buf = new char [nb];
  bin_file.read(buf, nb);
  cl::Program::Binaries bins;
  bins.push_back({buf,nb});
  devices.resize(1);
  cl::Program program(context, devices, bins);
  //Declaring 3 fast accelerators
  //cl::Kernel fast1(program,"fast_accel");
  cl::Kernel fast2(program,"fast_accel2");
  //cl::Kernel fast3(program,"fast_accel3");

  //cl::Kernel bfmatcher(program,"bfmatcher_accel");

  cl::Buffer buffer_in1(context,  CL_MEM_READ_ONLY, size_in_bytes);
  cl::Buffer buffer_out1(context, CL_MEM_WRITE_ONLY, size_in_bytes);
  cl::Buffer buffer_in2(context,  CL_MEM_READ_ONLY, size_in_bytes);
  cl::Buffer buffer_out2(context, CL_MEM_WRITE_ONLY, size_in_bytes);
  cl::Buffer buffer_in3(context,  CL_MEM_READ_ONLY, size_in_bytes);
  cl::Buffer buffer_out3(context, CL_MEM_WRITE_ONLY, size_in_bytes);
/*
  int narg=0;
  fast1.setArg(narg++, buffer_in1);
  fast1.setArg(narg++, threshold_value);
  fast1.setArg(narg++, buffer_out1);
  fast1.setArg(narg++, grey_image1.rows);
  fast1.setArg(narg++, grey_image1.cols);
*/
  int narg=0;
  fast2.setArg(narg++, buffer_in2);
  fast2.setArg(narg++, threshold_value);
  fast2.setArg(narg++, buffer_out2);
  fast2.setArg(narg++, grey_image2.rows);
  fast2.setArg(narg++, grey_image2.cols);
/*
  narg=0;
  fast3.setArg(narg++, buffer_in3);
  fast3.setArg(narg++, threshold_value);
  fast3.setArg(narg++, buffer_out3);
  fast3.setArg(narg++, grey_image3.rows);
  fast3.setArg(narg++, grey_image3.cols);
*/
  unsigned char *ptr_in1 = (unsigned char  *) q.enqueueMapBuffer (buffer_in1 ,  CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
  unsigned char *ptr_out1 = (unsigned char *) q.enqueueMapBuffer (buffer_out1 , CL_TRUE , CL_MAP_READ  , 0, size_in_bytes);
  unsigned char *ptr_in2 = (unsigned char  *) q.enqueueMapBuffer (buffer_in2 ,  CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
  unsigned char *ptr_out2 = (unsigned char *) q.enqueueMapBuffer (buffer_out2 , CL_TRUE , CL_MAP_READ  , 0, size_in_bytes);
  unsigned char *ptr_in3 = (unsigned char  *) q.enqueueMapBuffer (buffer_in3 ,  CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
  unsigned char *ptr_out3 = (unsigned char *) q.enqueueMapBuffer (buffer_out3 , CL_TRUE , CL_MAP_READ  , 0, size_in_bytes);

  for (unsigned int i = 0; i< size_in_bytes; i++) {
  	ptr_in1[i] = grey_image1.data[i];
  	ptr_in2[i] = grey_image2.data[i];
    ptr_in3[i] = grey_image3.data[i];
  }

  key1_img.data =  ptr_out1;
  key2_img.data =  ptr_out2;
  key3_img.data =  ptr_out3;

  //std::cout <<"Haven't enqueued task yet\n";

  //std::cout <<"Before first fast\n";

  clock_t start, end;
  start = clock();

	q.enqueueMigrateMemObjects({buffer_in2},0);
	q.enqueueTask(fast2);
	q.enqueueMigrateMemObjects({buffer_out2},CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
	narg=0;
	fast2.setArg(narg++, buffer_in1);
	fast2.setArg(narg++, threshold_value);
	fast2.setArg(narg++, buffer_out1);
	fast2.setArg(narg++, grey_image1.rows);
	fast2.setArg(narg++, grey_image1.cols);
	q.enqueueMigrateMemObjects({buffer_in1},0);
	q.enqueueTask(fast2);
	q.enqueueMigrateMemObjects({buffer_out1},CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
	narg=0;
	fast2.setArg(narg++, buffer_in3);
	fast2.setArg(narg++, threshold_value);
	fast2.setArg(narg++, buffer_out3);
	fast2.setArg(narg++, grey_image3.rows);
	fast2.setArg(narg++, grey_image3.cols);
	q.enqueueMigrateMemObjects({buffer_in3},0);
	q.enqueueTask(fast2);
	q.enqueueMigrateMemObjects({buffer_out3},CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
	end = clock();
   double time_taken = double(end-start) / double(CLOCKS_PER_SEC);
   cout << "Total time taken for hardware FAST is " << fixed << time_taken << setprecision(6) << endl;

  for(int i = 0 ;i < grey_image1.rows; i++){
	  for(int j = 0; j< grey_image2.cols; j++){
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
		  if (value3==255){
			  cv::KeyPoint key(j, i, 1);
			  keypoints3.push_back(key);
		  }
	  }
  }
  std::cout <<"Before first fast\n";

  cv::Mat out1, out2, out3;

  cv::drawKeypoints(grey_image1, keypoints1, out1);
  cv::drawKeypoints(grey_image2, keypoints2, out2);
  cv::drawKeypoints(grey_image3, keypoints3, out3);
  std::cout <<"Before first fast\n";

  cv::imwrite("1_keypoints.jpg", out1);
  cv::imwrite("2_keypoints.jpg", out2);
  cv::imwrite("3_keypoints.jpg", out3);
  std::cout <<"Before first fast\n";

  Ptr<DescriptorExtractor> extractor = ORB::create();
  extractor->compute(grey_image1, keypoints1, descriptors1);
  extractor->compute(grey_image2, keypoints2, descriptors2);
  extractor->compute(grey_image3, keypoints3, descriptors3);
  std::cout <<"Before first fast\n";

  /*

  std::cout <<"after extractor\n";

  short int* tmp_match;
  int nkp1 = descriptors1.rows;
  int nkp2 = descriptors2.rows;

  std::cout << nkp1 << std::endl;
  std::cout << nkp2 << std::endl;


  std::cout <<"buffers declared\n";

  cl::Buffer descbuff_in1(context,  CL_MEM_READ_ONLY, nkp1 * sizeof(ap_uint<256>));
  cl::Buffer descbuff_in2(context, CL_MEM_READ_ONLY, nkp1 * sizeof(ap_uint<256>));
  cl::Buffer descbuff_out(context,  CL_MEM_WRITE_ONLY, nkp1 * sizeof(short int));
  std::cout <<"buffers declared\n";

  narg=0;
  float bf_arg = .99;
  bfmatcher.setArg(narg++, descbuff_in1);
  std::cout <<"args1 declared\n";

  bfmatcher.setArg(narg++, descbuff_in2);
  std::cout <<"args2 declared\n";

  bfmatcher.setArg(narg++, descbuff_out);
  std::cout <<"args3 declared\n";

  bfmatcher.setArg(narg++, nkp1);
  std::cout <<"args4 declared\n";

  bfmatcher.setArg(narg++, nkp2);
  std::cout <<"args5 declared\n";

  bfmatcher.setArg(narg++, bf_arg);
  std::cout <<"args6 declared\n";

  //check this
  ap_uint<256> *desc_in1 = (ap_uint<256>  *) q.enqueueMapBuffer (descbuff_in1 ,  CL_TRUE , CL_MAP_WRITE , 0, nkp1 * sizeof(ap_uint<256>));
  ap_uint<256> *desc_in2 = (ap_uint<256>  *) q.enqueueMapBuffer (descbuff_in2 ,  CL_TRUE , CL_MAP_WRITE , 0, nkp2 * sizeof(ap_uint<256>));
  short int *desc_out = (short int  *) q.enqueueMapBuffer (descbuff_out ,  CL_TRUE , CL_MAP_READ , 0, nkp1 * sizeof(short int));
  std::cout <<"after descriptor decleration\n";

  for (int i = 0; i< nkp1; i++) {
    	desc_in1[i] = descriptors1.data[i];
  }
  for (int i = 0; i< nkp2; i++) {
      	desc_in2[i] = descriptors2.data[i];
  }
  tmp_match = desc_out;

  std::cout <<"Before calling bf_matcher\n";

  q.enqueueMigrateMemObjects({descbuff_in1},0);
  q.enqueueMigrateMemObjects({descbuff_in2},0);
  q.enqueueTask(bfmatcher);
  q.enqueueMigrateMemObjects({descbuff_out},CL_MIGRATE_MEM_OBJECT_HOST);
  q.finish();

  vector<DMatch> good_matches;

  int rev_matches = 0;
  for (int i = 0; i < nkp1; i++) {
	  if ((int)tmp_match[i] >= 0) rev_matches++;
  }

  good_matches.resize(rev_matches);
  rev_matches = 0;
  for (int i = 0; i < nkp1; i++) {
	  std::cout << "Temp match is" << tmp_match[i] << std::endl;

	  if ((int)tmp_match[i] >= 0) {
		  good_matches[rev_matches].queryIdx = i;

		  good_matches[rev_matches].trainIdx = (int)tmp_match[i];
		  rev_matches++;
	  }
  }
*/
  int nkp1 = descriptors1.rows;
  int nkp2 = descriptors2.rows;
  int16_t tmp_good_matches[nkp1];

  printf("\n size: %d\n", nkp1);
  printf("\n size: %d\n", nkp2);


  vector<cv::DMatch> good_matches_l, good_matches_r, good_matches_temp;
  cv::BFMatcher matcher = cv::BFMatcher(cv::NORM_L2, true);
  try {
	  matcher.match(descriptors2, descriptors1, good_matches_l);
	  matcher.match(descriptors2, descriptors3, good_matches_r);
	  matcher.match(descriptors1, descriptors2, good_matches_temp);

  }
  catch (const cv::Exception& ex){
   cout << "Exception thrown after point2f conversion, restarting camera" << endl;
   run_leds_mode(1);
   continue;
  }
  catch (const std::exception& ex){
   cout << "Exception thrown after point2f conversion, restarting camera" << endl;
   run_leds_mode(1);
   continue;
  }
  printf("\n good match size: %d\n", good_matches_l.size());
  printf("\n good match size: %d\n", good_matches_r.size());

  //(grey_image1.rows, grey_image1.cols + grey_image2.cols, CV_8UC1); //allocate memory for output gray image of fast accel
  cout << "result declared" << endl;
  cv::Mat ref_l, ref_r;
  try {
	  cv::drawMatches(grey_image1, keypoints1, grey_image2, keypoints2, good_matches_temp, ref_l, cv::Scalar::all(-1),cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	  cv::drawMatches(grey_image2, keypoints2, grey_image3, keypoints3, good_matches_r, ref_r, cv::Scalar::all(-1),cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
  }
  catch (const cv::Exception& ex){
     cout << "Exception thrown after point2f conversion, restarting camera" << endl;
     run_leds_mode(1);
     continue;
    }
    catch (const std::exception& ex){
     cout << "Exception thrown after point2f conversion, restarting camera" << endl;
     run_leds_mode(1);
     continue;
    }

 cv::imwrite("ref1.jpg", ref_l);
 cv::imwrite("ref2.jpg", ref_r);

  vector< cv::Point2f > src_l, dest_l, src_r, dest_r;
  cv::Mat H_l, H_r;
  cout << "points declared" << endl;


  //std::cout << "Printing size" << std::endl;
try{
for (int i = 0; i < good_matches_l.size(); i++){
		src_l.push_back(keypoints2[good_matches_l[i].queryIdx].pt);
		dest_l.push_back(keypoints1[good_matches_l[i].trainIdx].pt);
	}

    for (int i = 0; i < good_matches_r.size(); i++){
		src_r.push_back(keypoints2[good_matches_r[i].queryIdx].pt);
		dest_r.push_back(keypoints3[good_matches_r[i].trainIdx].pt);
	}
}
catch (const cv::Exception& ex){
 cout << "Exception thrown after point2f conversion, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}
catch (const std::exception& ex){
 cout << "Exception thrown after point2f conversion, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}
try {
  H_l = cv::findHomography(dest_l,src_l,cv::RANSAC, 5.0);
  H_r = cv::findHomography(dest_r,src_r,cv::RANSAC, 5.0);
}
catch (const cv::Exception& ex){
 cout << "Exception thrown after homography, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}
catch (const std::exception& ex){
 cout << "Exception thrown after homography, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}

  double translation[] = { 1, 0, in_image1.cols,
                            0, 1, in_image1.rows,
                            0, 0, 1            };
  cv::Mat translation_matrix(3, 3, CV_64FC1, translation);
  cv::Mat H_fl, H_fr;
  try {
  H_fl = translation_matrix * H_l;
  H_fr = translation_matrix * H_r;
  }
  catch (const cv::Exception& ex){
   cout << "Exception thrown after homography, restarting camera" << endl;
   run_leds_mode(1);
   continue;
  }
  catch (const std::exception& ex){
   cout << "Exception thrown after homography, restarting camera" << endl;
   run_leds_mode(1);
   continue;
  }
  // cout << "M = " << endl << " "  << translation_matrix << endl << endl;
  cv::Mat result(in_image1.rows * 3, in_image1.cols * 3, CV_8UC3);
  Mat result_l(in_image1.rows * 3, in_image1.cols * 3, CV_8UC3);
  Mat result_r(in_image1.rows * 3, in_image1.cols * 3, CV_8UC3);
  cv::Mat test_l(cv::Size(in_image1.cols * 3, in_image1.rows * 3), CV_8UC3);
  cv::Mat test_r(cv::Size(in_image1.cols * 3, in_image1.rows * 3), CV_8UC3);

  printf("error point 1\n");

  in_image1.copyTo(test_l(cv::Rect(0, 0, in_image1.cols, in_image1.rows)));
  in_image3.copyTo(test_r(cv::Rect(0, 0, in_image1.cols, in_image1.rows)));

  printf("test point 4\n");
  //Try catch needed if not sufficient matchpoints
try {
  cv::warpPerspective(test_l, result_l, H_fl, cv::Size(in_image1.cols * 3, in_image1.rows * 3));
  cv::warpPerspective(test_r, result_r, H_fr, cv::Size(in_image1.cols * 3, in_image1.rows * 3));
}
catch (const cv::Exception& ex){
 cout << "Exception thrown after warp perspective, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}
catch (const std::exception& ex){
 cout << "Exception thrown after warp perspective, restarting camera" << endl;
 run_leds_mode(1);
 continue;
}
  printf("test point 5\n");
  result += result_r + result_l;

  in_image2.copyTo(result(cv::Rect(in_image1.cols, in_image1.rows, in_image1.cols, in_image1.rows)));
  std::cout << "Result rows: " << result.rows << "Result colums: " << result.cols << std::endl;
  printf("test point 4\n");

  string in_image1_path1 = "cp ./data/left.jpg /srv/www/gallery/" + to_string(imageLoop) + "_left.jpg";
  string in_image2_path1 = "cp ./data/middle.jpg /srv/www/gallery/" + to_string(imageLoop) + "_middle.jpg";
  string in_image3_path1 = "cp ./data/right.jpg /srv/www/gallery/" + to_string(imageLoop) + "_right.jpg";
  string ref_path1 = "cp ref.jpg /srv/www/gallery/" + to_string(imageLoop) + "_ref.jpg";
  string ref1_path1 = "cp ref1.jpg /srv/www/gallery/" + to_string(imageLoop) + "_ref1.jpg";
  string ref2_path1 = "cp ref2.jpg /srv/www/gallery/" + to_string(imageLoop) + "_ref2.jpg";

  string keypoints_1 = "cp 1_keypoints.jpg /srv/www/gallery/" + to_string(imageLoop) + "_1_keypoints.jpg";
  string keypoints_2 = "cp 2_keypoints.jpg /srv/www/gallery/" + to_string(imageLoop) + "_2_keypoints.jpg";
  string keypoints_3 = "cp 3_keypoints.jpg /srv/www/gallery/" + to_string(imageLoop) + "_3_keypoints.jpg";

  string in_image1_path2 = "cp ./data/left.jpg ./data/" + to_string(imageLoop) + "_left.jpg";
  string in_image2_path2 = "cp ./data/middle.jpg ./data/" + to_string(imageLoop) + "_middle.jpg";
  string in_image3_path2 = "cp ./data/right.jpg ./data/" + to_string(imageLoop) + "_right.jpg";
  string ref_path2 = "cp ref.jpg ./data/" + to_string(imageLoop) + "_ref.jpg";
  string ref1_path2 = "cp ref1.jpg ./data/" + to_string(imageLoop) + "_ref1.jpg";
  string ref2_path2 = "cp ref2.jpg ./data/" + to_string(imageLoop) + "_ref2.jpg";


  cv::imwrite("ref.jpg", result);

  char arr1[in_image1_path1.length() + 1];
  char arr2[in_image2_path1.length() + 1];
  char arr3[in_image3_path1.length() + 1];
  char arr4[ref_path1.length() + 1];
  char arr5[in_image1_path2.length() + 1];
  char arr6[in_image1_path2.length() + 1];
  char arr7[in_image1_path2.length() + 1];
  char arr8[ref_path2.length() + 1];
  char arr9[ref1_path1.length() + 1];
  char arr10[ref2_path1.length() + 1];
  char arr11[ref1_path2.length() + 1];
  char arr12[ref2_path2.length() + 1];

  char arr13[keypoints_1.length() + 1];
  char arr14[keypoints_2.length() + 1];
  char arr15[keypoints_3.length() + 1];



  strcpy(arr1, in_image1_path1.c_str());
  strcpy(arr2, in_image2_path1.c_str());
  strcpy(arr3, in_image3_path1.c_str());
  strcpy(arr4, ref_path1.c_str());
  strcpy(arr5, in_image1_path2.c_str());
  strcpy(arr6, in_image2_path2.c_str());
  strcpy(arr7, in_image3_path2.c_str());
  strcpy(arr8, ref_path2.c_str());
  strcpy(arr9, ref1_path1.c_str());
  strcpy(arr10, ref2_path1.c_str());
  strcpy(arr11, ref1_path2.c_str());
  strcpy(arr12, ref2_path2.c_str());
  strcpy(arr13, keypoints_1.c_str());
  strcpy(arr14, keypoints_2.c_str());
  strcpy(arr15, keypoints_3.c_str());



  system(arr1);
  system(arr2);
  system(arr3);
  system(arr4);
  system(arr5);
  system(arr6);
  system(arr7);
  system(arr8);
  system(arr9);
  system(arr10);
  system(arr11);
  system(arr12);
  system(arr13);
  system(arr14);
  system(arr15);



  cout << "Stitching complete" << endl;
  run_leds_mode(15);
  imageLoop++;

  }
  return status;
}


