/*
 * Object.cpp
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#include <Object.h>

Object::Object() {
	// TODO Auto-generated constructor stub

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

/**
 * protected function: updates bbox based on point a and b.
 *
 * @param a
 * @param b
 */
void Object::updateBBox(Point a, Point b) {
	bbox = new BBox(a,b);
}

/**
 * Const function tests whether or not a Point "testPt" is within the BBox's bounding box
 *
 * @param Pt Point to test insidedness on
 * @return boolean representing whether or not Point is inside BBox's bounding box
 */
bool Object::inside(Point Pt){

	return bbox->insideBBox(Pt);
}

BBox Object::getBBox(){

	return *bbox;
}
