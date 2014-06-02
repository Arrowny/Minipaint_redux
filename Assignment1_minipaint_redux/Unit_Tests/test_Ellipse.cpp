/*
 * test_Ellipse.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Joe
 */

#include <iostream>
#include "math.h"
#include "Ellipse.h"
#include <cassert>

void test_EllipseConstructor() {

	Point ellStart;
	ellStart.x = 1.0;
	ellStart.y = 3.0;

	Point ellEnd;
	ellEnd.x = 3.0;
	ellEnd.y = 2.0;

	vmath::mat4 ScaleX;
	vmath::Tmat4<float> ScaleY;
	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll(ellStart,ellEnd);
	//BBox bbox(ellStart,ellEnd);

//	std::cout<<"ellStart ="<<ellStart.x<<","<<ellStart.y<<std::endl;
//	std::cout<<"ellEnd ="<<ellEnd.x<<","<<ellEnd.y<<std::endl;

	ScaleX = myEll.getScale();
	myEll.PrintTransform();

	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
//	Point tmpMax(ScaleX[0][0],ScaleX[0][1]);
//	Point tmpMin(ScaleX[1][0],ScaleX[2][2]);
//
	std::cout<<"ellPointMax ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl;

//	assert(ellPointMax.x == 3.0f);
//	assert(ellPointMax.y == 3.0f);
//	assert(ellPointMin.x == 1.0f);
//	assert(ellPointMin.y == 2.0f);
}

void test_EllipseDraw() {

	Point ellStart;
	ellStart.x = 1.0;
	ellStart.y = 1.0;

	Point ellEnd;
	ellEnd.x = 3.0;
	ellEnd.y = 2.0;

	drawableEllipse myEll(ellStart,ellEnd);
	BBox bbox(ellStart,ellEnd);

	std::cout<<"ellStart ="<<ellStart.x<<","<<ellStart.y<<std::endl;
	std::cout<<"ellEnd ="<<ellEnd.x<<","<<ellEnd.y<<std::endl;

	Point tmpMax = bbox.getMax();
	Point tmpMin = bbox.getMin();

	std::cout<<"tmpMax ="<<tmpMax.x<<","<<tmpMax.y<<std::endl;
	std::cout<<"tmpMin ="<<tmpMin.x<<","<<tmpMin.y<<std::endl;

	assert(tmpMax.x == 3.0f);
	assert(tmpMax.y == 2.0f);
	assert(tmpMin.x == 1.0f);
	assert(tmpMin.y == 1.0f);
}

int main() {
	std::cout<<"Welcome to Ellipse test"<<std::endl;
	test_EllipseConstructor();
	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}

//void test_EllipseDraw() {
//
//	Point A;
//	A.x = 1.0;
//	A.y = 1.0;
//
//	Point B;
//	B.x = 3.0;
//	B.y = 2.0;
//
//	std::vector<PointAndColor> PointColorVec;
//
//	Ellipse myEll = Ellipse(A,B);
//	PointColorVec = myEll.draw();
//
//	assert(PointColorVec[0][0] == 2.0);
//	assert(PointColorVec[0][1] == 2.0);
//}
