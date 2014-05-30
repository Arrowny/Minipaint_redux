/*
 * Rectangle.h
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "object.h"

class Rectangle: public Object {

public:
	Rectangle();
	Rectangle(Point a, Point b)
	virtual ~Rectangle();
	void draw();
	void translate(float xTrans, float yTrans);
	Point* getCorners();
	bool inside(Point a);
	void update(Point a, Point b);
};

#endif /* RECTANGLE_H_ */
