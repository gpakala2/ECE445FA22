#include "xf_stitch_config.h"

static constexpr int __XF_DEPTH_1 = (HEIGHT * WIDTH * (XF_PIXELWIDTH(TYPE, NPC1)) / 8) / (64 / 8);

void fast_accel(ap_uint<INPUT_PTR_WIDTH>* img_in, unsigned char threshold, ap_uint<OUTPUT_PTR_WIDTH>* img_out, int rows, int cols) {

    #pragma HLS INTERFACE m_axi      port=img_in        offset=slave  bundle=gmem0 depth=__XF_DEPTH_1
    #pragma HLS INTERFACE m_axi      port=img_out       offset=slave  bundle=gmem1 depth=__XF_DEPTH_1
    #pragma HLS INTERFACE s_axilite  port=rows 			          
	#pragma HLS INTERFACE s_axilite  port=cols			  
    #pragma HLS INTERFACE s_axilite  port=return

    xf::cv::Mat<TYPE, HEIGHT, WIDTH, NPC1, XF_CV_DEPTH_IN_1> in_mat(rows, cols);
    xf::cv::Mat<TYPE, HEIGHT, WIDTH, NPC1, XF_CV_DEPTH_OUT_1> out_mat(rows, cols);

    #pragma HLS DATAFLOW

    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, TYPE, HEIGHT, WIDTH, NPC1, XF_CV_DEPTH_IN_1>(img_in, in_mat);

    xf::cv::fast<NMS, TYPE, HEIGHT, WIDTH, NPC1, XF_CV_DEPTH_IN_1, XF_CV_DEPTH_OUT_1>(in_mat, out_mat, threshold);

    xf::cv::xfMat2Array<OUTPUT_PTR_WIDTH, TYPE, HEIGHT, WIDTH, NPC1, XF_CV_DEPTH_OUT_1>(out_mat, img_out);

    return;
}

// void bfmatcher_accel(
//     // ORB descriptor pointers
//     ap_uint<INPUT_PTR_WIDTH>* desc_list1,
//     ap_uint<INPUT_PTR_WIDTH>* desc_list2,

//     // Matching descriptor
//     ap_int<BF_OUTPUT_PTR_WIDTH>* desc_match_idx,

//     // number of valid keypoints in the corresponding desc lists
//     uint32_t num_keypoints1,
//     uint32_t num_keypoints2,

//     // ratio threshold for lowe's ratio test
//     float ratio_thresh
// ) {

//     xf::cv::bfMatcher<PARALLEL_COMPUTEUNIT, MAX_KEYPOINTS>(desc_list1, desc_list2, desc_match_idx, num_keypoints1, num_keypoints2, ratio_thresh);

// }