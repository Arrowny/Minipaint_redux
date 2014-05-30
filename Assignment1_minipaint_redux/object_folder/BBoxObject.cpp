/*
 * Rectangle.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include <BBox.h>
#include <GL/gl.h>
#include <Misc.h>
#include <BBoxObject.h>

/**
 * default constructor sets min and max vertex to: minVert(0.0,0.0), maxVert(0.0,0.0).
 */
BBoxObject::BBoxObject() {

	bbox = new BBox();
}

BBoxObject::BBoxObject(Point a, Point b) {
	bbox = new BBox(a, b);
}

BBoxObject::~BBoxObject() {

}

void BBoxObject::draw() {
	Point start_p = bbox->getMin();
	Point end_p = bbox->getMax();

	glBegin(GL_LINES);
	glVertex2f(start_p.x, start_p.y);
	glVertex2f(end_p.x, start_p.y);
	glVertex2f(end_p.x, start_p.y);
	glVertex2f(end_p.x, end_p.y);
	glVertex2f(end_p.x, end_p.y);
	glVertex2f(start_p.x, end_p.y);
	glVertex2f(start_p.x, end_p.y);
	glVertex2f(start_p.x, start_p.y);
	glEnd();
}

/**
 * returns the 4 vertices representing the 4 corners of the Rectangle. Corners are inserted
 * into a Point array in the following order: [0]bottom-left, [1]bottom-right, [2]top-right, [3] top-left.
 *
 * @return Point array representing 4 corners of Rectangle's bounding box
 */
Point* BBoxObject::getCorners() {
	return bbox->getCorners();
}

/**
 * Const function tests whether or not a Point "testPt" is within the Rectangle's bounding box
 *
 * @param testPt Point to test insidedness on bounding box.
 * @return boolean representing whether or not Point is inside Rectangle's bounding box
 */
bool BBoxObject::inside(Point a) {
	return bbox->insideBBox(a);
}

/**
 * translates Rectangle based on x translate and y translate
 *
 * @param xTrans x translation
 * @param yTrans y translation
 */
void BBoxObject::translate(float xTrans, float yTrans) {
	Point tmpMin = bbox->getMin();
	Point tmpMax = bbox->getMax();

	//TODO if add addition/ addition assignment operator to misc allows update code
	//TODO if add subtraction/ subtraction assignment operator to misc update code
	tmpMin.x += xTrans; tmpMin.y = yTrans;
	tmpMax.x += xTrans; tmpMax.y = yTrans;

	updateBBox(tmpMin,tmpMax);
}

/**
 * Sets up a rectangle based on the two points a and b.
 *
 * @param a
 * @param b
 */
void BBoxObject::update(Point a, Point b) {
	updateBBox(a,b);
}
