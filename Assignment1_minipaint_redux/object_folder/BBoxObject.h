/*
 * Rectangle.h
 *
 *  Created on: 2014��5��29��
 *      Author: yellow
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "object.h"

class BBoxObject: public Object {

public:
	BBoxObject();
	BBoxObject(Point a, Point b)
	virtual ~BBoxObject();
	void draw();
	void translate(float xTrans, float yTrans);
	Point* getCorners();
	bool inside(Point a);
	void update(Point a, Point b);
};

#endif /* RECTANGLE_H_ */