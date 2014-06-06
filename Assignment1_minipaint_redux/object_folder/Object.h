/*
 * Object.h
 *
 *  Created on: 2014��5��27��
 *      Author: yellow
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "BBox.h"
#include "Misc.h"
#include "Transformation.h"

class Object {

protected:
	BBox* bbox;
	Transformation* transform;
	void updateBBox(Point a, Point b);

public:
	Object();
	virtual ~Object();

	/**
	 * object draw function. Draws object to screen
	 */
	virtual std::vector<PointAndColor> draw() = 0;

	/**
	 * Moves object across screen.
	 */
	virtual void setTranslation(float xTrans, float yTrans) = 0;

	/**
	 * Rotate objects in a direction
	 */
	virtual void setRotation(float theta) = 0;

	/**
	 * Increase/Decrease size of an object
	 */
	virtual void setScale(float xScale, float yScale) = 0;

	/**
	 * gets matrix of each transformation.
	 *
	 * @return 4x4 matrix representing transformation/translation/rotation/scale matrix of transformation.
	 * Note: this transformation requires that points be represented in the form
	 * 		 [x,y,0.0f,1.0f].
	 */
	vmath::mat4 getTransformation();
	vmath::mat4 getTranslation();
	vmath::mat4 getRotation();
	vmath::mat4 getScale();

	bool inside(Point Pt);
};

#endif /* OBJECT_H_ */
