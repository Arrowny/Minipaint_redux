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
	virtual void draw() = 0;

	/**
	 * Moves object across screen.
	 */
	virtual void translate() = 0;
};

#endif /* OBJECT_H_ */
