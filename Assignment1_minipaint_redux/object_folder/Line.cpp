/*
 * Line.cpp
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#include "Line.h"
#include <math.h>
#define PI 3.14159265

namespace {

/**
 * This function defines the way to draw lines according to the slop, which equals to dy/dx.
 *
 * @param slop : the slop of the line, here we use it as a parameter to judge the situation.
 * @param larger: the larger one between dx and dy.
 * @param smaller:the smaller one between dx and dy
 * @param start_p : the start point.
 * @param end_p : the end point.
 */
void BresenhamLine(int line_type, float larger, float smaller, Point start_p,
		Point end_p) {
	if (line_type == 1) {
		float incy = (smaller != 0 ? smaller / (end_p.y - start_p.y) : 0);
		float p = 2 * smaller - larger;
		float dy2 = 2 * smaller;
		float dd2 = 2 * (smaller - larger);
		float x, y = start_p.y;
		for (x = start_p.x + 1; x <= end_p.x; ++x) {
			if (p < 0) {
				glVertex2f(x, y);
				p += dd2;
			} else {
				y += incy;
				glVertex2f(x, y);
				p += dd2;
			}
		}
	} else if (line_type == 2) {
		float incx = (smaller != 0 ? smaller / (end_p.x - start_p.x) : 0);
		float p = 2 * smaller - larger;
		float dx2 = 2 * smaller;
		float dd2 = 2 * (smaller - larger);
		float x = start_p.x, y;
		for (y = start_p.y + 1; y <= end_p.y; ++y) {
			if (p < 0) {
				glVertex2f(x, y);
				p += dd2;
			} else {
				x += incx;
				glVertex2f(x, y);
				p += dd2;
			}
		}
	}

}

/**
 * This function is used to swap the coordinates of start point and end point
 *
 * @param start_p: start point
 * @param end_p: end point
 */
void SwapPoints(Point &start_p, Point &end_p) {
	std::swap(start_p.x, end_p.x);
	std::swap(start_p.y, end_p.y);
}
void exchangePoints(Point &old_point, Point &new_point){
	old_point.x=new_point.x;
	old_point.y=new_point.y;
}

}//namespace


Line::Line() {
	start.update(0.0f, 0.0f);
	end.update(0.0f, 0.0f);

	bbox = new BBox( start, end);
	transform = new Transformation(0.0f,0.0f,0.0f,0.0f,0.0f);

}

Line::Line(Point lineStart, Point lineEnd) {
	start = lineStart;
	end = lineEnd;

	bbox = new BBox( start, end);

	Point translate;
	Point scale;
	float rotate;

	translate.x = (start.x + end.x)/2;
	translate.y = (start.y + end.y)/2;

	scale.x = sqrt(pow(translate.x, 2.0) + pow(translate.y , 2.0));
	scale.y = scale.x;

	float ry = (end.y - start.x)/2;
	float rx = (end.x - start.x)/2;
	rotate = acos (rx/scale.x) * 180.0 / PI;
	transform = new Transformation(rotate, translate.x, translate.y, scale.x, scale.y);
}

Line::~Line() {

}

/**
 *  This function judges the type of the line first and then use Breseman algorithm to draw lines.
 *
 * @param start_p: the start point
 * @param end_p: the end point
 */
void Line::draw() {

	Point start_p ;
	Point end_p ;
	start_vec.Tvec4(-1.0f , 0.0f, 0.0f, 1.0f);
	end_vec.Tvec4(1.0f, 0.0f, 0.0f, 1.0f);

	start_vec = start_vec * transform ->getScale() * transform ->getTranslation() * transform ->getRotation();
	end_vec = end_vec * transform ->getScale() * transform ->getTranslation() * transform ->getRotation();

	start_p.x = start_vec[0];
	start_p.y = start_vec[1];
	end_p.x = end_vec[0];
	end_p.y = end_vec[1];

	glBegin (GL_POINTS);
	float dy = abs(end_p.y - start_p.y);
	float dx = abs(end_p.x - start_p.x);
	if (dx >= dy) { // slop <=1
		int line_type = 1;
		BresenhamLine(line_type, dx, dy, start_p, end_p);

	} else { //slop>1
		int line_type = 2;
		if (start_p.y > end_p.y) {
			SwapPoints(start_p, end_p);
		}
		BresenhamLine(line_type, dy, dx, start_p, end_p);
	}
	glEnd();

}

/**
 * This getStart is used to get the position of the start point of the line.
 *
 */
Point Line::getStart(){
	start.printP();
	return start;
}

/**
 * This getEnd is used to get the position of the end point of the line.
 * @return
 */
Point Line::getEnd(){
	end.printP();
	return end;
}

/**
 * This setStart is used to set the new start point of the line, and then update the bounding box.
 * @param new_start
 */
void Line::setStart(Point new_start){
	start = new_start;
	//exchangePoints(start, new_start);
	updateBBox(start,end);
}

/**
 * This setEnd is used to set the new end point of the current line, and then update the bounding box
 * @param new_end
 */
void Line::setEnd(Point new_end){
	end=new_end;
	//exchangePoints(end, new_end);
	updateBBox(start,end);
}

/**
 * Moves object across screen.
 */
void Line::setTranslation(float xTrans, float yTrans){
	transform -> setTranslation(xTrans, yTrans);

}

/**
 * Rotate objects in a direction
 */
void Line::setRotation(float theta){
	transform -> setRotation(theta);
}

/**
 * Increase/Decrease size of an object
 */
void Line::setScale(float xScale, float yScale){
	transform -> setScale(xScale, yScale);
}

/**
 * gets matrix of each transformation.
 *
 * @return 4x4 matrix representing transformation/translation/rotation/scale matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
void Line::getTransformation(){
	transform -> getTransformation();
}
void Line::getTranslation(){
	transform -> getTranslation();
}
void Line::getRotation(){
	transform -> getRotation();
}
void Line::getScale(){
	transform -> getScale();
}
