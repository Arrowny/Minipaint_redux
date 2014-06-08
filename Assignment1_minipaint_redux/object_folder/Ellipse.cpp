/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"
#include <math.h>
//#include "Misc.h"
//#include "GL/gl.h"
//#include "vmath.h"
#include <string>
#include <vector>

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
drawableEllipse::drawableEllipse(Point ellStart, Point ellEnd) {

	start = ellStart;
	end = ellEnd;
	bbox = new BBox(ellStart, ellEnd);

	Point midpoint;
	Point minimum = bbox->getMin();

	std::cout<<"bbox minx = "<<minimum.x<<std::endl;
	std::cout<<"bbox miny = "<<minimum.y<<std::endl;
	std::cout<<"ellStart = "<<ellStart.x<<","<<ellStart.y<<std::endl;
	std::cout<<"ellEnd = "<<ellEnd.x<<","<<ellEnd.y<<std::endl;

	float rx = fabs(ellEnd.x - ellStart.x) / 2.0f;
	float ry = fabs(ellEnd.y - ellStart.y) / 2.0f;
	midpoint.x = minimum.x + rx;
	midpoint.y = minimum.y + ry;

	std::cout<<"rx = "<<rx<<std::endl;
	std::cout<<"ry = "<<ry<<std::endl;
	std::cout<<"midpointx = "<<midpoint.x<<std::endl;
	std::cout<<"midpointy = "<<midpoint.y<<std::endl;

	transform = new Transformation(0.0f, midpoint.x, midpoint.y, rx, ry);

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
	//PointAndColor ellPointColorStart()

	std::vector<PointAndColor> PointColorVec;
	vmath::Tvec4<float>* ellPoints;
	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);

	vecX = vecX * transform->getScale();
	//transform->print();
	vecY = vecY * transform->getScale();

	std::cout<<"vecX = ("<<vecX[0]<<","<<vecX[1]<<","<<vecX[2]<<","<<vecX[3]<<")"<<std::endl;
	std::cout<<"vecY = ("<<vecY[0]<<","<<vecY[1]<<","<<vecY[2]<<","<<vecY[3]<<")"<<std::endl;

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	start = A;
	end = B;

	std::cout<<"A = ("<<A.x<<","<<A.y<<")"<<std::endl;
	std::cout<<"B = ("<<B.x<<","<<B.y<<")"<<std::endl;
	std::cout<<"A.x = "<<A.x<<" "<<"A.y = "<<A.y<<std::endl;
	std::cout<<"B.x = "<<B.x<<" "<<"B.y = "<<B.y<<std::endl;

	float rx = A.x;
	float ry = B.y;
//	float rx = fabs(B.x - A.x) / 2.0f;
//	float ry = fabs(B.y - A.y) / 2.0f;

//	std::cout<<"rx = "<<rx<<" "<<"ry = "<<ry<<std::endl;

	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = -rx, y = ry, p;
	float px = 0, py = 2.0f * rxSq * y;

	std::cout<<"I'm outside region check"<<std::endl;

	//Region 1: 2nd Octant of 1st Quadrant
	std::cout<<"P = "<<p<<" Y = "<<y<<std::endl;
	p = rySq - (rxSq * ry) + (0.25 * rxSq);

//	std::cout<<"px = "<<px<<" "<<"py = "<<py<<std::endl;

	while (px < py) {

//		std::cerr<<">>>I'm inside region1 check"<<std::endl;

		//Transforming and plotting the points to where they should be
//		ellPoints = FindPointOctant2(start, rx, ry, rxSq, rySq, x, y, px, py, p);
//		ellPoints = partialTransform(ellPoints, *transform);

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

		fourPoints[0][0] = start.x + x;
		fourPoints[0][1] = start.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;
//		std::cout<<"fourPoints1 = "<<fourPoints[0][0]<<","<<fourPoints[0][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[1][0] = start.x - x;
		fourPoints[1][1] = start.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;
//		std::cout<<"fourPoints2 = "<<fourPoints[1][0]<<","<<fourPoints[1][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[2][0] = start.x + x;
		fourPoints[2][1] = start.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;
//		std::cout<<"fourPoints3 = "<<fourPoints[2][0]<<","<<fourPoints[2][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[3][0] = start.x - x;
		fourPoints[3][1] = start.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;
//		std::cout<<"fourPoints4 = "<<fourPoints[3][0]<<","<<fourPoints[3][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[0] = fourPoints[0]*transform->getRotation()*transform->getTranslation();
		fourPoints[1] = fourPoints[1]*transform->getRotation()*transform->getTranslation();
		fourPoints[2] = fourPoints[2]*transform->getRotation()*transform->getTranslation();
		fourPoints[3] = fourPoints[3]*transform->getRotation()*transform->getTranslation();

		//Pushing the point and color information into the vector
		//pushtoVector(fourPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

		tmpPoint.x = fourPoints[0][0];
		tmpPoint.y = fourPoints[0][1];
		std::cerr<<"tmpPoint = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec1 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[1][0];
		tmpPoint.y = fourPoints[1][1];
		std::cerr<<"tmpPoint2 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec2 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[2][0];
		tmpPoint.y = fourPoints[2][1];
		std::cerr<<"tmpPoint3 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec3 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[3][0];
		tmpPoint.y = fourPoints[3][1];
		std::cerr<<"tmpPoint4 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec4 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		//Draw the points
		drawFourPoints(fourPoints);

//		std::cout<<"px vs py = "<<px<<","<<py<<std::endl;

	}

	std::cout<<"Vector size1 = "<<PointColorVec.size()<<std::endl;

	//Region 2: 1st Octant of 1st Quadrant
	std::cout<<"P = "<<p<<" Y = "<<y<<std::endl;
	p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;

	while (y > 0) {
//		std::cerr<<">>>I'm inside region2 check"<<std::endl;
		//Transforming and plotting the points to where they should be
		//ellPoints = FindPointOctant1(start, rx, ry, rxSq, rySq, x, y, px, py, p);
		//ellPoints = partialTransform(ellPoints, *transform);
		vmath::Tvec4<float> fourPoints[4];

		p = rySq - (rxSq * ry) + (0.25 * rxSq);

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

		fourPoints[0][0] = start.x + x;
		fourPoints[0][1] = start.y + y;
		fourPoints[0][2] = 0.0;
		fourPoints[0][3] = 1.0;
//		std::cout<<"fourPoints1 = "<<fourPoints[0][0]<<","<<fourPoints[0][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[1][0] = start.x - x;
		fourPoints[1][1] = start.y + y;
		fourPoints[1][2] = 0.0;
		fourPoints[1][3] = 1.0;
//		std::cout<<"fourPoints2 = "<<fourPoints[1][0]<<","<<fourPoints[1][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y + y, 0.0f, 1.0f);

		fourPoints[2][0] = start.x + x;
		fourPoints[2][1] = start.y - y;
		fourPoints[2][2] = 0.0;
		fourPoints[2][3] = 1.0;
//		std::cout<<"fourPoints3 = "<<fourPoints[2][0]<<","<<fourPoints[2][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x + x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[3][0] = start.x - x;
		fourPoints[3][1] = start.y - y;
		fourPoints[3][2] = 0.0;
		fourPoints[3][3] = 1.0;
//		std::cout<<"fourPoints4 = "<<fourPoints[3][0]<<","<<fourPoints[3][1]<<std::endl;
		//new vmath::Tvec4<float>(start_p.x - x, start_p.y - y, 0.0f, 1.0f);

		fourPoints[0] = fourPoints[0]*transform->getRotation()*transform->getTranslation();
		fourPoints[1] = fourPoints[1]*transform->getRotation()*transform->getTranslation();
		fourPoints[2] = fourPoints[2]*transform->getRotation()*transform->getTranslation();
		fourPoints[3] = fourPoints[3]*transform->getRotation()*transform->getTranslation();

		//Pushing the point and color information into the vector
		//pushtoVector(fourPoints, ellColor, ellPointColor, PointColorVec, tmpPoint);

		tmpPoint.x = fourPoints[0][0];
		tmpPoint.y = fourPoints[0][1];
		std::cerr<<"tmpPoint = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec1 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[1][0];
		tmpPoint.y = fourPoints[1][1];
		std::cerr<<"tmpPoint2 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec2 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[2][0];
		tmpPoint.y = fourPoints[2][1];
		std::cerr<<"tmpPoint3 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec3 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		tmpPoint.x = fourPoints[3][0];
		tmpPoint.y = fourPoints[3][1];
		std::cerr<<"tmpPoint4 = "<<tmpPoint.x<<","<<tmpPoint.y<<std::endl;
		ellPointColor.point = tmpPoint;
		ellPointColor.color = ellColor;
//		std::cout<<"PointColorVec4 = "<<ellPointColor.point.x<<","<<ellPointColor.point.y<<std::endl;
//		std::cout<<"	"<<ellPointColor.color.red<<","<<ellPointColor.color.green<<","<<ellPointColor.color.blue<<std::endl;
//		std::cout<<"VecSize = "<<PointColorVec.size()<<std::endl;
		PointColorVec.push_back(ellPointColor);

		//Draw the points
		drawFourPoints(fourPoints);

//		std::cout<<"y = "<<y<<std::endl;
//		std::cout<<"p = "<<p<<std::endl;
	}
	std::cout<<"Vector size2 = "<<PointColorVec.size()<<std::endl;

	std::cout<<"I'm returning"<<std::endl;
	return PointColorVec;
}


void drawableEllipse::update(Point ellStart, Point ellEnd) {
	bbox = new BBox(ellStart, ellEnd);

}

void drawableEllipse::setTranslation(float rx, float ry) {

	Point A, B;
	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);

	transform->setTranslation(rx, ry);

	vecX = vecX * transform->getTranslation();
	vecY = vecY * transform->getTranslation();

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	start = A;
	end = B;

	bbox = new BBox(A, B);

}

void drawableEllipse::setRotation(float theta) {

	Point A, B;
	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);

	transform->setRotation(theta);

	vecX = vecX * transform->getRotation();
	vecY = vecY * transform->getRotation();

	A.x = vecX[0];
	A.y = vecX[1];
	B.x = vecY[0];
	B.y = vecY[1];

	start = A;
	end = B;

	bbox = new BBox(A, B);

}

void drawableEllipse::setScale(float rx, float ry) {

	Point A, B;
	Point magRx, magRy;
	Point midpoint;
	vmath::Tvec4<float> vecX(1.0f, 0.0f, 0.0f, 1.0f);
	vmath::Tvec4<float> vecY(0.0f, 1.0f, 0.0f, 1.0f);

	transform->setScale(rx, ry);

	vecX = vecX * transform->getScale() * transform->getRotation();
	vecY = vecY * transform->getScale() * transform->getRotation();

	if(vecX[0] > vecY[1])
	{
		magRx.x = vecX[0];
		magRx.y = 0.0f;
		magRy.x = 0.0f;
		magRy.y = vecX[0];

	}
	else
	{
		magRx.x = vecY[1];
		magRx.y = 0.0f;
		magRy.x = 0.0f;
		magRy.y = vecY[1];

	}

	vecX = vecX * transform->getTranslation();
	vecY = vecY * transform->getTranslation();

	std::cout<<"vecX = ("<<vecX[0]<<","<<vecX[1]<<","<<vecX[2]<<","<<vecX[3]<<")"<<std::endl;
	std::cout<<"vecY = ("<<vecY[0]<<","<<vecY[1]<<","<<vecY[2]<<","<<vecY[3]<<")\n"<<std::endl;

	std::cout<<"newRx = ("<<magRx.x<<","<<magRx.y<<")"<<std::endl;
	std::cout<<"newRy = ("<<magRy.x<<","<<magRy.y<<")"<<std::endl;

	midpoint.x = vecX[0] - magRx.x;
	midpoint.y = vecY[1] - magRy.y;

	std::cout<<"midpoint = ("<<midpoint.x<<","<<midpoint.y<<")"<<std::endl;

	A.x = magRx.x + midpoint.x;
	A.y = magRx.x + midpoint.x;
	B.x = -(magRx.x - midpoint.x);
	B.y = -(magRx.x - midpoint.x);

	bbox = new BBox(A, B);
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

	std::cout<<"[Object Type: Ellipse]"<<std::endl<<std::endl;
	std::cout<<"Bounding Box Information:"<<std::endl;
	bbox->print();
	std::cout<<"Object Information:"<<std::endl;
	Point A = bbox->getCenter();
	std::cout<<"Midpoint = "<<A.x<<","<<A.y<<std::endl;
	std::cout<<"rx = "<<fabs(end.x - start.x) / 2.0f<<std::endl;
	std::cout<<"ry = "<<fabs(end.y - start.y) / 2.0f<<std::endl<<std::endl;

}
