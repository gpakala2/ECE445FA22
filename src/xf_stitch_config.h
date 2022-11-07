#ifndef _XF_STITCH_CONFIG_H_
#define _XF_STITCH_CONFIG_H_

#include "hls_stream.h"
#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "features/xf_fast.hpp"
#include "imgproc/xf_bfmatcher.hpp"
#include "highgui.hpp"
#include "core.hpp"
#include "imgcodecs.hpp"
#include "imgproc.hpp"
#include "features2d.hpp"
#include "ap_int.h"
#include "common/xf_headers.hpp"
#include "calib3d.hpp"

typedef unsigned short int uint16_t;

#define WIDTH 1440
#define HEIGHT 1080

#define TYPE XF_8UC1
#define CH_TYPE XF_GRAY

#define NPC1 XF_NPPC8

#define INPUT_PTR_WIDTH 256
#define OUTPUT_PTR_WIDTH 256

#define BF_OUTPUT_PTR_WIDTH 16

#define NMS 1
#define XF_CV_DEPTH_IN_1 1
#define XF_CV_DEPTH_OUT_1 1


static const int MAX_KEYPOINTS = 1100;
static const int PARALLEL_COMPUTEUNIT = 4;

void fast_accel(ap_uint<INPUT_PTR_WIDTH>* img_inp, unsigned char threshold, ap_uint<OUTPUT_PTR_WIDTH>* img_out, int rows, int cols);

void bfmatcher_accel(ap_uint<INPUT_PTR_WIDTH>* desc_list1,
                     ap_uint<INPUT_PTR_WIDTH>* desc_list2,
                     ap_int<BF_OUTPUT_PTR_WIDTH>* desc_match_idx,
                     uint32_t num_keypoints1,
                     uint32_t num_keypoints2,
                     float ratio_thresh);

#endif //_XF_STITCH_CONFIG_H_
