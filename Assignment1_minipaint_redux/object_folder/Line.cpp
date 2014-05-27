/*
 * Line.cpp
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#include "Line.h"

//Line::Line() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Line::~Line() {
//	// TODO Auto-generated destructor stub
//}
namespace{
/**
 * This function defines the way to draw lines according to the slop, which equals to dy/dx.
 *
 * @param slop : the slop of the line, here we use it as a parameter to judge the situation.
 * @param larger: if dx >= dy, larger = dx; if dy > dx, larger = dy;
 * @param smaller:if dx >= dy, smaller = dy; if dy > dx, smaller = dx;
 * @param start_p : the start point.
 * @param end_p : the end point.
 */
void DrawLine(int slop,float larger, float smaller, Point start_p, Point end_p){
	float increase;
	if(slop==1){
		increase=(smaller!=0?smaller/(end_p.y-start_p.y):0);
	}
	else if(slop==2){
		increase=(smaller!=0?smaller/(end_p.x-start_p.x):0);
	}
	float p=2*smaller-larger;
	float dE=2*smaller;
	float dNE=2*(smaller-larger);
	float x=start_p.x, y=start_p.y;
	if(slop==1){
		for (x=start_p.x+1; x<=end_p.x; ++x) {
			if (p<0) {
				glVertex2f(x, y);
				p+=dE;
			}else {
				y+=increase;
				glVertex2f(x, y);
				p+=dNE;
			}
		}
	}
	else if (slop==2){
		for (y=start_p.y+1; y<=end_p.y; ++y) {
			if (p<0) {
				glVertex2f(x, y);
				p+=dE;
			}else {
				y+=increase;
				glVertex2f(x, y);
				p+=dNE;
			}
		}
	}
}
}

/**
 *  This function use Breseman algorithm to draw lines.
 *
 * @param start_p: the start point
 * @param end_p: the end point
 */
void Line(Point start_p, Point end_p) {
	glBegin(GL_POINTS);
	if (start_p.x=end_p.x && start_p.y=end_p.y)
	{
		glVertex2i(start_p.x, start_p.y);
		return;
	}
	if (start_p.x>end_p.x) {
		std::swap(start_p.x, end_p.x);
		std::swap(start_p.y, end_p.y);
	}
	//glVertex2d(start_p.x, start_p.y);

	float dy=abs(end_p.y-start_p.y);
	float dx=abs(end_p.x-start_p.x);
	if (dx>=dy) {// slop <=1
		int slop=1;

		DrawLine(slop,dx,dy, start_p, end_p);

//		float incy=(dy!=0?dy/(end_p.y-start_p.y):0);
//		float p=2*dy-dx;
//		float dy2=2*dy;
//		float dd2=2*(dy-dx);
//		float x, y=start_p.y;
//		for (x=start_p.x+1; x<=end_p.x; ++x) {
//			if (p<0) {
//				glVertex2f(x, y);
//				p+=dy2;
//			}else {
//				y+=incy;
//				glVertex2f(x, y);
//				p+=dd2;
//			}
//		}
	}else { //slop>1
		int slop=2;
		if (start_p.y>end_p.y) {
			std::swap(start_p.x, end_p.x);
			std::swap(start_p.y, end_p.y);
		}

		DrawLine(slop,dy,dx,start_p, end_p);

//		float incx=(dx!=0?dx/(end_p.x-start_p.x):0);
//		float p=2*dx-dy;
//		float dx2=2*dx;
//		float dd2=2*(dx-dy);
//		float x=start_p.x, y;
//		for (y=start_p.y+1; y<=end_p.y; ++y) {
//			if (p<0) {
//				glVertex2f(x, y);
//				p+=dx2;
//			}else {
//				x+=incx;
//				glVertex2f(x, y);
//				p+=dd2;
//			}
//		}
	}
	glEnd();
}


