/*
 * test_Ellipse.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Joe
 */

#include <iostream>
#include "math.h"
#include "Ellipse.h"
#include "Object.h"
#include <cassert>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

void test_DefaultEllipseConstructor(){


	vmath::mat4 Scale;

	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll;

//	std::cout<<"ellStart ="<<ellStart.x<<","<<ellStart.y<<std::endl;
//	std::cout<<"ellEnd ="<<ellEnd.x<<","<<ellEnd.y<<std::endl;

	Scale = myEll.getScale();
	myEll.PrintTransform();

	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
//
	std::cout<<"ellPointMax ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

//	assert(ellPointMax.x == 10.0f);
//	assert(ellPointMax.y == 10.0f);
//	assert(ellPointMin.x == 1.0f);
//	assert(ellPointMin.y == 1.0f);

}

void test_EllipseConstructor() {

	Point ellStart;
	ellStart.x = 1.0f;
	ellStart.y = 1.0f;

	Point ellEnd;
	ellEnd.x = 10.0f;
	ellEnd.y = 10.0f;

	vmath::mat4 Scale;

	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll(ellStart,ellEnd);

//	std::cout<<"ellStart ="<<ellStart.x<<","<<ellStart.y<<std::endl;
//	std::cout<<"ellEnd ="<<ellEnd.x<<","<<ellEnd.y<<std::endl;

	Scale = myEll.getScale();
	myEll.PrintTransform();

	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
//
	std::cout<<"ellPointMax ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

	assert(ellPointMax.x == 10.0f);
	assert(ellPointMax.y == 10.0f);
	assert(ellPointMin.x == 1.0f);
	assert(ellPointMin.y == 1.0f);
}

void test_EllipseDraw() {

	Point A;
	A.x = 0.0f;
	A.y = 0.0f;

	Point B;
	B.x = 4.0f;
	B.y = 4.0f;

	std::vector<PointAndColor> PointColorVec;

	drawableEllipse tryEll(A,B);
	PointColorVec = tryEll.draw();

	std::cerr<<"PointColorVec = "<<PointColorVec.size()<<std::endl;

}

void test_EllipseTranslate() {

	Point A;
	A.x = 1.0f;
	A.y = 1.0f;

	Point B;
	B.x = 2.0f;
	B.y = 2.0f;

	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll(A,B);
	std::cerr<<"Before set:- "<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax1 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin1 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

	myEll.setTranslation(2.0,2.0);
	std::cerr<<"After set:- "<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax2 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin2 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

}

void test_EllipseScale() {

	Point A;
	A.x = 0.0f;
	A.y = 0.0f;

	Point B;
	B.x = 5.0f;
	B.y = 5.0f;

	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll(A,B);
	std::cout<<"\n>>>>>> Before set:- \n"<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax1 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin1 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

	myEll.setScale(10.0,10.0);
	std::cout<<">>>>>> After set:- \n"<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax2 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin2 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

}

void test_EllipseRotation() {

	Point A;
	A.x = 1.0f;
	A.y = 1.0f;

	Point B;
	B.x = 10.0f;
	B.y = 10.0f;

	Point ellPointMax;
	Point ellPointMin;

	drawableEllipse myEll(A,B);
	std::cerr<<"Before set:- "<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax1 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin1 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

	myEll.setRotation(10.0);
	std::cerr<<"After set:- "<<std::endl;
	myEll.PrintTransform();
	ellPointMax = myEll.getMax();
	ellPointMin = myEll.getMin();
	std::cout<<"ellPointMax2 ="<<ellPointMax.x<<","<<ellPointMax.y<<std::endl;
	std::cout<<"ellPointMin2 ="<<ellPointMin.x<<","<<ellPointMin.y<<std::endl<<std::endl;

}

int main() {
	std::cout<<"Welcome to Ellipse test"<<std::endl;
//	test_DefaultEllipseConstructor();
//	test_EllipseConstructor();
//	test_EllipseDraw();
//	test_EllipseTranslate();
	test_EllipseScale();
//	test_EllipseRotation();
	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}
