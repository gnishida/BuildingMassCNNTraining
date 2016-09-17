#include "ShapeLOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

	ShapeLOperator::ShapeLOperator(const Value& frontWidth, const Value& leftWidth) {
		this->name = "shapeL";
		this->frontWidth = frontWidth;
		this->leftWidth = leftWidth;

		if (!utils::isNumber(frontWidth.value)) {
			this->params.push_back(frontWidth.value);
		}
		if (!utils::isNumber(leftWidth.value)) {
			this->params.push_back(leftWidth.value);
		}
	}

	boost::shared_ptr<Shape> ShapeLOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
		float actual_frontWidth;
		float actual_leftWidth;

		if (frontWidth.type == Value::TYPE_RELATIVE) {
			actual_frontWidth = shape->_scope.x * grammar.evalFloat(frontWidth.value, shape);
		}
		else {
			actual_frontWidth = shape->_scope.x * grammar.evalFloat(frontWidth.value, shape);
		}

		if (leftWidth.type == Value::TYPE_RELATIVE) {
			actual_leftWidth = shape->_scope.y * grammar.evalFloat(leftWidth.value, shape);
		}
		else {
			actual_leftWidth = shape->_scope.y * grammar.evalFloat(leftWidth.value, shape);
		}

		return shape->shapeL(shape->_name, actual_frontWidth, actual_leftWidth);
	}

}
