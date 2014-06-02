/*
 * Object.h
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
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
};

#endif /* OBJECT_H_ */
