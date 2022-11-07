#!/bin/bash

rm stitch ref.jpg test.jpg

g++ xf_fast_tb.cpp fast_accel.cpp -D__SDSVHLS__ -I/tools/Xilinx/Vitis_HLS/2022.2/include -I/home/gautam/test/Vitis_Libraries/vision/L1/include -I/home/gautam/test/install/include/opencv4/opencv2 -std=c++0x -fcf-protection=none -L/home/gautam/test/install/lib -L/usr/lib -L/lib -L/usr/lib/x86_64-linux-gnu -lopencv_calib3d -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_features2d -o stitch

./stitch new_left.jpg new_right.jpg
