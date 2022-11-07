#include "edge_detect.h"


void mysobel(rgb_img_t &src, rgb_img_t &dst, int dir)
{
	int const rows = MAX_HEIGHT;
	int const cols = MAX_WIDTH;

	rgb_img_t img0(rows, cols);

	if (dir)
	{
		hls::Sobel<1,0,3>(src, img0);
	}
	else
	{
		hls::Sobel<0,1,3>(src, img0);
	}

	hls::ConvertScaleAbs(img0, dst);

}

void mysobelxy(rgb_img_t &src, rgb_img_t &dst)
{
	int const rows = MAX_HEIGHT;
	int const cols = MAX_WIDTH;

	rgb_img_t img0(rows, cols);
	rgb_img_t img1(rows, cols);
	rgb_img_t img2(rows, cols);
	rgb_img_t img3(rows, cols);

	hls::Duplicate(src, img0, img1);
	mysobel(img0, img2, 1);
	mysobel(img1, img3, 0);
	hls::AddWeighted(img2, 1, img3, 1, 0, dst);
}

void sobelfoo(stream_t &stream_in, stream_t &stream_out)
{
	int const rows = MAX_HEIGHT;
	int const cols = MAX_WIDTH;

	rgb_img_t img0(rows, cols);
	rgb_img_t img1(rows, cols);
	rgb_img_t img2(rows, cols);
	rgb_img_t img4(rows, cols);

	hls::AXIvideo2Mat(stream_in, img0);

	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	mysobelxy(img1,img2);
	hls::CvtColor<HLS_GRAY2RGB>(img2, img4);

	hls::Mat2AXIvideo(img4, stream_out);
}
//
//void blurfoo(stream_t &stream_in, stream_t &stream_out)
//{
//	int const rows = MAX_HEIGHT;
//	int const cols = MAX_WIDTH;
//
//	rgb_img_t img0(rows, cols);
//	rgb_img_t img1(rows, cols);
//
//	hls::AXIvideo2Mat(stream_in, img0);
//
//	hls::GaussianBlur<5,5>(img0, img1, (double)5, (double)5);
//
//	hls::Mat2AXIvideo(img1, stream_out);
//
//}

void edge_detect(stream_t &stream_in, stream_t &stream_out)
{

	int const rows = MAX_HEIGHT;
	int const cols = MAX_WIDTH;

	sobelfoo(stream_in, stream_out);
}
