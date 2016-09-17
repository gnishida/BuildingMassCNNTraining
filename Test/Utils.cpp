﻿#include "Utils.h"
#include <regex>
#include <sstream>

#ifndef SQR
#define SQR(x)	((x) * (x))
#endif

namespace utils {

	const double M_PI = 3.141592653589;
	const float FLOAT_TOL = 1e-6f;

	bool isNumber(const std::string& str) {
		std::regex e("^-?\\d*\\.?\\d+");
		if (std::regex_match(str, e)) return true;
		else return false;
	}

	void computeMean(const std::vector<std::vector<float>>& values, std::vector<float>& mean) {
		mean.clear();

		if (values.size() == 0) return;

		// 総和を計算する
		mean.resize(values[0].size(), 0);
		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < values[i].size(); ++j) {
				mean[j] += values[i][j];
			}
		}

		// 平均を計算する
		for (int i = 0; i < mean.size(); ++i) {
			mean[i] /= (float)values.size();
		}
	}

	void computeVariance(const std::vector<std::vector<float>>& values, const std::vector<float>& mean, std::vector<float>& var) {
		var.clear();

		if (values.size() == 0) return;

		// 二乗差の総和を計算する
		var.resize(mean.size(), 0);
		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < values[i].size(); ++j) {
				var[j] += SQR(values[i][j] - mean[j]);
			}
		}

		// 二乗差の平均を計算する
		for (int i = 0; i < var.size(); ++i) {
			var[i] /= (float)values.size();
		}
	}

	/**
	 * Generate a random number in [0, 1).
	 * Note: 1 is exluded!
	 */
	float genRand() {
		return (float)(rand() % 1000) / 1000.0f;
	}

	/**
	 * Generate a random number in [0, b).
	 * Note: b is excluded!
	 */
	float genRand(float v) {
		return genRand() * v;
	}

	/**
	 * Generate a random number in [a, b).
	 * Note: b is excluded!
	 */
	float genRand(float a, float b) {
		return genRand(b - a) + a;
	}

	/**
	* Generate a random integer number in [0, a].
	* Note: a is included!
	*/
	int genIntRand(int a) {
		return genRand(a + 1);
	}

	/**
	* Generate a random integer number in [a, b].
	* Note: b is included!
	*/
	int genIntRand(int a, int b) {
		return genRand(b + 1 - a) + a;
	}

	/**
	* Computes the intersection between two line segments on the XY plane.
	* Segments must intersect within their extents for the intersection to be valid. z coordinate is ignored.
	*
	* @param a one end of the first line
	* @param b another end of the first line
	* @param c one end of the second line
	* @param d another end of the second line
	* @param tab
	* @param tcd
	* @param segmentOnly
	* @param intPoint	the intersection
	* @return true if two lines intersect / false otherwise
	**/
	bool segmentSegmentIntersect(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& d, float *tab, float *tcd, bool segmentOnly, glm::vec2& intPoint) {
		glm::vec2 u = b - a;
		glm::vec2 v = d - c;

		if (glm::length(u) < FLOAT_TOL || glm::length(u) < FLOAT_TOL) {
			return false;
		}

		float numer = v.x*(c.y - a.y) + v.y*(a.x - c.x);
		float denom = u.y*v.x - u.x*v.y;

		if (denom == 0.0f)  {
			// they are parallel
			*tab = 0.0f;
			*tcd = 0.0f;
			return false;
		}

		float t0 = numer / denom;

		glm::vec2 ipt = a + t0*u;
		glm::vec2 tmp = ipt - c;
		float t1;
		if (glm::dot(tmp, v) > 0.0f) {
			t1 = tmp.length() / v.length();
		}
		else {
			t1 = -1.0f * tmp.length() / v.length();
		}

		//Check if intersection is within segments
		if (segmentOnly && !((t0 >= FLOAT_TOL) && (t0 <= 1.0f - FLOAT_TOL) && (t1 >= FLOAT_TOL) && (t1 <= 1.0f - FLOAT_TOL))){
			return false;
		}

		*tab = t0;
		*tcd = t1;
		glm::vec2 dirVec = b - a;

		intPoint = a + (*tab)*dirVec;

		return true;
	}

	glm::vec2 projectPoint(int screen_width, int screen_height, const glm::vec3& p, const glm::mat4& mvpMatrix) {
		glm::vec4 pp = mvpMatrix * glm::vec4(p, 1);
		return glm::vec2((pp.x / pp.w + 1.0f) * 0.5f * screen_width, (1.0f - pp.y / pp.w) * 0.5f * screen_height);
	}

	void extractEdges(const cv::Mat& img, std::vector<std::pair<glm::vec2, glm::vec2>>& edges) {
		cv::Mat mat;
		if (img.channels() == 1) {
			mat = img.clone();
		}
		else if (img.channels() == 3) {
			cv::cvtColor(img, mat, CV_BGR2GRAY);
		}
		else if (img.channels() == 4) {
			cv::cvtColor(img, mat, CV_BGRA2GRAY);
		}

#if 0
		cv::imwrite("contour0.png", mat);
#endif

		cv::threshold(mat, mat, 128, 255, cv::THRESH_BINARY_INV);

		std::vector<cv::Vec4i> lines;
		cv::HoughLinesP(mat, lines, 1, CV_PI / 180, 10, 10, 10);

		// HoughLinesの結果を、edgesリストにコピー
		edges.resize(lines.size());
		for (int i = 0; i < lines.size(); ++i) {
			edges[i].first = glm::vec2(lines[i][0], lines[i][1]);
			edges[i].second = glm::vec2(lines[i][2], lines[i][3]);
		}

#if 0
		cv::Mat result(mat.size(), CV_8UC3, cv::Scalar(255, 255, 255));
		std::cout << "contour lines (" << edges.size() << "): " << std::endl;
		for (int i = 0; i < edges.size(); ++i) {
			std::cout << "(" << edges[i].first.x << "," << edges[i].first.y << ") - (" << edges[i].second.x << "," << edges[i].second.y << ")" << std::endl;
			cv::Scalar color(rand() % 250, rand() % 250, rand() % 250);
			cv::circle(result, cv::Point(edges[i].first.x, edges[i].first.y), 6, color, -1);
			cv::circle(result, cv::Point(edges[i].second.x, edges[i].second.y), 6, color, -1);
			cv::line(result, cv::Point(edges[i].first.x, edges[i].first.y), cv::Point(edges[i].second.x, edges[i].second.y), color, 2);
		}
		std::cout << std::endl;
		cv::imwrite("contour.png", result);
#endif

		utils::cleanEdges(edges, 20, 5.0 / 180.0 * M_PI);
#if 0
		cv::Mat result2(mat.size(), CV_8UC3, cv::Scalar(255, 255, 255));
		for (int i = 0; i < edges.size(); ++i) {
			std::cout << "(" << edges[i].first.x << "," << edges[i].first.y << ") - (" << edges[i].second.x << "," << edges[i].second.y << ")" << std::endl;
			cv::line(result2, cv::Point(edges[i].first.x, edges[i].first.y), cv::Point(edges[i].second.x, edges[i].second.y), cv::Scalar(rand() % 250, rand() % 250, rand() % 250), 3);
		}
		std::cout << std::endl;
		cv::imwrite("contour2.png", result2);
#endif

		//utils::cleanContours(edges, 80, 10.0 / 180.0 * M_PI);
#if 0
		cv::Mat result3(mat.size(), CV_8UC3, cv::Scalar(255, 255, 255));
		for (int i = 0; i < edges.size(); ++i) {
			std::cout << "(" << edges[i].first.x << "," << edges[i].first.y << ") - (" << edges[i].second.x << "," << edges[i].second.y << ")" << std::endl;
			cv::Scalar color(rand() % 250, rand() % 250, rand() % 250);
			cv::circle(result3, cv::Point(edges[i].first.x, edges[i].first.y), 6, color, -1);
			cv::circle(result3, cv::Point(edges[i].second.x, edges[i].second.y), 6, color, -1);
			cv::line(result3, cv::Point(edges[i].first.x, edges[i].first.y), cv::Point(edges[i].second.x, edges[i].second.y), color, 2);
		}
		std::cout << std::endl;
		cv::imwrite("contour3.png", result3);
#endif

	}

	void cleanEdges(std::vector<std::pair<glm::vec2, glm::vec2>>& edges, float maxLineGap, float theta) {
		float dotTol = cosf(theta);

		bool erased;
		while (true) {
			erased = false;
			for (int i = 0; i < edges.size() && !erased; ++i) {
				for (int j = i + 1; j < edges.size() && !erased; ++j) {
					if (glm::length(edges[i].first - edges[j].first) < 1 && glm::length(edges[i].second - edges[j].second) < 1) {
						edges.erase(edges.begin() + j);
						erased = true;
					}
					else if (glm::length(edges[i].first - edges[j].second) < 1 && glm::length(edges[i].second - edges[j].first) < 1) {
						edges.erase(edges.begin() + j);
						erased = true;
					}
					else {
						if (fabs(glm::dot(glm::normalize(edges[i].first - edges[i].second), glm::normalize(edges[j].first - edges[j].second))) > dotTol) {
							glm::vec2 norm1(-(edges[i].first - edges[i].second).y, (edges[i].first - edges[i].second).x);
							glm::vec2 norm2(-(edges[j].first - edges[j].second).y, (edges[j].first - edges[j].second).x);
							norm1 = glm::normalize(norm1);
							norm2 = glm::normalize(norm2);
							if (fabs(glm::dot(norm1, edges[j].first - edges[i].first)) < 3 || fabs(glm::dot(norm1, edges[j].second - edges[i].first)) < 3) {	// two lines are parallel and close!!
								if (fabs(edges[i].first.x - edges[i].second.x) > fabs(edges[i].first.y - edges[i].second.y)) {	// horizontal line
									// order each line
									if (edges[i].first.x > edges[i].second.x) {
										std::swap(edges[i].first.x, edges[i].second.x);
										std::swap(edges[i].first.y, edges[i].second.y);
									}
									if (edges[j].first.x > edges[j].second.x) {
										std::swap(edges[j].first.x, edges[j].second.x);
										std::swap(edges[j].first.y, edges[j].second.y);
									}

									// if two lines are apart, don't merge them.
									if (edges[i].first.x > edges[j].second.x) {
										if (glm::length(edges[i].first - edges[j].second) > maxLineGap) continue;
									}
									if (edges[j].first.x > edges[i].second.x) {
										if (glm::length(edges[i].second - edges[j].first) > maxLineGap) continue;
									}

									// merge two lines to the first line
									if (edges[j].first.x < edges[i].first.x) {
										edges[i].first = edges[j].first;
									}
									if (edges[j].second.x > edges[i].second.x) {
										edges[i].second = edges[j].second;
									}

									edges.erase(edges.begin() + j);
									erased = true;
								}
								else {	// vertical line
									// order each line
									if (edges[i].first.y > edges[i].second.y) {
										std::swap(edges[i].first.x, edges[i].second.x);
										std::swap(edges[i].first.y, edges[i].second.y);
									}
									if (edges[j].first.y > edges[j].second.y) {
										std::swap(edges[j].first.x, edges[j].second.x);
										std::swap(edges[j].first.y, edges[j].second.y);
									}

									// if two lines are apart, don't merge them.
									if (edges[i].first.y > edges[j].second.y) {
										if (glm::length(edges[i].first - edges[j].second) > maxLineGap) continue;
									}
									if (edges[j].first.y > edges[i].second.y) {
										if (glm::length(edges[i].second - edges[j].first) > maxLineGap) continue;
									}

									// merge two lines to the first line
									if (edges[j].first.y < edges[i].first.y) {
										edges[i].first = edges[j].first;
									}
									if (edges[j].second.y > edges[i].second.y) {
										edges[i].second = edges[j].second;
									}

									edges.erase(edges.begin() + j);
									erased = true;
								}
							}
						}
					}
				}
			}

			if (!erased) break;
		}
	}

	void cleanContours(std::vector<std::pair<glm::vec2, glm::vec2>>& edges, float maxLineGap, float theta) {
		if (edges.size() == 0) return;

		float dotTol = cosf(theta);

		std::vector<std::pair<glm::vec2, glm::vec2>> contour;
		std::vector<bool> used;
		for (int i = 0; i < edges.size(); ++i) {
			used.push_back(false);
		}

		contour.push_back(edges[0]);
		used[0] = true;
		int numRemainedEdges = edges.size() - 1;

		while (numRemainedEdges > 0) {
			float min_dist = std::numeric_limits<float>::max();
			int next = -1;

			// find the next edge
			for (int i = 0; i < edges.size(); ++i) {
				if (used[i]) continue;

				float dist1 = glm::length(contour.back().second - edges[i].first);
				float dist2 = glm::length(contour.back().second - edges[i].second);

				if (dist1 < min_dist && dist1 < dist2) {
					min_dist = dist1;
					next = i;
				}
				else if (dist2 < min_dist) {
					min_dist = dist2;
					next = i;
				}
			}

			if (glm::length(edges[next].first - contour.back().second) > glm::length(edges[next].second - contour.back().second)) {
				std::swap(edges[next].first.x, edges[next].second.x);
				std::swap(edges[next].first.y, edges[next].second.y);
			}

			if (glm::length(edges[next].first - contour.back().second) <= 3) {
				glm::vec2 midPt = (contour.back().second + edges[next].first) * 0.5f;
				contour.back().second = midPt;
				edges[next].first = midPt;
			}
			else if (glm::length(edges[next].first - contour.back().second) <= 10) {
				glm::vec2 dir = glm::normalize(edges[next].first - contour.back().second);
				if (fabs(glm::dot(glm::normalize(contour.back().second - contour.back().first), dir)) > 0.8) {
					contour.back().second = edges[next].first;
				}
				else if (fabs(glm::dot(glm::normalize(edges[next].second - edges[next].first), dir)) > 0.8) {
					edges[next].first = contour.back().second;
				}
				else {
					contour.push_back(std::make_pair(contour.back().second, edges[next].first));
				}
			}
			else if (glm::length(edges[next].first - contour.back().second) <= maxLineGap) {
				glm::vec2 dir = glm::normalize(edges[next].first - contour.back().second);
				if (fabs(glm::dot(glm::normalize(contour.back().second - contour.back().first), dir)) > dotTol) {
					contour.back().second = edges[next].first;
				}
				else if (fabs(glm::dot(glm::normalize(edges[next].second - edges[next].first), dir)) > dotTol) {
					edges[next].first = contour.back().second;
				}
				else {
					contour.push_back(std::make_pair(contour.back().second, edges[next].first));
				}
			}
			else {
				used[next] = true;
				numRemainedEdges--;
				continue;
			}

			contour.push_back(edges[next]);
			used[next] = true;
			numRemainedEdges--;
		}

		if (glm::length(contour.front().first - contour.back().second) <= 3) {
			glm::vec2 midPt = (contour.front().first + contour.back().second) * 0.5f;
			contour.front().first = midPt;
			contour.back().second = midPt;
		}
		else if (glm::length(contour.front().first - contour.back().second) <= 10) {
			glm::vec2 dir = glm::normalize(contour.front().first - contour.back().second);
			if (fabs(glm::dot(glm::normalize(contour.back().second - contour.back().first), dir)) > 0.8) {
				contour.back().second = contour.front().first;
			}
			else if (fabs(glm::dot(glm::normalize(contour.front().second - contour.front().first), dir)) > 0.8) {
				contour.front().first = contour.back().second;
			}
			else {
				contour.push_back(std::make_pair(contour.back().second, contour.front().first));
			}
		}
		else if (glm::length(contour.front().first - contour.back().second) <= maxLineGap) {
			glm::vec2 dir = glm::normalize(contour.front().first - contour.back().second);
			if (fabs(glm::dot(glm::normalize(contour.back().second - contour.back().first), dir)) > dotTol) {
				contour.back().second = contour.front().first;
			}
			else if (fabs(glm::dot(glm::normalize(contour.front().second - contour.front().first), dir)) > dotTol) {
				contour.front().first = contour.back().second;
			}
			else {
				contour.push_back(std::make_pair(contour.back().second, contour.front().first));
			}
		}

		edges = contour;
	}

	/**
	 * Make the image smaller while preserving the black lines.
	 */
	void resizeImage(cv::Mat& img, const cv::Size& size) {
		while (img.cols != size.width || img.rows != size.height) {
			cv::Size next_size(img.cols * 0.6, img.rows * 0.6);
			if (next_size.width < size.width) next_size.width = size.width;
			if (next_size.height < size.height) next_size.height = size.height;

			cv::resize(img, img, next_size);
			cv::threshold(img, img, 250, 255, cv::THRESH_BINARY);
		}
	}

	void blueImage(cv::Mat& img) {
		if (img.channels() == 1) {
			cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
		}

		for (int r = 0; r < img.rows; ++r) {
			for (int c = 0; c < img.cols; ++c) {
				cv::Vec3b color = img.at<cv::Vec3b>(r, c);
				if (color[0] < 128) {
					img.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 0, 0);
				}
				else {
					img.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 255, 255);
				}
			}
		}
	}

	void blendImages(cv::Mat& img1, const cv::Mat& img2, const cv::Scalar& transparent_color) {
		for (int r = 0; r < img1.rows; ++r) {
			for (int c = 0; c < img1.cols; ++c) {
				cv::Vec3b color = img1.at<cv::Vec3b>(r, c);

				if (color[0] == transparent_color[0] && color[1] == transparent_color[1] && color[2] == transparent_color[2]) {
					img1.at<cv::Vec3b>(r, c) = img2.at<cv::Vec3b>(r, c);
				}
			}
		}
	}

	/**
	 * Translate the image by offset_x along X axis and offset_y along Y axis.
	 */
	void translateImage(cv::Mat& img, int offset_x, int offset_y) {
		cv::Mat tmp = img.clone();
		img = cv::Mat(img.size(), img.type(), cv::Vec3b(255, 255, 255));

		// translate the image
		for (int r = 0; r < img.rows; ++r) {
			for (int c = 0; c < img.cols; ++c) {
				if (c + offset_x < 0 || c + offset_x >= img.cols) continue;
				if (r + offset_y < 0 || r + offset_y >= img.rows) continue;

				img.at<cv::Vec3b>(r + offset_y, c + offset_x) = tmp.at<cv::Vec3b>(r, c);
			}
		}
	}

	double deg2rad(double deg) {
		return deg / 180.0 * M_PI;
	}

	double rad2deg(double rad) {
		return rad / M_PI * 180.0;
	}

}