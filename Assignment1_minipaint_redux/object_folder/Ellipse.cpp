/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"

//#include "Misc.h"
//#include "GL/gl.h"
//#include "vmath.h"
//#include "BBox.h"

/////////////////////////////////////////////////////////////////Namespace/////////////////////////////////////////////////////////////////

//Helper Functions

namespace {

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

	/**Find out the points needed to be drawn on 2nd Octant of 1st Quadrant
	 * using Ellipse Midpoint Algorithm
	 *
	 * The variables below are passed from the main draw function:-
	 *
	 * @param start_p
	 * @param rx
	 * @param ry
	 * @param rxSq
	 * @param rySq
	 * @param x
	 * @param y
	 * @param px
	 * @param py
	 * @param p
	 * @return
	 */
	vmath::vec4* FindPointOctant2(Point start_p, float rx, float ry, float rxSq, float rySq,
			float x, float y, float px, float py, float p) {

		vmath::Tvec4<float> fourPoints[4];

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

		fourPoints[0][0] = start_p.x + x;
		fourPoints[0][1] = start_p.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[1][0] = start_p.x - x;
		fourPoints[1][1] = start_p.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[2][0] = start_p.x + x;
		fourPoints[2][1] = start_p.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[3][0] = start_p.x - x;
		fourPoints[3][1] = start_p.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		return fourPoints;

	}

	/**Find out the points needed to be drawn on 1st Octant of 1st Quadrant
	 * using Ellipse Midpoint Algorithm
	 *
	 * The variables below are passed from the main draw function:-
	 *
	 * @param start_p
	 * @param rx
	 * @param ry
	 * @param rxSq
	 * @param rySq
	 * @param x
	 * @param y
	 * @param px
	 * @param py
	 * @param p
	 * @return
	 */
	vmath::vec4* FindPointOctant1(Point start_p, float rx, float ry, float rxSq, float rySq,
			float x, float y, float px, float py, float p) {

		vmath::Tvec4<float> fourPoints[4];

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

		fourPoints[0][0] = start_p.x + x;
		fourPoints[0][1] = start_p.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[1][0] = start_p.x - x;
		fourPoints[1][1] = start_p.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[2][0] = start_p.x + x;
		fourPoints[2][1] = start_p.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[3][0] = start_p.x - x;
		fourPoints[3][1] = start_p.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		return fourPoints;
	}

	/**Adds points that are obtained from the FindOctant functions to a vector to be returned
	 *
	 * @param fourPoints vector of points that are obtained
	 * @param ellColor struct with glColor3f information
	 * @param ellPointColor struct to be inserted with point and color information
	 * @param PointColorVec	vector with collection of point and color information
	 */
	void pushtoVector(vmath::vec4* fourPoints, Color ellColor, PointAndColor ellPointColor, std::vector<PointAndColor> PointColorVec, Point tmpPoint)
	{
		tmpPoint.x = fourPoints[0][0];
		tmpPoint.y = fourPoints[0][1];
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[1][0];
		tmpPoint.y = fourPoints[1][1];
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[2][0];
		tmpPoint.y = fourPoints[2][1];
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[3][0];
		tmpPoint.y = fourPoints[3][1];
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		PointColorVec.push_back(ellPointColor);

	}

	/**The rest of the transformations needed to put the points in the correct position
	 *
	 * @param fourPoints vector of points that are obtained
	 * @param transform pointer to transformation function
	 * @return
	 */
	vmath::vec4* partialTransform(vmath::vec4* fourPoints, Transformation* transform)
	{
		fourPoints[0] = fourPoints[0]*transform->getRotation()*transform->getTranslation();
		fourPoints[1] = fourPoints[1]*transform->getRotation()*transform->getTranslation();
		fourPoints[2] = fourPoints[2]*transform->getRotation()*transform->getTranslation();
		fourPoints[3] = fourPoints[3]*transform->getRotation()*transform->getTranslation();

		return fourPoints;
	}

}

/////////////////////////////////////////////////////////////////End_Namespace/////////////////////////////////////////////////////////////////

//Constructors & Destructor

/** Default constructor for ellipse
 *
 */
Ellipse::Ellipse() {
	Point A;
	Point B;
	A.x = A.y = B.x = B.y = 0.0;

	BBox bbox(A, B);
	start.update(0.0, 0.0);
	float rx = 0.0;
	float ry = 0.0;
	transform = new Transformation(0.0, 0.0, 0.0, rx, ry);
}

/**Constructor for ellipse with a specified start and end point
 *
 * @param ellStart (x,y) coordinates of Start point
 * @param ellEnd (x,y) coordinates of End point
 */
Ellipse::Ellipse(Point ellStart, Point ellEnd) {

	start = ellStart;
	end = ellEnd;
	BBox bbox(ellStart, ellEnd);

	Point midpoint;
	Point minimum = bbox.getMin();

	float rx = abs(ellEnd.x - ellStart.x) / 2;
	float ry = abs(ellEnd.y - ellStart.y) / 2;
	midpoint.x = minimum.x + rx;
	midpoint.y = minimum.y + ry;

	transform = new Transformation(0.0, midpoint.x, midpoint.y, rx, ry);

}

/**Destructor for ellipse
 *
 */
Ellipse::~Ellipse() {

}

//Functions

/**Draws Ellipse with parameters specified in the constructor
 *
 */
std::vector<PointAndColor> Ellipse::draw() {

	Point A;
	Point B;
	Point tmpPoint;
	Color ellColor;
	ellColor.red = 0.0f;
	ellColor.green = 0.0f;
	ellColor.blue = 0.0f;

	PointAndColor ellPointColor(tmpPoint, ellColor);

	std::vector<PointAndColor> PointColorVec;
	vmath::vec4* ellPoints;
	vmath::vec4 vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::vec4 vecY(0.0f, 1.0f, 0.0f, 1.0f);

	vecX = vecX * transform->getScale();
	vecY = vecY * transform->getScale();

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	float rx = abs(A.x - B.x) / 2;
	float ry = abs(A.y - B.y) / 2;
	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0, y = ry, p;
	float px = 0, py = 2 * rxSq * y;

	//Region 1: 2nd Octant of 1st Quadrant
	p = rySq - (rxSq * ry) + (0.25 * rxSq);
	while (px < py) {

		//Transforming and plotting the points to where they should be
		ellPoints = FindPointOctant2(start, rx, ry, rxSq, rySq, x, y, px, py, p);
		ellPoints = partialTransform(ellPoints, transform);

		//Pushing the point and color information into the vector
		pushtoVector(ellPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

		//Draw the points
		drawFourPoints(ellPoints);

	}

	//Region 2: 1st Octant of 1st Quadrant
	p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;
	while (y > 0) {

		//Transforming and plotting the points to where they should be
		ellPoints = FindPointOctant1(start, rx, ry, rxSq, rySq, x, y, px, py, p);
		ellPoints = partialTransform(ellPoints, transform);

		//Pushing the point and color information into the vector
		pushtoVector(ellPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

		//Draw the points
		drawFourPoints(ellPoints);
	}

	return PointColorVec;
}

void Ellipse::update(Point ellStart, Point ellEnd) {
	BBox bbox(ellStart, ellEnd);

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
