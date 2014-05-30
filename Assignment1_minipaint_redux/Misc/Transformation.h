/*
 * Transformation.h
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "vmath.h"

class Transformation {
private:
	vmath::mat4 Translation;
	vmath::mat4 Rotation;
	vmath::mat4 Scale;
	vmath::mat4 Transformation;
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
