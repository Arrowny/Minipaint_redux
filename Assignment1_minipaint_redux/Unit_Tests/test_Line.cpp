/*
 * test_Line.cpp
 *
 *  Created on: 2014Äê5ÔÂ31ÈÕ
 *      Author: yellow
 */

#include <iostream>
#include "math.h"
#include "Line.h"
#include <cassert>



/**
 * here test setStart(), setEnd, getStrat, getEnd at the same time.
 */
void test_start_end(){
	drawableLine L;
	Point start(0.11,0.22);
	Point end(0.33,0.44);

	L.setStart(start);
	L.setEnd(end);

	assert(start.x == L.getStart().x);
	assert(start.y == L.getStart().y);
	assert(end.x == L.getEnd().x);
	assert(end.y == L.getEnd().y);
	std::cout<<"end test of test_start_end()"<<std::endl;
}

int main() {
	std::cout<<"Welcome to Line test"<<std::endl;

	test_start_end();

	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}

