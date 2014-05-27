/*
 * Circle.cpp
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#include "Circle.h"

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
	}
}


