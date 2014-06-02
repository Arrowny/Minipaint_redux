/*
 * Transformation.h
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "vmath.h"
#include "Misc.h"

/**
 * Provides support for 2d transformations.
 */
class Transformation {
private:
	vmath::Tmat4<float> translation;
	vmath::Tmat4<float> rotation;
	vmath::Tmat4<float> scale;
	vmath::Tmat4<float> transform;
	vmath::Tmat4<float> invTransform;
	vmath::Tmat4<float> setInvTransform();

public:
	Transformation();
	Transformation(float theta, float xTrans, float yTrans, float xScale, float yScale);
	virtual ~Transformation();
	void setRotation(float theta);
	void setTranslation(float xTrans, float yTrans);
	void setScale(float xScale, float yScale);
	vmath::Tmat4<float> getTransformation();
	vmath::Tmat4<float> getInverseTransformation();
	vmath::Tmat4<float> getTranslation();
	vmath::Tmat4<float> getRotation();
	vmath::Tmat4<float> getScale();
	Point worldtoObj(Point worldPoint);
	Point objToWorld(Point worldPoint);
	void print();
};

#endif /* TRANSFORMATION_H_ */
