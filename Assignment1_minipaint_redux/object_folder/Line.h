/*
 * Line.h
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#ifndef LINE_H_
#define LINE_H_

#include "Object.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>


class Line: public virtual Object {
public:
	Line();
	virtual ~Line();
};

#endif /* LINE_H_ */
