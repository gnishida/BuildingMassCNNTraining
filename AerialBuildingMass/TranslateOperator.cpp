#include "TranslateOperator.h"
#include "CGA.h"
#include "Shape.h"
#include "Utils.h"

namespace cga {

TranslateOperator::TranslateOperator(int mode, int coordSystem, const Value& x, const Value& y, const Value& z) {
	this->name = "translate";
	this->mode = mode;
	this->coordSystem = coordSystem;
	this->x = x;
	this->y = y;
	this->z = z;

	if (!utils::isNumber(x.value)) {
		this->params.push_back(x.value);
	}
	if (!utils::isNumber(y.value)) {
		this->params.push_back(y.value);
	}
	if (!utils::isNumber(z.value)) {
		this->params.push_back(z.value);
	}
}

boost::shared_ptr<Shape> TranslateOperator::apply(boost::shared_ptr<Shape>& shape, const Grammar& grammar, std::list<boost::shared_ptr<Shape> >& stack) {
	float actual_x;
	float actual_y;
	float actual_z;

	if (x.type == Value::TYPE_RELATIVE) {
		actual_x = shape->_scope.x * grammar.evalFloat(x.value, shape);
	} else {
		actual_x = grammar.evalFloat(x.value, shape);
	}

	if (y.type == Value::TYPE_RELATIVE) {
		actual_y = shape->_scope.y * grammar.evalFloat(y.value, shape);
	} else {
		actual_y = grammar.evalFloat(y.value, shape);
	}

	if (z.type == Value::TYPE_RELATIVE) {
		actual_z = shape->_scope.z * grammar.evalFloat(z.value, shape);
	} else {
		actual_z = grammar.evalFloat(z.value, shape);
	}

	shape->translate(mode, coordSystem, actual_x, actual_y, actual_z);
	return shape;
}

}