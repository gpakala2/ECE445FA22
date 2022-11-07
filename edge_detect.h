#include "hls_video.h"

typedef ap_axiu<24,1,1,1> interface_t;
typedef ap_uint<3> interface_3_bits;
typedef hls::stream<interface_t> stream_t;

void edge_detect(stream_t &stream_in, stream_t &stream_out);

#define MAX_WIDTH 	1280
#define MAX_HEIGHT  720

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> rgb_img_t;
typedef hls::Scalar<3, unsigned char> rgb_pix_t;

#define INPUT_IMAGE "rover.bmp"
#define OUTPUT_IMAGE "rover_out.bmp"
