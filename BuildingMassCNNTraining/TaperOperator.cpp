#include "TaperOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

	TaperOperator::TaperOperator(const std::string& height, const std::string& slope) {
		this->name = "taper";
		this->height = height;
		this->slope = slope;

		if (!utils::isNumber(height)) {
			this->params.push_back(height);
		}
		if (!utils::isNumber(slope)) {
			this->params.push_back(slope);
		}
	}

	boost::shared_ptr<Shape> TaperOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
		float actual_height = grammar.evalFloat(height, shape);
		float actual_slope = grammar.evalFloat(slope, shape);
	
		return shape->taper(shape->_name, actual_height, actual_slope);
	}

}
