#pragma once

#include <opencv2/opencv.hpp>
#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Shape.h"
#include "Grammar.h"
#include <QImage>

class GLWidget3D;
class RenderManager;

namespace mcmc {
	class Chain {
	public:
		cga::Grammar grammar;
		QImage image;
		float E;
		float T;

		cga::Grammar next_grammar;
		QImage next_image;
		float next_E;

		cga::Grammar best_grammar;
		float best_E;

	public:
		Chain(const cga::Grammar& grammar, float T);
		void generateProposal();
		void update();
	};

	class MCMC {
	private:
		QImage target;
		cv::Mat targetDistMap;
		GLWidget3D* glWidget;
		cga::Grammar orig_grammar;

	public:
		MCMC(const QImage& target, GLWidget3D* glWidget, cga::Grammar grammar);

		void run(int maxIterations);
		void SGD(Chain& chain, int maxIterations, int refineInterval);
		void runPT(int maxIterations);
		QImage render(cga::Grammar& gramamr);
		float evaluate(QImage& image, cga::Grammar& grammar);
		float alignCost(cga::Grammar& grammar);
	};

	float distance(const cv::Mat& distMap, const cv::Mat& targetDistMap, float alpha, float beta);
}