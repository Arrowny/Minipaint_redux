/*
 * BBox.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef BBOX_H_
#define BBOX_H_
#include "Misc.h"
#include "Transformation.h"
#include "vmath.h"


/**
 * Generates a 2D box with that streches from Point min(x,y) to Point max(x,y). And rocksteady.
 */
class BBox {

private:
	Transformation* transform;
	Point* min;
	Point* max;

public:

	BBox();
	BBox(Point min, Point max);
	~BBox();
	BBox unionBBox(Point uPoint);
	BBox unionBBox(BBox uBox);
	BBox expandBBox(float expX, float expY);
	bool insideBBox(Point testPt);
	Point* getCorners();
	Point getMax();
	Point getMin();
	void print();
};

#endif /* BBOX_H_ */
