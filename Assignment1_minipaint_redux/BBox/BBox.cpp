/*
 * BBox.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#include "BBox.h"

namespace {

	/**
	 * Sets the min and max y value for BBox based on points a and b
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
	 * Sets the min and max y value for BBox based on points a and b
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
}

BBox::BBox() {
	this->min.x = 0; this->max.x = 0;
	this->min.y = 0; this->min.y = 0;
}

/**
 * Basic bounding box constructor that takes two input points. Will create a
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

