#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Utils.h"
#include <glm/glm.hpp>

bool validateImage(const cv::Mat& img) {
	int margin = 10;

	cv::Mat gray_img;
	cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);

	// if there is no line, return false.
	double min_val, max_val;
	cv::minMaxLoc(gray_img, &min_val, &max_val);
	if (min_val >= 100) return false;

	// check horizontally
	cv::Mat hor;
	cv::reduce(gray_img, hor, 0, CV_REDUCE_MIN);
	for (int c = 0; c < margin; ++c) {
		if (hor.at<uchar>(0, c) < 100) return false;
	}
	for (int c = gray_img.cols - 1; c > gray_img.cols - margin - 1; --c) {
		if (hor.at<uchar>(0, c) < 100) return false;
	}

	// check vertically
	cv::Mat ver;
	cv::reduce(gray_img, ver, 1, CV_REDUCE_MIN);
	for (int r = 0; r < margin; ++r) {
		if (ver.at<uchar>(r, 0) < 100) return false;
	}
	for (int r = gray_img.rows - 1; r > gray_img.rows - margin - 1; --r) {
		if (ver.at<uchar>(r, 0) < 100) return false;
	}

	return true;
}

int main() {
	cv::Mat img = cv::imread("C:/Anaconda/caffe/contour_regression/data/images/01/000/000001.png");
	
	// extract contour vectors
	std::vector<std::pair<glm::vec2, glm::vec2>> contour;
	utils::extractEdges(img, contour);

	cv::Mat result(img.size(), CV_8U, cv::Scalar(255));
	for (int i = 0; i < contour.size(); ++i) {
		cv::line(result, cv::Point(contour[i].first.x, contour[i].first.y), cv::Point(contour[i].second.x, contour[i].second.y), cv::Scalar(0), 1);
	}
	cv::imwrite("result.png", result);

	return 0;
}