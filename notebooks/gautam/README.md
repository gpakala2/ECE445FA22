# Gautam Worklog

[TOC]

# 2022-09-14 - Initial Design Idea Discussion

Today, we discussed the idea of building an image stitcher. I looked into the basic idea image stitching and its workflow. I found a github of a software image stitching process with a library called opencv for computer vision algorithms.

[https://github.com/tharaka27/SoCStitcher](https://github.com/tharaka27/SoCStitcher)  
[OpenCV C++ Documentation](https://www.opencv-srf.com/2017/11/load-and-display-image.html)

The workflow of image stitching involves key point detection, keypoint description, keypoint matching, homography calculation then image warping and overlapping.

![](stitch_process.png)

# 2022-09-20 - Search for Hardware Acceleration

Looking into the process of image stitching, I found three functions that can be accelerated through the FPGA.

**Keypoint Detection:** 
There are multiple methods of keypoint detection I found. SURF, SIFT, and FAST. According to the article below, ORB, which uses FAST, is the fastest algorithm and is also used in phones.

[ORB Process Article](https://medium.com/@deepanshut041/introduction-to-orb-oriented-fast-and-rotated-brief-4220e8ec40cf)  

FAST uses a circle of comparisons of the greyscale values around a pixel, rather than SIFT and SURF which are series of convolutions. FAST is much easier to accelerate.

![](FAST.jpg)

**Keypoint Description and Matching:** 

Description of the keypoints generates unique binary descriptors based on position in the image. This is a process I determined would yield too much hardware LUT consumption on the FPGA and instead opted to do in software. On the other hand, the algorithm for matching could be easily accelerated. For matching key points, I found the Brute Force algorithm. As it sounds and shows in the image below, this algorithm iteratively goes through each point in the train (reference) image and tests them with all the key points in the query (image to be warped) image. This may be a bottleneck if done in software, but hardware accelerated, this process can be parallelized and done at a much faster rate.

![](bruteforce.png)

**Homography Transformation:**

The homography matrix determines how to warp the query image into the reference frame of the train image. The homography calculation in the process was debated today on whether to be done in hardware or not. This calculation is a linear algebra least-squares problem involving finding the eigenvector of the keypoint match matrix with the highest eigenvalue. This matrix only needs to be solved with 4 keypoint matches. This can cause the homography warp to be slightly incorrect. So cthe RANSAC algorithm that can be added,iteratively loops through keypoint matches and finds the homography matrix with the highest eigenvalue as the best solution. This adds robustness to our calculation.

![](homography.png)

**Image Warp:**
The last step in the process is blending. This simply involves matrix multiplying the homography matrix across the image. I thought this would be extremely easy to accelerate using a systolic array matrix multiplier to apply the transformation to the image.
 
# 2022-10-06 - Vitis Library Environment Set Up

# 2022-10-22 - Image Overlay Process

# 2022-11-10 - OpenCL Testing


