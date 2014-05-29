/*
 * Circle.cpp
 *
<<<<<<< HEAD
 *  Created on: 2014Äê5ÔÂ27ÈÕ
=======
 *  Created on: 05/29/2014
>>>>>>> ca1f7edfe47a1cfe6a467b8cdb923ce761ee8c6c
 *      Author: yellow
 */

#include "Circle.h"

<<<<<<< HEAD
//Circle::Circle() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Circle::~Circle() {
//	// TODO Auto-generated destructor stub
//}
namespace{
/**
 *
 * @param change_p:
 * @param start_p:click position on the screen
 */
void DrawEightSymmetricPoint(Point change_p, Point start_p){
	glBegin(GL_POINTS);
	glVertex2f(start_p.x+change_p.x, start_p.y+change_p.y);
	glVertex2f(start_p.x-change_p.x, start_p.y+change_p.y);
	glVertex2f(start_p.x-change_p.x, start_p.y-change_p.y);
	glVertex2f(start_p.x+change_p.x, start_p.y-change_p.y);
	glVertex2f(start_p.x+change_p.y, start_p.y+change_p.x);
	glVertex2f(start_p.x-change_p.y, start_p.y+change_p.x);
	glVertex2f(start_p.x-change_p.y, start_p.y-change_p.x);
	glVertex2f(start_p.x+change_p.y, start_p.y-change_p.x);
	glEnd();
}
}


/**
 * This function use Mid-point circle algorithm to draw a circle
 *
 * @param start_p: click position on the screen
 * @param r: radius of the circle
 * @change_p:
 */
void Circle(Point start_p, float r) {
	Point change_p;
	change_p.x=0;
	change_p.y=r;
	float p=1.25-r;
	while (change_p.x<=change_p.y) {
		DrawEightSymmetricPoint( change_p, start_p);
		if (p<0) { //mid-point is inside the circle
			++change_p.x;
			p+=2*change_p.x+1;
		}else {// mid point is outside the circle
			p+=2*change_p.x-2*change_p.y+5;
			++change_p.x;
			--change_p.y;
		}
=======
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
>>>>>>> ca1f7edfe47a1cfe6a467b8cdb923ce761ee8c6c
	}
}


