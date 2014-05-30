/*
 * Rectangle.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include <BBox.h>
#include <GL/gl.h>
#include <Misc.h>
#include <Rectangle.h>

/**
 * default constructor sets min and max vertex to: minVert(0.0,0.0), maxVert(0.0,0.0).
 */
Rectangle::Rectangle() {
	bbox = new BBox(0.0, 0.0);
}

Rectangle::Rectangle(Point a, Point b) {
	bbox = new BBox(a, b);
}

Rectangle::~Rectangle() {

}

void Rectangle::draw() {
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
Point* Rectangle::getCorners() {
	return bbox->getCorners();
}

/**
 * Const function tests whether or not a Point "testPt" is within the Rectangle's bounding box
 *
 * @param testPt Point to test insidedness on bounding box.
 * @return boolean representing whether or not Point is inside Rectangle's bounding box
 */
bool Rectangle::inside(Point a) {
	return bbox->insideBBox(a);
}

/**
 * translates Rectangle based on x translate and y translate
 *
 * @param xTrans x translation
 * @param yTrans y translation
 */
void Rectangle::translate(float xTrans, float yTrans) {
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
void Rectangle::update(Point a, Point b) {
	updateBBox(a,b);
}
