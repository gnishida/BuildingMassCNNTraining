#include "ShapeUOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

	ShapeUOperator::ShapeUOperator(const Value& frontWidth, const Value& backDepth) {
		this->name = "shapeU";
		this->frontWidth = frontWidth;
		this->backDepth = backDepth;

		if (!utils::isNumber(frontWidth.value)) {
			this->params.push_back(frontWidth.value);
		}
		if (!utils::isNumber(backDepth.value)) {
			this->params.push_back(backDepth.value);
		}
	}

	boost::shared_ptr<Shape> ShapeUOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
		float actual_frontWidth;
		float actual_backDepth;

		if (frontWidth.type == Value::TYPE_RELATIVE) {
			actual_frontWidth = shape->_scope.x * grammar.evalFloat(frontWidth.value, shape);
		}
		else {
			actual_frontWidth = shape->_scope.x * grammar.evalFloat(frontWidth.value, shape);
		}

		if (backDepth.type == Value::TYPE_RELATIVE) {
			actual_backDepth = shape->_scope.y * grammar.evalFloat(backDepth.value, shape);
		}
		else {
			actual_backDepth = shape->_scope.y * grammar.evalFloat(backDepth.value, shape);
		}

		return shape->shapeU(shape->_name, actual_frontWidth, actual_backDepth);
	}

}
