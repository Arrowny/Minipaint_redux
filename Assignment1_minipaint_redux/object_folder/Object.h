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

class Object {
private:
	BBox* bbox;
	virtual BBox updateBBox() = 0;
public:
	Object();
	virtual ~Object();
	virtual void draw() = 0;
	virtual void translate() = 0;
};

#endif /* OBJECT_H_ */
