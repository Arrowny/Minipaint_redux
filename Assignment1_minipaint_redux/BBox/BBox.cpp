/*
 * BBox.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */


#include "BBox.h"

namespace {

	/**
	 * Sets the min and max x value for BBox based on points a and b.
	 *
	 * @param a first point
	 * @param b second point
	 * @param min pointer to the address of Point min for bbox
	 * @param max pointer to the address of Point max for bbox
	 * @return void
	 */
	void setMinMaxX(Point a, Point b, Point &min, Point &max) {
		if (a.x <= b.x) {
			min.x = a.x;
			max.x = b.x;
		} else {
			min.x = b.x;
			max.x = a.x;
		}
	}

	/**
	 * Sets the min and max y value for BBox based on points a and b.
	 *
	 * @param a first point
	 * @param b second point
	 * @param min pointer to the address of Point min for bbox
	 * @param max pointer to the address of Point max for bbox
	 * @return void
	 */
	void setMinMaxY(Point a, Point b, Point &min, Point &max) {
		if (a.y <= b.y) {
			min.y = a.y;
			max.y = b.y;
		} else {
			min.y = b.y;
			max.y = a.y;
		}
	}

	/**
	 * Finds minimum of uMin and min sets this value into tmpMin.
	 *
	 * @param uMin
	 * @param min
	 * @param tmpMin Point that will contain the minimum (x,y) coordinate
	 */
	void findMinOfUnionedBBox(Point uMin, Point min, Point &tmpMin) {
		if(uMin.x > min.x) 	{ tmpMin.x = min.x; }
		else 				{ tmpMin.x = uMin.x;}
		if(uMin.y > min.y) 	{ tmpMin.y = min.y; }
		else				{ tmpMin.y = uMin.y;}
	}

	/**
	 * Finds the maximum of uMax and max sets this value into tmpMin.
	 *
	 * @param uMax
	 * @param max
	 * @param tmpMax Point that will contain the maximum 9x,y) coordinate
	 */
	void findMaxOfUnionedBBox(Point uMax, Point max, Point &tmpMax) {
		if(uMax.x < max.x) 	{ tmpMax.x = max.x; }
		else				{ tmpMax.x = uMax.x;}
		if(uMax.y < max.y) 	{ tmpMax.y = max.y; }
		else				{ tmpMax.y = uMax.y;}
	}
}

/**
 * Basic BBox constructor. Sets bounding box to impossible values Max: (-1.0, -1.0
 * Min: (0.0, 0.0). This ensures that inside test will fail if performed on default BBox.
 */
BBox::BBox() {
	min.update(0.0,0.0);
	max.update(-1.0,-1.0);
}

/**
 * BBox constructor that takes two input points. Will create a
 * bounding box "BBox" based on the minimum and maximum Points (x,y) of a and b.
 *
 * @param a first input point
 * @param b second input point
 */
BBox::BBox(Point a, Point b) {
	setMinMaxX(a, b, min, max);
	setMinMaxY(a, b, min, max);
}

BBox::~BBox() {

}

/**
 * Union input bounding box with a Point.
 *
 * @param uPoint point to be unioned with this BBox's bounding box
 * @return new BBox representing the union of this BBox's bounding box with point uPoint
 */
BBox BBox::unionBBox(Point uPoint) const{
	Point tmpMin;
	Point tmpMax;

	findMinOfUnionedBBox(uPoint, min, tmpMin);
	findMaxOfUnionedBBox(uPoint, max, tmpMax);

	BBox tmpBox(tmpMin, tmpMax);
	return tmpBox;
}

/**
 * Union input bounding box with bounding box of this BBox.
 *
 * @param uBox input bounding box to union with this bounding box
 * @return unioned bounding box
 */
BBox BBox::unionBBox(BBox uBox) const{
	Point uMin = uBox.getMin();
	Point uMax = uBox.getMax();
	Point tmpMin;
	Point tmpMax;

	//find extents of unioned BBox
	findMinOfUnionedBBox(uMin, min, tmpMin);
	findMaxOfUnionedBBox(uMax, max, tmpMax);

	BBox tmpBox(tmpMin, tmpMax);
	return tmpBox;
}

/**
 * Return a BBox with a bounding box expanded in the x axis by expX and expanded in the y axis
 * by expY.
 *
 * @param expX expansion in the x axis
 * @param expY expansion in the y axis
 * @return new expanded bounding box
 */
BBox BBox::expandBBox(float expX, float expY) const{
	Point tmpMin = min;
	Point tmpMax = max;

	tmpMin.x -= expX; tmpMax.x += expX;
	tmpMin.y -= expY; tmpMax.y += expY;

	BBox tmpBox(tmpMin, tmpMax);
	return tmpBox;
}

/**
 * Const function tests whether or not a Point "testPt" is within the BBox's bounding box
 *
 * @param testPt Point to test insidedness on
 * @return boolean representing whether or not Point is inside BBox's bounding box
 */
bool BBox::insideBBox(Point testPt) const {

	if(	testPt.x <= max.x &&
		testPt.x >= min.x &&
		testPt.y <= max.y &&
		testPt.y >= min.y	)
		{return true;}

	return false;
}

/**
 * returns the 4 vertices representing the 4 corners of the BBox's bounding box. Corners are inserted
 * into a Point array in the following order: [0]bottom-left, [1]bottom-right, [2]top-right, [3] top-left.
 *
 * @return Point array representing 4 corners of BBox's bounding box
 */
Point* BBox::getCorners() const {
	Point corners[4];

	corners[0].update(min.x,min.y);
	corners[1].update(max.x,min.y);
	corners[2].update(max.x,max.y);
	corners[3].update(min.x,max.y);

	return corners;
}

/**
 *
 * @return copy of min for this BBox's bounding box.
 */
Point BBox::getMin() const {

	Point tmpMin;
	tmpMin.x = min.x;
	tmpMin.y = min.y;
	return tmpMin;
}

/**
 *
 * @return copy of max for this BBox's bounding box.
 */
Point BBox::getMax() const {
	Point tmpMax;
	tmpMax.x = max.x;
	tmpMax.y = max.y;
	return tmpMax;
}

