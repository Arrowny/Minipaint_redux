/*
 * Object.cpp
 *
 *  Created on: 2014��5��27��
 *      Author: yellow
 */

#include "Object.h"

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
