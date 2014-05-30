/*
 * Transformation.h
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "vmath.h"

/**
 * Provides support for 2d transformations.
 */
class Transformation {
private:
	vmath::Tmat4<float> Translation;
	vmath::Tmat4<float> Rotation;
	vmath::Tmat4<float> Scale;
	vmath::Tmat4<float> Transform;
public:
	Transformation();
	Transformation(float theta, float xTrans, float yTrans, float xScale, float yScale);
	virtual ~Transformation();
	void setRotation(float theta);
	void setTranslation(float xTrans, float yTrans);
	void setScale(float xScale, float yScale);
	vmath::mat4 getTransformation();
	vmath::mat4 getTranslation();
	vmath::mat4 getRotation();
	vmath::mat4 getScale();
};

#endif /* TRANSFORMATION_H_ */
