#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

namespace cvutils {
	cv::Mat rectify_image(cv::Mat& image, const std::vector<cv::Point2f>& pts);	void resize_image(cv::Mat src, cv::Mat& tgt, cv::Size tgt_size);	void skeletonize(cv::Mat src, cv::Mat& tgt);	void grayScale(cv::Mat img, cv::Mat& grayImg);
}


