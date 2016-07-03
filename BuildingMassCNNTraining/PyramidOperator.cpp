#include "PyramidOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

	PyramidOperator::PyramidOperator(const std::string& height) {
		this->name = "pyramid";
		this->height = height;

		if (!utils::isNumber(height)) {
			this->params.push_back(height);
		}
	}

	boost::shared_ptr<Shape> PyramidOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
		float actual_height = grammar.evalFloat(height, shape);

		return shape->pyramid(shape->_name, actual_height);
	}

}
