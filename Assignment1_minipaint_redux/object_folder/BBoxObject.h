/*
 * Rectangle.h
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "object.h"

class BBoxObject: public Object {

public:
	BBoxObject();
	BBoxObject(Point a, Point b);

	BBoxObject(BBox newBBox);
	virtual ~BBoxObject();
	std::vector<PointAndColor> draw();
	Point* getCorners();
	bool inside(Point a);
	void update(Point a, Point b);
};

#endif /* RECTANGLE_H_ */
