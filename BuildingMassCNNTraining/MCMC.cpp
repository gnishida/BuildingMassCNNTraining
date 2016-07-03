#include "MCMC.h"
#include "CGA.h"
#include "Rectangle.h"
#include "GLUtils.h"
#include "GLWidget3D.h"
#include <QDir>
#include <time.h>
#include <QTextStream>

namespace mcmc {
	const float SIMILARITY_METRICS_ALPHA = 1000.0f;
	const float SIMILARITY_METRICS_BETA = 1000.0f;

	Chain::Chain(const cga::Grammar& grammar, float T) {
		this->grammar = grammar;
		this->T = T;

		// initialize the paramter values
		for (auto it = this->grammar.attrs.begin(); it != this->grammar.attrs.end(); ++it) {
			float range = it->second.range_end - it->second.range_start;
			it->second.value = std::to_string(range / 9.0f * (rand() % 10) + it->second.range_start);
		}
	}

	void Chain::generateProposal() {
		next_grammar = grammar;

		int resolution = 10;

		// next_grammarのパラメータ値を変更する
		for (auto it = next_grammar.attrs.begin(); it != next_grammar.attrs.end(); ++it) {
			float range = it->second.range_end - it->second.range_start;
			float unit = range / resolution;
			int index = std::max(0.0f, std::min((float)resolution, (std::stof(it->second.value) - it->second.range_start) / unit + 0.5f));
			//int index = (std::stof(it->second.value) - it->second.range_start) / unit;
			int r = rand() % 5;

			if (r == 0) {
				index = std::max(0, index - 1);
			}
			else if (r == 4) {
				index = std::min(resolution, index + 1);
			}

			it->second.value = std::to_string(unit * index + it->second.range_start);

			if (std::stof(it->second.value) > it->second.range_end) {
				int xxx = 0;
			}
		}
	}

	void Chain::update() {
		// update the best grammar
		if (next_E < best_E) {
			best_E = next_E;
			best_grammar = next_grammar;
		}

		// Metropolis
		float acceptance_ratio = std::min(1.0f, exp(-next_E/T) / exp(-E/T));
		if ((rand() % 100) / 100.0f < acceptance_ratio) {
			grammar = next_grammar;
			E = next_E;
		}

		// decrease T
		T = T / 1.00001f;
	}


	MCMC::MCMC(const QImage& target, GLWidget3D* glWidget, cga::Grammar grammar) {
		this->target = target;
		this->glWidget = glWidget;
		this->orig_grammar = grammar;

		cv::Mat grayImage = cv::Mat(this->target.height(), this->target.width(), CV_8UC4, this->target.bits(), this->target.bytesPerLine()).clone();
		
		// resize 1/4
		cv::cvtColor(grayImage, grayImage, CV_RGB2GRAY);
		cv::resize(grayImage, grayImage, cv::Size(grayImage.cols * 0.5, grayImage.rows * 0.5));
		cv::threshold(grayImage, grayImage, 250, 255, CV_THRESH_BINARY);
		cv::resize(grayImage, grayImage, cv::Size(grayImage.cols * 0.5, grayImage.rows * 0.5));
		cv::threshold(grayImage, grayImage, 250, 255, CV_THRESH_BINARY);

		// compute a distance map
		cv::distanceTransform(grayImage, targetDistMap, CV_DIST_L2, 3);

		////////////////////////////////////////////// DEBUG //////////////////////////////////////////////
		//cv::imwrite("results/targetDistMap.png", targetDistMap);
		////////////////////////////////////////////// DEBUG //////////////////////////////////////////////

		targetDistMap.convertTo(targetDistMap, CV_32F);
	}

	/**
	* MCMC
	*/
	void MCMC::run(int maxIterations) {
		if (!QDir("results_mcmc").exists()) {
			QDir().mkpath("results_mcmc");
		}

		time_t start = clock();

		float T = 1.0f;

		QFile file("results_mcmc/result.txt");
		file.open(QIODevice::WriteOnly);
		QTextStream out(&file);

		// initialize chain
		Chain chain(orig_grammar, 1.0f);
		chain.E = evaluate(render(chain.grammar), chain.grammar);
		chain.best_grammar = chain.grammar;
		chain.best_E = chain.E;

		for (int iter = 0; iter < maxIterations; ++iter) {
			chain.generateProposal();
			chain.next_E = evaluate(render(chain.next_grammar), chain.next_grammar);
			chain.update();

			SGD(chain, 24, 4);

			if ((iter + 1) % 1 == 0) {
				float best_E;
				QImage best_image;

				QImage image = target;
				QPainter painter(&image);
				painter.setOpacity(0.8);

				best_image = render(chain.best_grammar);
				best_E = chain.best_E;

				painter.drawImage(0, 0, best_image);

				QString filename = QString("results_mcmc/result_%1.png").arg(iter + 1);
				image.save(filename);

				std::cout << "--------------------------------------------------------" << std::endl;
				std::cout << "Iter: " << (iter + 1) << ", Best value: " << best_E << std::endl;
				time_t end = clock();
				std::cout << "Time elapsed: " << (double)(end - start) / CLOCKS_PER_SEC << "sec" << std::endl;

				out << (iter + 1) << "," << best_E << "\n";
			}

			////////////////////////////////////////////// DEBUG //////////////////////////////////////////////
			/*
			QString filename = QString("results_mcmc/result_%1.png").arg(iter);
			cv::Mat backMat = target.clone();
			QImage background(backMat.data, backMat.cols, backMat.rows, backMat.step, QImage::Format_RGB888);
			QPainter painter(&background);
			painter.setOpacity(0.8);
			painter.drawImage(0, 0, next_image);
			background.save(filename);
			*/
			////////////////////////////////////////////// DEBUG //////////////////////////////////////////////
		}

		file.close();

		time_t end = clock();
		std::cout << "Time elapsed: " << (double)(end - start) / CLOCKS_PER_SEC << "sec" << std::endl;

		float best_E;
		best_E = chain.best_E;
		render(chain.best_grammar);

		std::cout << "Best value: " << best_E << std::endl;
	}

	/**
	 *  現在のステートから、Stochastic gradient descentによる最適化
	 */
	void MCMC::SGD(Chain& chain, int maxIterations, int refineInterval) {
		int resolution = 10;

		int N = maxIterations / refineInterval + 1;
		int count = 0;
		for (int iter = 0; iter < N; ++iter) {
			for (int iter2 = 0; iter2 < refineInterval && count < maxIterations; ++iter2, ++count) {
				bool updated = false;

				for (int param_index = 0; param_index < chain.grammar.attrs.size(); ++param_index) {
					// next grammarの変更パラメータのiteratorを取得する
					cga::Grammar next_grammar = chain.grammar;
					auto param_it = next_grammar.attrs.begin();
					for (int k = 0; k < param_index; ++k) {
						param_it++;
					}

					// option 1
					float range = param_it->second.range_end - param_it->second.range_start;
					float unit = range / resolution;
					int index = std::min(9.0f, (std::stof(param_it->second.value) - param_it->second.range_start) / unit + 0.5f);
					//int index = (std::stof(param_it->second.value) - param_it->second.range_start + 0.5) / unit;
					param_it->second.value = std::to_string(unit * std::min(resolution, index + 1) + param_it->second.range_start);
					float next_E1 = evaluate(render(next_grammar), next_grammar);

					if (std::stof(param_it->second.value) > param_it->second.range_end) {
						int xxx = 0;
					}

					// option 2
					param_it->second.value = std::to_string(unit * std::max(0, index - 1) + param_it->second.range_start);
					float next_E2 = evaluate(render(next_grammar), next_grammar);

					if (next_E1 < chain.E && next_E1 < next_E2) {
						param_it->second.value = std::to_string(unit * std::min(resolution, index + 1) + param_it->second.range_start);
						chain.grammar = next_grammar;
						chain.E = next_E1;
						if (next_E1 < chain.best_E) {
							chain.best_grammar = next_grammar;
							chain.best_E = next_E1;
						}
						updated = true;
					}
					else if (next_E2 < chain.E && next_E2 < next_E1) {
						param_it->second.value = std::to_string(unit * std::max(0, index - 1) + param_it->second.range_start);
						chain.grammar = next_grammar;
						chain.E = next_E2;
						if (next_E2 < chain.best_E) {
							chain.best_grammar = next_grammar;
							chain.best_E = next_E2;
						}
						updated = true;
					}
					else {
						// no update
					}
				}

				// 更新がないなら、終了
				if (!updated) break;
			}

			// increase the resolution
			resolution *= 2;
		}

		///////////////// DEBUG //////////////////////////////////////////
		for (auto it = chain.best_grammar.attrs.begin(); it != chain.best_grammar.attrs.end(); ++it) {
			std::cout << it->second.value << ",";
		}
		std::cout << endl;
	}

	/**
	 * Parallel Tempering
	 */
	void MCMC::runPT(int maxIterations) {
		if (!QDir("results_mcmc").exists()) {
			QDir().mkpath("results_mcmc");
		}

		time_t start = clock();

		cga::Grammar current_grammar = orig_grammar;
		float T = 1.0f;

		QFile file("results_mcmc/result.txt");
		file.open(QIODevice::WriteOnly);
		QTextStream out(&file);
		
		// initialize chain
		Chain chain1(orig_grammar, 1.0f);
		chain1.E = evaluate(render(chain1.grammar), chain1.grammar);
		chain1.best_grammar = chain1.grammar;
		chain1.best_E = chain1.E;

		Chain chain2(orig_grammar, 2.0f);
		chain2.E = evaluate(render(chain2.grammar), chain2.grammar);
		chain2.best_grammar = chain2.grammar;
		chain2.best_E = chain2.E;

		for (int iter = 0; iter < maxIterations; ++iter) {
			cga::Grammar next_grammar = current_grammar;

			// next_grammarのパラメータ値を変更する
			chain1.generateProposal();
			chain1.next_E = evaluate(render(chain1.next_grammar), chain1.next_grammar);
			chain1.update();
	
			chain2.generateProposal();
			chain2.next_E = evaluate(render(chain2.next_grammar), chain2.next_grammar);
			chain2.update();

			if ((iter + 1) % 100 == 0) {
				float best_E;
				QImage best_image;

				if (chain1.best_E < chain2.best_E) {
					best_image = render(chain1.best_grammar);
					best_E = chain1.best_E;
					best_image = render(chain1.best_grammar);
				}
				else {
					best_image = render(chain2.best_grammar);
					best_E = chain2.best_E;
					best_image = render(chain2.best_grammar);
				}

				QString filename = QString("results_mcmc/result_%1.png").arg(iter + 1);
				best_image.save(filename);

				std::cout << "--------------------------------------------------------" << std::endl;
				std::cout << "Iter: " << (iter + 1) << ", Best value: " << best_E << std::endl;
				time_t end = clock();
				std::cout << "Time elapsed: " << (double)(end - start) / CLOCKS_PER_SEC << "sec" << std::endl;

				out << (iter + 1) << "," << best_E << "\n";
			}

			////////////////////////////////////////////// DEBUG //////////////////////////////////////////////
			/*
			QString filename = QString("results_mcmc/result_%1.png").arg(iter);
			cv::Mat backMat = target.clone();
			QImage background(backMat.data, backMat.cols, backMat.rows, backMat.step, QImage::Format_RGB888);
			QPainter painter(&background);
			painter.setOpacity(0.8);
			painter.drawImage(0, 0, next_image);
			background.save(filename);
			*/
			////////////////////////////////////////////// DEBUG //////////////////////////////////////////////
		}

		file.close();

		time_t end = clock();
		std::cout << "Time elapsed: " << (double)(end - start) / CLOCKS_PER_SEC << "sec" << std::endl;

		float best_E;
		if (chain1.best_E < chain2.best_E) {
			best_E = chain1.best_E;
			render(chain1.best_grammar);
		}
		else {
			best_E = chain2.best_E;
			render(chain2.best_grammar);
		}
		
		std::cout << "Best value: " << best_E << std::endl;
	}

	QImage MCMC::render(cga::Grammar& grammar) {
		// run the derivation
		cga::CGA cga;
		boost::shared_ptr<cga::Shape> axiom = boost::shared_ptr<cga::Shape>(new cga::Rectangle("Start", "", glm::translate(glm::rotate(glm::mat4(), -3.141592f * 0.5f, glm::vec3(1, 0, 0)), glm::vec3(-0.5, -0.5, 0)), glm::mat4(), 1, 1, glm::vec3(1, 1, 1)));
		cga.stack.push_back(axiom);
		cga.derive(grammar, true);

		// render the image
		std::vector<boost::shared_ptr<glutils::Face> > faces;
		cga.generateGeometry(faces);
		glWidget->renderManager.removeObjects();
		glWidget->renderManager.addFaces(faces, false);
		glWidget->render();

		return glWidget->grabFrameBuffer();
	}

	float MCMC::evaluate(QImage& image, cga::Grammar& grammar) {
		// convert to gray scale image
		cv::Mat sourceImage = cv::Mat(image.height(), image.width(), CV_8UC4, image.bits(), image.bytesPerLine()).clone();
		cv::Mat mat;
		cv::cvtColor(sourceImage, mat, CV_RGB2GRAY);

		// resize the image
		if (targetDistMap.cols < 512) {
			float scale = 512.0f / image.width();
			cv::resize(mat, mat, cv::Size(image.width() * scale, image.height() * scale));
			cv::threshold(mat, mat, 250, 255, CV_THRESH_BINARY);
		}
		cv::resize(mat, mat, cv::Size(targetDistMap.cols, targetDistMap.rows));
		cv::threshold(mat, mat, 250, 255, CV_THRESH_BINARY);

		// compute a distance map
		cv::Mat distMap;
		cv::distanceTransform(mat, distMap, CV_DIST_L2, 3);

		float dist = distance(distMap, targetDistMap, SIMILARITY_METRICS_ALPHA, SIMILARITY_METRICS_BETA);
		float align = 0;// alignCost(grammar);
		

		return dist + align * 0.05;
	}

	float MCMC::alignCost(cga::Grammar& grammar) {
		float diff = std::min(1.0f, fabs(std::stof(grammar.attrs["xx_0"].value) - std::stof(grammar.attrs["x_1"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["xx_2"].value) - std::stof(grammar.attrs["x_3"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["x_0"].value) - std::stof(grammar.attrs["x_2"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["x_1"].value) - std::stof(grammar.attrs["x_3"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["xx_0"].value) - std::stof(grammar.attrs["xx_2"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["xx_1"].value) - std::stof(grammar.attrs["xx_3"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["y_0"].value) - std::stof(grammar.attrs["y_1"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["yy_0"].value) - std::stof(grammar.attrs["yy_1"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["yy_0"].value) - std::stof(grammar.attrs["y_2"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["yy_1"].value) - std::stof(grammar.attrs["y_3"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["y_2"].value) - std::stof(grammar.attrs["y_3"].value)));
		diff += std::min(1.0f, fabs(std::stof(grammar.attrs["yy_2"].value) - std::stof(grammar.attrs["yy_3"].value)));

		return diff;
	}

	float distance(const cv::Mat& distMap, const cv::Mat& targetDistMap, float alpha, float beta) {
		float dist1 = 0.0f;
		float dist2 = 0.0f;

		for (int r = 0; r < distMap.rows; ++r) {
			for (int c = 0; c < distMap.cols; ++c) {
				if (targetDistMap.at<float>(r, c) == 0) {
					dist1 += distMap.at<float>(r, c);
				}
				if (distMap.at<float>(r, c) == 0) {
					dist2 += targetDistMap.at<float>(r, c);
				}
			}
		}

		// 画像サイズに基づいて、normalizeする
		float Z = distMap.rows * distMap.cols * (distMap.rows + distMap.cols) * 0.5;
		dist1 /= Z;
		dist2 /= Z;

		float dist = alpha * dist1 + beta * dist2;

		return dist;
		//return expf(-dist / T);

	}
}