/*
 * Line.cpp
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#include "Line.h"

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
void DrawLine(int line_type, float larger, float smaller, Point start_p,
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

} //namespace

Line::Line() {
	start.update(0.0, 0.0);
	end.update(0.0, 0.0);
}

Line::Line(Point lineStart, Point lineEnd) {
	start = lineStart;
	end = lineEnd;
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

	Point start_p = start;
	Point end_p = end;

	glBegin (GL_POINTS);
	float dy = abs(end_p.y - start_p.y);
	float dx = abs(end_p.x - start_p.x);
	if (dx >= dy) { // slop <=1
		int line_type = 1;
		DrawLine(line_type, dx, dy, start_p, end_p);

	} else { //slop>1
		int line_type = 2;
		if (start_p.y > end_p.y) {
			SwapPoints(start_p, end_p);
		}
		DrawLine(line_type, dy, dx, start_p, end_p);
	}
	glEnd();
}

