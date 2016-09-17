#include "ExtrudeOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

ExtrudeOperator::ExtrudeOperator(const std::string& height) {
	this->name = "extrude";
	this->height = height;

	if (!utils::isNumber(height)) {
		this->params.push_back(height);
	}
}

boost::shared_ptr<Shape> ExtrudeOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
	float actual_height = grammar.evalFloat(height, shape);

	return shape->extrude(shape->_name, actual_height);
}

}
