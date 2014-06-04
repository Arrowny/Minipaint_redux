/*
 * test_BBox.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#include <iostream>
#include "math.h"
#include "Misc.h"
#include "BBox.h"
#include "assert.h"

void test_Default_BBoxconstructor() {
	BBox defaultBBox;

	Point tmpMax = defaultBBox.getMax();
	Point tmpMin = defaultBBox.getMin();

	//test that passed values are actually copies and not the original values
	tmpMax.x = 25;
	//Debug: std::cout<<tmpMax.x<<" "<<defaultBBox.getMax().x<<std::endl;
	assert ( tmpMax.x > defaultBBox.getMax().x );

	//make sure constructor is working correctly
	//Debug: std::cout<<tmpMax.y<<" "<<tmpMin.y<<std::endl;
	assert (tmpMax.y < tmpMin.y);
}

void test_Point_Constructor() {
	Point a(4.0, 7.0);
	Point b(5.0, 2.0);

	BBox PtConstructorBBox(a,b);

	Point tmpMax = PtConstructorBBox.getMax();
	Point tmpMin = PtConstructorBBox.getMin();


	//Debug:PtConstructorBBox.print();
	//Debug:std::cout<<"Min: ("<<tmpMin.x<<","<<tmpMin.y<<")"<<std::endl;
	//Debug:std::cout<<"Max: ("<<tmpMax.x<<","<<tmpMax.y<<")"<<std::endl;

	//Note: not good practice to compare floating point numbers
	assert (tmpMin.x == 4.0);
	assert (tmpMin.y == 2.0);
	assert (tmpMax.x == 5.0);
	assert (tmpMax.y == 7.0);
}

void test_Union_Point_And_Assignment_Copy_Operators() {
	BBox defaultBBox;

	Point unionPoint(5.0,5.0);
	BBox* originalAddress = &defaultBBox;
	defaultBBox = defaultBBox.unionBBox(unionPoint);
	BBox* newAddress = &defaultBBox;
	BBox checkCopy = defaultBBox;

	Point tmpMax = defaultBBox.getMax();
	Point tmpMin = defaultBBox.getMin();


	//Debug: std::cout<<"Min: ("<<tmpMin.x<<","<<tmpMin.y<<")"<<std::endl;
	//Debug: std::cout<<"Max: ("<<tmpMax.x<<","<<tmpMax.y<<")"<<std::endl;
	assert (tmpMin.x == 5.0);
	assert (tmpMin.y == 5.0);
	assert (tmpMax.x == 5.0);
	assert (tmpMax.y == 5.0);

	tmpMin = checkCopy.getMin();
	tmpMax = checkCopy.getMax();

	//Debug: std::cout<<"Min: ("<<tmpMin.x<<","<<tmpMin.y<<")"<<std::endl;
	//Debug: std::cout<<"Max: ("<<tmpMax.x<<","<<tmpMax.y<<")"<<std::endl;
	assert (tmpMin.x == 5.0);
	assert (tmpMin.y == 5.0);
	assert (tmpMax.x == 5.0);
	assert (tmpMax.y == 5.0);

	//Debug:std::cout<<&(*originalAddress)<<" vs "<<&(*newAddress)<<std::endl;
	//Debug:std::cout<<&(*newAddress)<<" vs "<<&checkCopy<<std::endl;

	//check assignment operator is working correctly (assignment operator should not change address)
	assert (&(*originalAddress) == &(*newAddress));

	//check copy constructor. Copy should not have same address as original.
	assert (&(*newAddress) != &checkCopy);
}

void test_Union_BBox() {
	BBox defaultBBox;
	BBox defaultBBox2;
	defaultBBox = defaultBBox.unionBBox(defaultBBox2);


	Point tmpMax = defaultBBox.getMax();
	Point tmpMin = defaultBBox.getMin();

	//test that passing a default bbox will produce the correct results
	assert(tmpMin.x == 0.0f);
	assert(tmpMin.y == 0.0f);
	assert(tmpMax.x == -1.0f);
	assert(tmpMax.y == -1.0f);

	Point a(4.0f, 7.0f);
	Point b(5.0f, 2.0f);
	BBox PtConstructorBBox(a,b);
	defaultBBox = defaultBBox.unionBBox(PtConstructorBBox);


	tmpMax = defaultBBox.getMax();
	tmpMin = defaultBBox.getMin();

	//Debug:std::cout<<"Min: ("<<tmpMin.x<<","<<tmpMin.y<<")"<<std::endl;
	//Debug:std::cout<<"Max: ("<<tmpMax.x<<","<<tmpMax.y<<")"<<std::endl;

	//test that passing a new bbox to a default bbox will produce the correct results
	assert (tmpMin.x == 4.0f);
	assert (tmpMin.y == 2.0f);
	assert (tmpMax.x == 5.0f);
	assert (tmpMax.y == 7.0f);

	Point c(1.0f,7.0f);
	Point d(5.0f,1.0f);
	BBox PtConstructorBBox2(c,d);
	defaultBBox = defaultBBox.unionBBox(PtConstructorBBox2);

	tmpMax = defaultBBox.getMax();
	tmpMin = defaultBBox.getMin();

	//test that passing a new bbox to an initialized bbox will produce the correct results
	assert (tmpMin.x == 1.0f);
	assert (tmpMin.y == 1.0f);
	assert (tmpMax.x == 5.0f);
	assert (tmpMax.y == 7.0f);
}

void test_expand() {
	Point a(1.0, 1.0);
	Point b(2.0, 2.0);

	BBox PtConstructorBBox(a,b);
	PtConstructorBBox = PtConstructorBBox.expandBBox(1.0,1.0);

	Point tmpMax = PtConstructorBBox.getMax();
	Point tmpMin = PtConstructorBBox.getMin();

	//Debug: std::cout<<"Min: ("<<tmpMin.x<<","<<tmpMin.y<<")"<<std::endl;
	//Debug: std::cout<<"Max: ("<<tmpMax.x<<","<<tmpMax.y<<")"<<std::endl;

	//Note: not good practice to compare floating point numbers
	assert (tmpMin.x == 0.0);
	assert (tmpMin.y == 0.0);
	assert (tmpMax.x == 3.0);
	assert (tmpMax.y == 3.0);
}

void test_inside() {

	Point a(1.0, 1.0);
	Point b(2.0, 2.0);

	BBox PtConstructorBBox(a,b);

	Point outside1(0.0,0.0);
	Point inside1(1.0,1.0);
	Point inside2(1.5,1.7);
	Point outside2(3.0,2.0);
	assert( !PtConstructorBBox.insideBBox(outside1) );
	assert( !PtConstructorBBox.insideBBox(outside2) );
	assert( PtConstructorBBox.insideBBox(inside1) );
	assert( PtConstructorBBox.insideBBox(inside2) );

}

void test_getCorners() {
	Point a(1.0, 1.0);
	Point b(2.0, 2.0);

	BBox PtConstructorBBox(a,b);

	Point* corners = PtConstructorBBox.getCorners();

	assert(corners[0].x == 1.0); assert(corners[0].y == 1.0);
	assert(corners[1].x == 2.0); assert(corners[1].y == 1.0);
	assert(corners[2].x == 2.0); assert(corners[2].y == 2.0);
	assert(corners[3].x == 1.0); assert(corners[2].y == 2.0);
}

int main() {
	std::cout<<"Welcome to BBox test"<<std::endl;
	test_Default_BBoxconstructor();
	test_Point_Constructor();
	test_Union_Point_And_Assignment_Copy_Operators();
	test_Union_BBox();
	test_expand();
	//test_inside();
	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}
