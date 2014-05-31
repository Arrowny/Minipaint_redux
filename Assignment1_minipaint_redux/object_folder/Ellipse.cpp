/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"

#include "Misc.h"
#include "GL/gl.h"

namespace {

	//void GetMidPoint(BBox* bbox, Point start, Point end) {
	//	Point translate;
	//	Point midpoint = bbox->getMin;
	//
	//	float rx = abs(start.x - end.x) / 2;
	//	float ry = abs(start.y - end.y) / 2;
	//	translate.x = midpoint.x + rx;
	//	translate.y = midpoint.y + ry;
	//
	//}

	/**
	 * Draws 4 points on the canvas
	 *
	 * @param fourPoints four points of the object to be drawn.
	 */
	void drawFourPoints(vmath::vec4* fourPoints) {
		glBegin(GL_POINTS);
		glVertex2i(fourPoints[0][0], fourPoints[0][1]);
		glVertex2i(fourPoints[1][0], fourPoints[1][1]);
		glVertex2i(fourPoints[2][0], fourPoints[2][1]);
		glVertex2i(fourPoints[3][0], fourPoints[3][1]);
		glEnd();
	}

	vmath::vec4* FindPointOctant2(Point start_p, float rx, float ry, float rxSq, float rySq,
			float x, float y, float px, float py, float p) {

		//Region 1: 2nd Octant of 1st Quadrant
		vmath::vec4 fourPoints[4];

		p = rySq - (rxSq * ry) + (0.25 * rxSq);

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

		fourPoints[0] = new vmath::vec4(start_p.x + x, start_p.y + y, 0.0f, 1.0f);
		fourPoints[1] = new vmath::vec4(start_p.x - x, start_p.y + y, 0.0f, 1.0f);
		fourPoints[2] = new vmath::vec4(start_p.x + x, start_p.y - y, 0.0f, 1.0f);
		fourPoints[3] = new vmath::vec4(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		return fourPoints;

	}

	vmath::vec4* FindPointOctant1(Point start_p, float rx, float ry, float rxSq, float rySq,
			float x, float y, float px, float py, float p) {

		//Region 2: 1st Octant of 1st Quadrant
		vmath::vec4 fourPoints[4];

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

		fourPoints[0] = new vmath::vec4(start_p.x + x, start_p.y + y, 0.0f, 1.0f);
		fourPoints[1] = new vmath::vec4(start_p.x - x, start_p.y + y, 0.0f, 1.0f);
		fourPoints[2] = new vmath::vec4(start_p.x + x, start_p.y - y, 0.0f, 1.0f);
		fourPoints[3] = new vmath::vec4(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		return fourPoints;
	}

}

void Ellipse::draw() {

	Point A;
	Point B;
	vmath::vec4* ellPoints;
	vmath::vec4 vecX = (1.0f, 0.0f, 0.0f, 1.0f);
	vmath::vec4 vecY = (0.0f, 1.0f, 0.0f, 1.0f);

	vecX = vecX * transform->getScale();
	vecY = vecY * transform->getScale();

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	float rx = abs(start.x - end.x) / 2;
	float ry = abs(start.y - end.y) / 2;
	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0, y = ry, p;
	float px = 0, py = 2 * rxSq * y;

	p = rySq - (rxSq * ry) + (0.25 * rxSq);
	while (px < py) {
		ellPoints = FindPointOctant2(start, A.x, B.y, rxSq, rySq, x, y, px, py, p);
		ellPoints[0] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[1] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[2] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[3] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		drawFourPoints(ellPoints);
	}

	p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;
	while (y > 0) {
		ellPoints = FindPointOctant1(start, A.x, B.y, rxSq, rySq, x, y, px, py, p);
		ellPoints[0] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[1] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[2] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		ellPoints[3] = ellPoints[0]*transform->getTranslation()*transform->getRotation();
		drawFourPoints(ellPoints);
	}
}

Ellipse::Ellipse() {
	bbox = new bbox(0.0, 0.0);
	start.update(0.0, 0.0);
	float rx = 0.0;
	float ry = 0.0;
	transform = new Transformation(0.0, 0.0, 0.0, rx, ry);
}

Ellipse::Ellipse(Point ellStart, Point ellEnd) {

	start = ellStart;
	end = ellEnd;
	bbox = new bbox(ellStart, ellEnd);

	Point translate;
	Point midpoint = bbox->getMin;

	float rx = abs(ellStart.x - ellEnd.x) / 2;
	float ry = abs(ellStart.y - ellEnd.y) / 2;
	translate.x = midpoint.x + rx;
	translate.y = midpoint.y + ry;

	transform = new Transformation(0.0, translate.x, translate.y, rx, ry);

}

Ellipse::~Ellipse() {

}


void Ellipse::update(Point ellStart, Point ellEnd) {
	bbox = new bbox(ellStart, ellEnd);

}

void Ellipse::setTranslation(float rx, float ry) {

	transform->setTranslation(rx, ry);

}

void Ellipse::setRotation(float theta) {

	transform->setRotation(theta);

}

void Ellipse::setScale(float rx, float ry) {

	transform->setScale(rx, ry);

}

void Ellipse::getTranslation() {

	transform->getTranslation();

}

void Ellipse::getRotation() {

	transform->getRotation();

}

void Ellipse::getScale() {

	transform->getScale();

}
