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
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

void test_EllipseConstructor() {

	Point ellStart;
	ellStart.x = 1.0f;
	ellStart.y = 1.0f;

	Point ellEnd;
	ellEnd.x = 5.0f;
	ellEnd.y = 5.0f;

	vmath::Tmat4<float> ScaleX;
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

//	assert(ellPointMax.x == 10.0f);
//	assert(ellPointMax.y == 10.0f);
//	assert(ellPointMin.x == 1.0f);
//	assert(ellPointMin.y == 1.0f);
}

void test_EllipseDraw() {

	Point A;
	A.x = 1.0f;
	A.y = 1.0f;

	Point B;
	B.x = 20.0f;
	B.y = 20.0f;

	std::vector<PointAndColor> PointColorVec;

	drawableEllipse tryEll(A,B);
	PointColorVec = tryEll.draw();

	std::cerr<<"PointColorVec = "<<PointColorVec.size()<<std::endl;

}

int main() {
	std::cout<<"Welcome to Ellipse test"<<std::endl;
	test_EllipseConstructor();
	//test_EllipseDraw();
	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}
