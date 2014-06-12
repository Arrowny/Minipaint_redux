/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

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
	vmath::Tvec4<float>* FindPointOctant2(Point start_p, float rx, float ry, float rxSq, float rySq,
			float x, float y, float px, float py, float p) {

		vmath::Tvec4<float> fourPoints[4];

		p = rySq - (rxSq * ry) + (0.25 * rxSq);

		x+=1.0f;
		px = px + 2.0f * rySq;

		if (p < 0) {
			p = p + rySq + px;
		}

		else {
			y-=1.0f;
			py = py - 2.0f * rxSq;
			p = p + rySq + px - py;
		}

		fourPoints[0][0] = start_p.x + x;
		fourPoints[0][1] = start_p.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;
		std::cout<<"fourPoints1 = "<<fourPoints[0][0]<<","<<fourPoints[0][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[1][0] = start_p.x - x;
		fourPoints[1][1] = start_p.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;
		std::cout<<"fourPoints2 = "<<fourPoints[1][0]<<","<<fourPoints[1][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[2][0] = start_p.x + x;
		fourPoints[2][1] = start_p.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;
		std::cout<<"fourPoints3 = "<<fourPoints[2][0]<<","<<fourPoints[2][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[3][0] = start_p.x - x;
		fourPoints[3][1] = start_p.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;
		std::cout<<"fourPoints4 = "<<fourPoints[3][0]<<","<<fourPoints[3][1]<<std::endl;
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

		y-=1.0f;
		py = py - 2.0f * rxSq;

		if (p > 0) {
			p = p + rxSq - py;
		}

		else {
			x+=1.0f;
			px = px + 2.0f * rySq;
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
	void pushtoVector(vmath::Tvec4<float>* fourPoints, Color ellColor, PointAndColor ellPointColor, std::vector<PointAndColor> PointColorVec, Point tmpPoint)
	{
		tmpPoint.x = fourPoints[0][0];
		tmpPoint.y = fourPoints[0][1];
		std::cerr<<"tmpPoint = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		std::cout<<"PointColorVec1 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[1][0];
		tmpPoint.y = fourPoints[1][1];
		std::cerr<<"tmpPoint2 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		std::cout<<"PointColorVec2 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[2][0];
		tmpPoint.y = fourPoints[2][1];
		std::cerr<<"tmpPoint3 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		std::cout<<"PointColorVec3 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[3][0];
		tmpPoint.y = fourPoints[3][1];
		std::cerr<<"tmpPoint4 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
		std::cout<<"PointColorVec4 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

	}

	/**The rest of the transformations needed to put the points in the correct position
	 *
	 * @param fourPoints vector of points that are obtained
	 * @param transform pointer to transformation function
	 * @return
	 */
	vmath::Tvec4<float>* partialTransform(vmath::Tvec4<float>* fourPoints, Transformation transform)
	{
		fourPoints[0] = fourPoints[0]*transform.getRotation()*transform.getTranslation();
		fourPoints[1] = fourPoints[1]*transform.getRotation()*transform.getTranslation();
		fourPoints[2] = fourPoints[2]*transform.getRotation()*transform.getTranslation();
		fourPoints[3] = fourPoints[3]*transform.getRotation()*transform.getTranslation();
		std::cout<<"TfourPoints1 = "<<fourPoints[0][0]<<","<<fourPoints[0][1]<<std::endl;
		std::cout<<"TfourPoints2 = "<<fourPoints[1][0]<<","<<fourPoints[1][1]<<std::endl;
		std::cout<<"TfourPoints3 = "<<fourPoints[2][0]<<","<<fourPoints[2][1]<<std::endl;
		std::cout<<"TfourPoints4 = "<<fourPoints[3][0]<<","<<fourPoints[3][1]<<std::endl;

		return fourPoints;
	}

}

/////////////////////////////////////////////////////////////////End_Namespace/////////////////////////////////////////////////////////////////

//Constructors & Destructor

/** Default constructor for ellipse
 *
 */
drawableEllipse::drawableEllipse() {

	bbox = new BBox();
	transform = new Transformation();
}

/**Constructor for ellipse with a specified start and end point
 *
 * @param ellStart (x,y) coordinates of Start point
 * @param ellEnd (x,y) coordinates of End point
 */
drawableEllipse::drawableEllipse(Point ellCenter, Point ellRad) {

	float rx = fabs(ellRad.x - ellCenter.x) / 2.0f;
	float ry = fabs(ellRad.y - ellCenter.y) / 2.0f;

	start.x = ellCenter.x - rx;
	start.y = ellCenter.y - ry;
	end.x = rx + ellCenter.x;
	end.y = ry + ellCenter.y;

	//bbox = new BBox(ellStart, ellEnd);

	//Point midpoint;
	Point minimum = bbox->getMin();

	midpoint.x = minimum.x + rx;
	midpoint.y = minimum.y + ry;

	transform = new Transformation(0.0f, ellCenter.x, ellCenter.y, ellRad.x, ellRad.y);

	std::vector<PointAndColor> boundaryPACs = this->draw();
	BBox newBBox;
	for(int ii = 0; ii < boundaryPACs.size(); ii++) {
		newBBox = newBBox.unionBBox(boundaryPACs[ii].point);
	}
	bbox = new BBox(newBBox.getMin(), newBBox.getMax());

//	Point A, B;
//	Point magRx, magRy;
//	Point midpoint;
//	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
//	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);
//
//	vecX = vecX * transform->getScale();
//	vecY = vecY * transform->getScale();
//
//	if(vecX[0] > vecY[1])
//	{
//		magRx.x = vecX[0];
//		magRx.y = 0.0f;
//		magRy.x = 0.0f;
//		magRy.y = vecX[0];
//
//	}
//	else
//	{
//		magRx.x = vecY[1];
//		magRx.y = 0.0f;
//		magRy.x = 0.0f;
//		magRy.y = vecY[1];
//
//	}
//
//	vecX = vecX * transform->getRotation() * transform->getTranslation();
//	vecY = vecY * transform->getRotation() * transform->getTranslation();
//
//	midpoint.x = vecX[0] - magRx.x;
//	midpoint.y = vecY[1] - magRy.y;
//	vecX = vecX * transform->getScale();
//	vecY = vecY * transform->getScale();
//
//	A.x = vecX[0];
//	A.y = vecX[1];
//	B.x = vecY[0];
//	B.y = vecY[1];
//
//	A.x = magRx.x + midpoint.x;
//	A.y = magRx.x + midpoint.y;
//	B.x = -(magRx.x - midpoint.x);
//	B.y = -(magRx.x - midpoint.y);
//	start = A;
//	end = B;
//
//	bbox = new BBox(A, B);
}

/**Destructor for ellipse
 *
 */
drawableEllipse::~drawableEllipse() {

}

//Functions

/**Draws Ellipse with parameters specified in the constructor
 *
 */
std::vector<PointAndColor> drawableEllipse::draw() {

	Point A;
	Point B;
	Point tmpPoint;
	Color ellColor;
	ellColor.red = 0.0f;
	ellColor.green = 0.0f;
	ellColor.blue = 0.0f;

	PointAndColor ellPointColor(tmpPoint, ellColor);

	std::vector<PointAndColor> PointColorVec;
	vmath::Tvec4<float>* ellPoints;
	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);

	vecX = vecX * transform->getScale();
	vecY = vecY * transform->getScale();

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	start.x = A.y;
	start.y = B.x;
	end = B;

	float rx = A.x;
	float ry = B.y;
//	float rx = fabs(A.x - B.x) / 2.0f;
//	float ry = fabs(A.y - B.y) / 2.0f;

	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0.0f, y = ry, p;
	float px = 0.0f, py = 2.0f * rxSq * y;

	//Region 1: 2nd Octant of 1st Quadrant
	p = rySq - (rxSq * ry) + (0.25f * rxSq);

	while (px < py) {

//		Transforming and plotting the points to where they should be
//		ellPoints = FindPointOctant2(start, rx, ry, rxSq, rySq, x, y, px, py, p);
//		ellPoints = partialTransform(ellPoints, *transform);

		vmath::Tvec4<float> fourPoints[4];

		fourPoints[0][0] = start.x + x;
		fourPoints[0][1] = start.y + y;
		fourPoints[0][2] = 0.0f;
		fourPoints[0][3] = 1.0f;

		fourPoints[1][0] = start.x - x;
		fourPoints[1][1] = start.y + y;
		fourPoints[1][2] = 0.0f;
		fourPoints[1][3] = 1.0f;

		fourPoints[2][0] = start.x + x;
		fourPoints[2][1] = start.y - y;
		fourPoints[2][2] = 0.0f;
		fourPoints[2][3] = 1.0f;

		fourPoints[3][0] = start.x - x;
		fourPoints[3][1] = start.y - y;
		fourPoints[3][2] = 0.0f;
		fourPoints[3][3] = 1.0f;

		fourPoints[0] = fourPoints[0]*transform->getRotation()*transform->getTranslation();
		fourPoints[1] = fourPoints[1]*transform->getRotation()*transform->getTranslation();
		fourPoints[2] = fourPoints[2]*transform->getRotation()*transform->getTranslation();
		fourPoints[3] = fourPoints[3]*transform->getRotation()*transform->getTranslation();

		//Pushing the point and color information into the vector
		//pushtoVector(fourPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

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

		//Find the next point

		x+=1.0f;
		px = px + 2.0f * rySq;

		if (p < 0) {
			p = p + rySq + px;
		}

		else {
			y-=1.0f;
			py = py - 2.0f * rxSq;
			p = p + rySq + px - py;
		}

	}

	//Region 2: 1st Octant of 1st Quadrant
	p = rySq * (x + 0.5f) * (x + 0.5f) + rxSq * (y - 1.0f) * (y - 1.0f) - rxSq * rySq;

	while (y > 0) {

		//Transforming and plotting the points to where they should be
		//ellPoints = FindPointOctant1(start, rx, ry, rxSq, rySq, x, y, px, py, p);
		//ellPoints = partialTransform(ellPoints, *transform);
		vmath::Tvec4<float> fourPoints[4];

		fourPoints[0][0] = start.x + x;
		fourPoints[0][1] = start.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;

		fourPoints[1][0] = start.x - x;
		fourPoints[1][1] = start.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;

		fourPoints[2][0] = start.x + x;
		fourPoints[2][1] = start.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;

		fourPoints[3][0] = start.x - x;
		fourPoints[3][1] = start.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;

		fourPoints[0] = fourPoints[0]*transform->getRotation()*transform->getTranslation();
		fourPoints[1] = fourPoints[1]*transform->getRotation()*transform->getTranslation();
		fourPoints[2] = fourPoints[2]*transform->getRotation()*transform->getTranslation();
		fourPoints[3] = fourPoints[3]*transform->getRotation()*transform->getTranslation();

		//Pushing the point and color information into the vector
		//pushtoVector(fourPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

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

		//Find the next point

		y-=1.0f;
		py = py - 2.0f * rxSq;

		if (p > 0) {
			p = p + rxSq - py;
		}

		else {
			x+=1.0f;
			px = px + 2.0f * rySq;
			p = p + rxSq - py + px;
		}

	}

	return PointColorVec;
}


void drawableEllipse::update(Point ellStart, Point ellEnd) {
	bbox = new BBox(ellStart, ellEnd);

}

void drawableEllipse::setTranslation(float xTrans, float yTrans) { //TODO: Make this more efficient

	transform->setTranslation(xTrans, yTrans);

	Point BBoxMin = bbox->getMin();
	Point BBoxMax = bbox->getMax();
	Point BBoxCen = bbox->getCenter();

	vmath::Tmat4<float> translation = vmath::translate(xTrans - BBoxCen.x, yTrans - BBoxCen.y, 0.0f);
	BBoxMin = BBoxMin.transform(translation);
	BBoxMax = BBoxMax.transform(translation);

	bbox = new BBox(BBoxMin,BBoxMax);

}

void drawableEllipse::setRotation(float theta) { //TODO: Make this more efficient

	transform->setRotation(theta);

	std::vector<PointAndColor> boundaryPACs = this->draw();
	BBox newBBox;

	float maxX = 0.0f;
	float minX = std::numeric_limits<float>::max();
	float maxY = 0.0f;
	float minY = std::numeric_limits<float>::max();
	Point chkPoint;
	for(int ii = 0; ii < boundaryPACs.size(); ii++) {
		chkPoint = boundaryPACs[ii].point;
		if(chkPoint.x > maxX) {
			maxX = chkPoint.x;
		}

		if(chkPoint.x < minX) {
			minX = chkPoint.x;
		}

		if(chkPoint.y > maxY) {
			maxY = chkPoint.y;
		}

		if(chkPoint.y < minY) {
			minY = chkPoint.y;
		}
	}
	Point newMin(minX,minY);
	Point newMax(maxX,maxY);
	bbox = new BBox(newMin, newMax);
}

void drawableEllipse::setScale(float rx, float ry) { //TODO: Make this more efficient

	transform->setScale(rx, ry);

	std::vector<PointAndColor> boundaryPACs = this->draw();
	BBox newBBox;
	int PACsize = boundaryPACs.size();
	for(int ii = 0; ii < boundaryPACs.size(); ii++) {
		newBBox = newBBox.unionBBox(boundaryPACs[ii].point);
	}
	bbox = new BBox(newBBox.getMin(), newBBox.getMax());

}

vmath::mat4 drawableEllipse::getTransformation() {

	transform->getTransformation();

}


vmath::mat4 drawableEllipse::getTranslation() {

	transform->getTranslation();

}

vmath::mat4 drawableEllipse::getRotation() {

	transform->getRotation();

}

vmath::mat4 drawableEllipse::getScale() {

	transform->getScale();

}

Point drawableEllipse::getMax() {

	return bbox->getMax();

}

Point drawableEllipse::getMin() {

	return bbox->getMin();

}

void drawableEllipse::PrintTransform(){

	transform->print();
}

void drawableEllipse::print(){

	std::cerr<<"Object Type: Ellipse"<<std::endl;
	std::cout<<"Bounding Box Information:"<<std::endl;
	bbox->print();
	std::cout<<"Object Information:"<<std::endl;
	//std::cout<<"Midpoint = "<<bbox->getCenter<<std::endl;
	std::cout<<"rx = "<<fabs(end.x - start.x) / 2.0f<<std::endl;
	std::cout<<"ry = "<<fabs(end.y - start.y) / 2.0f<<std::endl;

}
