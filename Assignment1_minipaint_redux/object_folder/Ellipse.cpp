/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"

#include "Misc.h"
#include "GL/gl.h"

Ellipse::Ellipse() {
	bbox = new bbox(0.0, 0.0);
	start.update(0.0, 0.0);
	float rx = 0.0;
	float ry = 0.0;
	vmath::mat4 Trans = new Transformation(0.0, 0.0, 0.0, 0.0, 0.0);
}

Ellipse::Ellipse(Point ellStart, Point ellEnd) {
	ellStart = start;
	ellEnd = end;
	bbox = new bbox(ellStart, ellEnd);
	float rx = abs(ellStart.x - ellEnd.x) / 2;
	float ry = abs(ellStart.x - ellEnd.x) / 2;
	transform = new Transformation(0.0, 0.0, 0.0, ellStart, ellEnd);
}

Ellipse::~Ellipse() {

}

namespace {

/**
 * Draws 4 points on the canvas
 *
 * @param start_p starting point
 * @param x	x-coordinate
 * @param y y-coordinate
 */
void FourPointSymmetry(Point start_p, float x, float y) {
	glBegin(GL_POINTS);
	glVertex2i(start_p.x + x, start_p.y + y);
	glVertex2i(start_p.x - x, start_p.y + y);
	glVertex2i(start_p.x + x, start_p.y - y);
	glVertex2i(start_p.x - x, start_p.y - y);
	glEnd();
}

void Ellipse::draw(Point start_p, float rx, float ry) {
	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0, y = ry, p;
	float px = 0, py = 2 * rxSq * y;

	//Region 1
	p = rySq - (rxSq * ry) + (0.25 * rxSq);

	while (px < py) {
		FourPointSymmetry(start_p, x, y);

		x++;
		px = px + 2 * rySq;

		if (p < 0) {
			p = p + rySq + px;
		}

		else {
			y--;
			py = py - 2 * rxSq;
			p = p + rySq + px - py;
		}

	}

	//Region 2
	p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;

	while (y > 0) {
		FourPointSymmetry(start_p, x, y);

		y--;
		py = py - 2 * rxSq;

		if (p > 0) {
			p = p + rxSq - py;
		}

		else {
			x++;
			px = px + 2 * rySq;
			p = p + rxSq - py + px;
		}

	}

}

<<<<<<< HEAD
void Ellipse::update(Point ellStart, Point ellEnd)
{
	bbox = new bbox(ellStart,ellEnd);
=======
void Ellipse::update(Point ellStart, Point ellEnd) {
	bbox = new bbox(ellStart, ellEnd);

>>>>>>> origin/Joe
}
