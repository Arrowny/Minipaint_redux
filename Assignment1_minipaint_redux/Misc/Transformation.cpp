/*
 * Transformation.cpp
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#include <Transformation.h>

Transformation::Transformation() {
	Translation.identity();
	Rotation.identity();
	Scale.identity();
	Transform.identity();
}

Transformation::Transformation(float theta, float xTrans, float yTrans, float xScale, float yScale) {
	Translation = vmath::translate(theta, xTrans, 0.0f);
	Rotation = vmath::scale(xScale, yScale, 0.0 );
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

