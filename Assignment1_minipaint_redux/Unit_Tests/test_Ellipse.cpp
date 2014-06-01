/*
 * test_Ellipse.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Joe
 */

#include <iostream>
#include "math.h"
#include "Object.h"
#include "Ellipse.h"
#include <cassert>

void test_EllipseConstructor() {

	Point ellStart;
	ellStart.x = 1.0;
	ellStart.y = 1.0;

	Point ellEnd;
	ellEnd.x = 3.0;
	ellEnd.y = 2.0;

	Ellipse myEll(ellStart,ellEnd);
	BBox bbox(ellStart,ellEnd);

	Point tmpMax = bbox.getMax();
	Point tmpMin = bbox.getMin();

	assert(tmpMax.x == 3.0);
	assert(tmpMax.y == 2.0);
	assert(tmpMin.x == 1.0);
	assert(tmpMin.y == 1.0);
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
