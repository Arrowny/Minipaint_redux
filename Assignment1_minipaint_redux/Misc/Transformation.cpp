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
	Translation = vmath::translate(xTrans, yTrans, 0.0f);
	Rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	Scale = vmath::scale(xScale, yScale, 0.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

/**
 * sets the rotation matrix of transformation.
 *
 * @param theta rotation of 2d point
 */
void Transformation::setRotation(float theta) {
	Rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;
}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::mat4 Transformation::getRotation() {
	return Rotation;
}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::mat4 Transformation::getTransformation() {
	return Transform;
}

