/*
 * BBox.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef BBOX_H_
#define BBOX_H_
#include "Misc.h"


/**
 * Generates a 2D box with that stretches from Point min(x,y) to Point max(x,y)
 */
class BBox {
private:
	Point min;
	Point max;
public:
	BBox();
	BBox(Point min, Point max);
	~BBox();

	//BBox& BBox::operator=( const BBox& other );
	BBox unionBBox(Point uPoint) const;
	BBox unionBBox(BBox uBox) const;
	BBox expandBBox(float expX, float expY) const;
	bool insideBBox(Point testPt) const;
	Point* getCorners() const;
	Point getMin() const;
	Point getMax() const;

};

#endif /* BBOX_H_ */
