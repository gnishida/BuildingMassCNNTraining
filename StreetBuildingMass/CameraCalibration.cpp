#include "CameraCalibration.h"
#include <opencv2/calib3d.hpp>
#include <iostream>

#ifndef SQR
#define SQR(x)	((x) * (x))
#endif

double CameraCalibration::calibrateCamera(std::vector<std::vector<cv::Point3f> >& objectPoints, std::vector<std::vector<cv::Point2f> >& imagePoints, cv::Size size, cv::Mat& cameraMat, cv::Mat& distortion, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs) {
	/*
	cv::calibrateCamera(objectPoints, imagePoints, size, cameraMat, distortion, rvecs, tvecs, CV_CALIB_ZERO_TANGENT_DIST | CV_CALIB_FIX_K2 | CV_CALIB_FIX_K3 | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5 | CV_CALIB_FIX_K6);
	std::cout << "<<< OpenCV results >>>" << std::endl;
	std::cout << "Camera Matrix:" << std::endl << cameraMat << std::endl;
	for (int i = 0; i < rvecs.size(); ++i) {
		std::cout << "R:" << std::endl << rvecs[i] << std::endl;
		std::cout << "T:" << std::endl << tvecs[i] << std::endl;
	}
	*/

	// 画像の数
	int n = objectPoints.size();

	rvecs.resize(n);
	tvecs.resize(n);

	//std::cout << "<<< My results >>>" << std::endl;
	std::vector<cv::Mat> H(n);
	for (int i = 0; i < n; ++i) {
		computeH(objectPoints[i], imagePoints[i], H[i]);
		//std::cout << "Homograph Matrix: " << std::endl << H[i] << std::endl;
	}

	cv::Mat B;
	computeB(H, size, B);

	computeIntrinsicMatrix(B, cameraMat);
	//std::cout << "Camera Matrix: " << std::endl << cameraMat << std::endl;

	return cv::calibrateCamera(objectPoints, imagePoints, cv::Size(128, 128), cameraMat, distortion, rvecs, tvecs, cv::CALIB_USE_INTRINSIC_GUESS | cv::CALIB_FIX_ASPECT_RATIO | cv::CALIB_FIX_PRINCIPAL_POINT | cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_K2 | cv::CALIB_FIX_K3 | cv::CALIB_FIX_K4 | cv::CALIB_FIX_K5 | cv::CALIB_FIX_K6);

	//return cv::calibrateCamera(objectPoints, imagePoints, size, cameraMat, distortion, rvecs, tvecs, CV_CALIB_ZERO_TANGENT_DIST | CV_CALIB_FIX_K2 | CV_CALIB_FIX_K3 | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5 | CV_CALIB_FIX_K6);

	/*
	for (int i = 0; i < n; ++i) {
		computeExtrinsicMatrix(cameraMat, H[i], rvecs[i], tvecs[i]);

		std::cout << "R:" << std::endl << rvecs[i] << std::endl;
		std::cout << "T:" << std::endl << tvecs[i] << std::endl;
	}

	double totalError = refine(objectPoints, imagePoints, cameraMat, distortion, rvecs, tvecs);
	
	return totalError;
	*/
}

/**
 * Project 3D points onto the image plane based on the intrinsic and extrinsic parameters.
 *
 * @param objectPoints			3D points
 * @param rvec					rotation parameters
 * @param tvec					translation parameters
 * @param cameraMat				intrinsic parameters
 * @param distortion			distortion parameters
 * @param projectedImagePoints	the projected points on the image plane
 */
void CameraCalibration::projectPoints(std::vector<cv::Point3f> objectPoints, cv::Mat& rvec, cv::Mat& tvec, cv::Mat& cameraMat, cv::Mat& distortion, std::vector<cv::Point2f>& projectedImagePoints) {
	// 外部パラメータ行列の作成
	cv::Mat R;
	cv::Rodrigues(rvec, R);
			
	cv::Mat P(3, 4, CV_64F);
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			P.at<double>(r, c) = R.at<double>(r, c);
		}
		P.at<double>(r, 3) = tvec.at<double>(r, 0);
	}

	// レンズ歪み
	double k1 = distortion.at<double>(0, 0);

	// principal points
	double u0 = cameraMat.at<double>(0, 2);
	double v0 = cameraMat.at<double>(1, 2);
	double fx = cameraMat.at<double>(0, 0);
	double fy = cameraMat.at<double>(1, 1);

	projectedImagePoints.resize(objectPoints.size());

	for (int i = 0; i < objectPoints.size(); ++i) {
		cv::Mat pts(4, 1, CV_64F);
		pts.at<double>(0, 0) = objectPoints[i].x;
		pts.at<double>(1, 0) = objectPoints[i].y;
		pts.at<double>(2, 0) = objectPoints[i].z;
		pts.at<double>(3, 0) = 1.0;

		cv::Mat pts2 = cameraMat * P * pts;

		double u = pts2.at<double>(0, 0) / pts2.at<double>(2, 0);
		double v = pts2.at<double>(1, 0) / pts2.at<double>(2, 0);
		double x = (u - u0) / fx;
		double y = (v - v0) / fy;

		double r2 = x * x + y * y;

		double du = (u - u0) * k1 * r2;
		double dv = (v - v0) * k1 * r2;

		projectedImagePoints[i].x = u + du;
		projectedImagePoints[i].y = v + dv;
	}
}

/**
 * Homogeneous 行列を計算する。Zhang論文の式(2)を参照のこと。
 *
 * @param objectPoints		3D座標のリスト
 * @param imagePoints		2D座標のリスト
 * @param H					計算されたHomogeneous行列
 */
void CameraCalibration::computeH(std::vector<cv::Point3f>& objectPoints, std::vector<cv::Point2f>& imagePoints, cv::Mat& H) {
	cv::Mat A(objectPoints.size() * 2, 9, CV_64F);
	for (int i = 0; i < objectPoints.size(); ++i) {
		A.at<double>(i * 2 + 0, 0) = objectPoints[i].x;
		A.at<double>(i * 2 + 0, 1) = objectPoints[i].y;
		A.at<double>(i * 2 + 0, 2) = 1;
		A.at<double>(i * 2 + 0, 3) = 0;
		A.at<double>(i * 2 + 0, 4) = 0;
		A.at<double>(i * 2 + 0, 5) = 0;
		A.at<double>(i * 2 + 0, 6) = -imagePoints[i].x * objectPoints[i].x;
		A.at<double>(i * 2 + 0, 7) = -imagePoints[i].x * objectPoints[i].y;
		A.at<double>(i * 2 + 0, 8) = -imagePoints[i].x;

		A.at<double>(i * 2 + 1, 0) = 0;
		A.at<double>(i * 2 + 1, 1) = 0;
		A.at<double>(i * 2 + 1, 2) = 0;
		A.at<double>(i * 2 + 1, 3) = objectPoints[i].x;
		A.at<double>(i * 2 + 1, 4) = objectPoints[i].y;
		A.at<double>(i * 2 + 1, 5) = 1;
		A.at<double>(i * 2 + 1, 6) = -imagePoints[i].y * objectPoints[i].x;
		A.at<double>(i * 2 + 1, 7) = -imagePoints[i].y * objectPoints[i].y;
		A.at<double>(i * 2 + 1, 8) = -imagePoints[i].y;
	}

	cv::Mat w, u, v;
	cv::SVD::compute(A, w, u, v);
	
	H = cv::Mat(3, 3, CV_64F);
	H.at<double>(0, 0) = v.at<double>(v.rows - 1, 0);
	H.at<double>(0, 1) = v.at<double>(v.rows - 1, 1);
	H.at<double>(0, 2) = v.at<double>(v.rows - 1, 2);
	H.at<double>(1, 0) = v.at<double>(v.rows - 1, 3);
	H.at<double>(1, 1) = v.at<double>(v.rows - 1, 4);
	H.at<double>(1, 2) = v.at<double>(v.rows - 1, 5);
	H.at<double>(2, 0) = v.at<double>(v.rows - 1, 6);
	H.at<double>(2, 1) = v.at<double>(v.rows - 1, 7);
	H.at<double>(2, 2) = v.at<double>(v.rows - 1, 8);


	// チェック
	/*
	for (int i = 0; i < objectPoints.size(); ++i) {
		cv::Mat pt(3, 1, CV_64F);
		pt.at<double>(0, 0) = objectPoints[i].x;
		pt.at<double>(1, 0) = objectPoints[i].y;
		pt.at<double>(2, 0) = 1;

		cv::Mat pt2 = H * pt;

		printf("(%.2lf, %.2lf) <-> (%.2lf, %.2lf)\n", imagePoints[i].x, imagePoints[i].y, pt2.at<double>(0, 0) / pt2.at<double>(2, 0), pt2.at<double>(1, 0) / pt2.at<double>(2, 0));
	}
	*/
}

/**
 * 行列B=(AA^T)^-1を計算する。Zhang論文の式(9)を参照のこと。
 * 
 * @param H			homogeneous行列
 * @param size		画像のサイズ
 * @param B			計算された行列B
 */
void CameraCalibration::computeB(std::vector<cv::Mat>& H, cv::Size& size, cv::Mat& B) {
	int n = H.size();

	cv::Mat A(n * 2 + 3, 6, CV_64F);
	for (int i = 0; i < n; ++i) {
		double h11 = H[i].at<double>(0, 0);
		double h12 = H[i].at<double>(0, 1);
		double h13 = H[i].at<double>(0, 2);
		double h21 = H[i].at<double>(1, 0);
		double h22 = H[i].at<double>(1, 1);
		double h23 = H[i].at<double>(1, 2);
		double h31 = H[i].at<double>(2, 0);
		double h32 = H[i].at<double>(2, 1);
		double h33 = H[i].at<double>(2, 2);

		A.at<double>(i * 2 + 0, 0) = h11 * h11;
		A.at<double>(i * 2 + 0, 1) = h11 * h22 + h12 * h21;
		A.at<double>(i * 2 + 0, 2) = h12 * h22;
		A.at<double>(i * 2 + 0, 3) = h11 * h23 + h13 * h21;
		A.at<double>(i * 2 + 0, 4) = h12 * h23 + h13 * h22;
		A.at<double>(i * 2 + 0, 5) = h13 * h23;

		A.at<double>(i * 2 + 1, 0) = h11 * h11 - h21 * h21;
		A.at<double>(i * 2 + 1, 1) = h11 * h12 * 2 - h21 * h22 * 2;
		A.at<double>(i * 2 + 1, 2) = h11 * h12 - h22 * h22;
		A.at<double>(i * 2 + 1, 3) = h11 * h13 * 2 - h21 * h23 * 2;
		A.at<double>(i * 2 + 1, 4) = h12 * h13 * 2 - h22 * h23 * 2;
		A.at<double>(i * 2 + 1, 5) = h13 * h13 - h23 * h23;
	}

	// 追加の制約条件
	{
		A.at<double>(n * 2 + 0, 0) = 0;
		A.at<double>(n * 2 + 0, 1) = 1;
		A.at<double>(n * 2 + 0, 2) = 0;
		A.at<double>(n * 2 + 0, 3) = 0;
		A.at<double>(n * 2 + 0, 4) = 0;
		A.at<double>(n * 2 + 0, 5) = 0;

		A.at<double>(n * 2 + 1, 0) = size.width * 0.5;
		A.at<double>(n * 2 + 1, 1) = 0;
		A.at<double>(n * 2 + 1, 2) = 0;
		A.at<double>(n * 2 + 1, 3) = 1;
		A.at<double>(n * 2 + 1, 4) = 0;
		A.at<double>(n * 2 + 1, 5) = 0;

		A.at<double>(n * 2 + 2, 0) = 0;
		A.at<double>(n * 2 + 2, 1) = 0;
		A.at<double>(n * 2 + 2, 2) = size.height * 0.5;
		A.at<double>(n * 2 + 2, 3) = 0;
		A.at<double>(n * 2 + 2, 4) = 1;
		A.at<double>(n * 2 + 2, 5) = 0;
	}

	cv::Mat w, u, v;
	cv::SVD::compute(A, w, u, v);

	double B11 = v.at<double>(v.rows - 1, 0);
	double B12 = v.at<double>(v.rows - 1, 1);
	double B22 = v.at<double>(v.rows - 1, 2);
	double B13 = v.at<double>(v.rows - 1, 3);
	double B23 = v.at<double>(v.rows - 1, 4);
	double B33 = v.at<double>(v.rows - 1, 5);

	B = cv::Mat(3, 3, CV_64F);
	B.at<double>(0, 0) = B11;
	B.at<double>(0, 1) = B12;
	B.at<double>(0, 2) = B13;
	B.at<double>(1, 0) = B12;
	B.at<double>(1, 1) = B22;
	B.at<double>(1, 2) = B23;
	B.at<double>(2, 0) = B13;
	B.at<double>(2, 1) = B23;
	B.at<double>(2, 2) = B33;

	if (B11 < 0) {
		B = -B;
	}
}

void CameraCalibration::computeIntrinsicMatrix(cv::Mat& B, cv::Mat& cameraMat) {
	double v0 = (B.at<double>(0, 1) * B.at<double>(0, 2) - B.at<double>(0, 0) * B.at<double>(1, 2)) / (B.at<double>(0, 0) * B.at<double>(1, 1) - B.at<double>(0, 1) * B.at<double>(0, 1));
	double lmbd = B.at<double>(2, 2) - (B.at<double>(0, 2) * B.at<double>(0, 2) + v0 * (B.at<double>(0, 1) * B.at<double>(0, 2) - B.at<double>(0, 0) * B.at<double>(1, 2))) / B.at<double>(0, 0);
	if (lmbd < 0) lmbd = -lmbd;
	double alpha = sqrt(lmbd / B.at<double>(0, 0));
	double beta = sqrt(lmbd * B.at<double>(0, 0) / (B.at<double>(0, 0) * B.at<double>(1, 1) - B.at<double>(0, 1) * B.at<double>(0, 1)));
	double gamma = -B.at<double>(0, 1) * alpha * alpha * beta / lmbd;
	double u0 = gamma * v0 / alpha - B.at<double>(0, 2) * alpha * alpha / lmbd;

	cameraMat.at<double>(0, 0) = alpha;
	cameraMat.at<double>(0, 1) = gamma;
	cameraMat.at<double>(0, 2) = u0;
	cameraMat.at<double>(1, 0) = 0;
	cameraMat.at<double>(1, 1) = beta;
	cameraMat.at<double>(1, 2) = v0;
	cameraMat.at<double>(2, 0) = 0;
	cameraMat.at<double>(2, 1) = 0;
	cameraMat.at<double>(2, 2) = 1;
}

/**
 * カメラ外部パラメータ行列を計算する
 *
 * @param cameraMat		カメラ内部パラメータ行列
 * @param H				homogeneous行列
 * @param R				計算された回転行列(3x1)
 * @param T				計算された並進行列(3x1)
 */
void CameraCalibration::computeExtrinsicMatrix(cv::Mat& cameraMat, cv::Mat& H, cv::Mat& R, cv::Mat& T) {
	cv::Mat R33(3, 3, CV_64F);
	R33 = cameraMat.inv() * H;
	double lmbd = -1.0 / sqrt(R33.at<double>(0, 0) * R33.at<double>(0, 0) + R33.at<double>(1, 0) * R33.at<double>(1, 0) + R33.at<double>(2, 0) * R33.at<double>(2, 0));

	R33 = R33 * lmbd;

	T = cv::Mat(3, 1, CV_64F);
	for (int r = 0; r < 3; ++r) {
		T.at<double>(r, 0) = R33.at<double>(r, 2);
	}

	// cross productにより回転行列の３列目を計算
	{
		R33.at<double>(0, 2) = R33.at<double>(1, 0) * R33.at<double>(2, 1) - R33.at<double>(2, 0) * R33.at<double>(1, 1);
		R33.at<double>(1, 2) = R33.at<double>(2, 0) * R33.at<double>(0, 1) - R33.at<double>(0, 0) * R33.at<double>(2, 1);
		R33.at<double>(2, 2) = R33.at<double>(0, 0) * R33.at<double>(1, 1) - R33.at<double>(1, 0) * R33.at<double>(0, 1);
	}

	// 回転行列の各列をnormalize
	for (int c = 0; c < 3; ++c) {
		double l = sqrt(R33.at<double>(0, c) * R33.at<double>(0, c) + R33.at<double>(1, c) * R33.at<double>(1, c) + R33.at<double>(2, c) * R33.at<double>(2, c));
		for (int r = 0; r < 3; ++r) {
			R33.at<double>(r, c) /= l;
		}
	}

	// 3x1行列に変換する
	cv::Rodrigues(R33, R);
}

