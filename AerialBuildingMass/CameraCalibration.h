#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>

class CameraCalibration {
protected:
	CameraCalibration() {}

public:
	static double calibrateCamera(std::vector<std::vector<cv::Point3f> >& objectPoints, std::vector<std::vector<cv::Point2f> >& imagePoints, cv::Size size, cv::Mat& cameraMat, cv::Mat& distortion, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs);
	static void projectPoints(std::vector<cv::Point3f> objectPoints, cv::Mat& rvec, cv::Mat& tvec, cv::Mat& cameraMat, cv::Mat& distortion, std::vector<cv::Point2f>& projectedImagePoints);

private:
	static void computeH(std::vector<cv::Point3f>& objectPoints, std::vector<cv::Point2f>& imagePoints, cv::Mat& H);
	static void computeB(std::vector<cv::Mat>& H, cv::Size& size, cv::Mat& B);
	static void computeIntrinsicMatrix(cv::Mat& B, cv::Mat& cameraMat);
	static void computeExtrinsicMatrix(cv::Mat& cameraMat, cv::Mat& H, cv::Mat& R, cv::Mat& T);
};

