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
	virtual ~Rectangle();
	void draw(Point start_p, Point end_p);
};

#endif /* RECTANGLE_H_ */
