/*
 * Ellipse.h
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "object.h"

class Ellipse: public Object {
public:
	Ellipse();
	virtual ~Ellipse();
	void draw(Point start_p, float rx, float ry);
};

#endif /* ELLIPSE_H_ */
