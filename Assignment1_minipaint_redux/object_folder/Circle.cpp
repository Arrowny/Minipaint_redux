/*
 * Circle.cpp
 *
 *  Created on: 05/29/2014
 *      Author: yellow
 */

#include "Circle.h"

Circle::Circle() {
	// TODO Auto-generated constructor stub

}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

namespace {
/**
 * Use 8 pints symmetry algorithm to draw the symmetric points according to one point we already know.
 *
 * @param start_p
 * @param x
 * @param y
 */
void EightPointSymmetry(Point start_p, float x, float y){
	glBegin(GL_POINTS);
	glVertex2f(start_p.x+x, start_p.y+y);
	glVertex2f(start_p.x-x, start_p.y+y);
	glVertex2f(start_p.x-x, start_p.y-y);
	glVertex2f(start_p.x+x, start_p.y-y);
	glVertex2f(start_p.x+y, start_p.y+x);
	glVertex2f(start_p.x-y, start_p.y+x);
	glVertex2f(start_p.x-y, start_p.y-x);
	glVertex2f(start_p.x+y, start_p.y-x);
	glEnd();
}
/**
 * Midpoint circle algorithm
 * @param p: decision factor
 * @param x
 * @param y
 */
void MidPointCircle(float p, float x, float y){
	if (p<0) {
		++x;
		p+=2*x+1;
	}else {
		p+=2*x-2*y+5;
		++x;
		--y;
	}
}
}
/**
 *
 * @param start_p: the starting point where we click
 * @param r: the radius of the circle
 */
void circle(Point start_p, float r) {
	float x=0.0, y=r;
	float p=1.25-r;
	while (x<=y) {
		EightPointSymmetry(start_p, x, y);
		MidPointCircle(p,x,y);
	}
}


