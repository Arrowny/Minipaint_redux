/*
 * test_Canvas.cpp
 *
 *  Created on: 2014Äê6ÔÂ6ÈÕ
 *      Author: yellow
 */

#include <iostream>
#include "math.h"
#include "Canvas.h"
#include "Transformation.h"
#include "Object.h"
#include "Line.h"
#include "Ellipse.h"
#include "Misc.h"
#include <cassert>
#include <cstdio>
#include <iostream>

void test_CanvasConstructor_Default(){
	//Canvas myCanvas = new Canvas();

}

void test_CanvasConstructor_with_parameters(){
	std::cout<<"test of CanvasConstructor_with_parameters"<<std::endl;
	Point start(1.0f,1.0f);
	Point end(6.0f, 6.0f);

	Object* object1;
	object1 = new Line();
			//new Line(start, end, Color(0.0f,0.0f,0.0f));
	Canvas myCanvas(object1);


	Point A = myCanvas.getCenter();
	printf("Center of myCanvas: %f, %f \n",A.x, A.y);
	myCanvas.print();

//	Point B = L.getCenter();
//	printf("Center of L: %f, %f \n",B.x, B.y);


}
void test_CanvasConstructor_with_parameters2(){
	std::cout<<"test of CanvasConstructor_with_parameters"<<std::endl;
	Point start(1.0f,1.0f);
	Point end(6.0f, 6.0f);

	Object* object1 = new Line(start, end, Color(0.0f,0.0f,0.0f));
	Object* object2 = new Line(start, end, Color(0.0f,0.0f,0.0f));

	std::vector<Object*> initialObjs;
	initialObjs.push_back(object1);
	initialObjs.push_back(object2);

	Canvas myCanvas(initialObjs);


	Point A = myCanvas.getCenter();
	printf("Center of myCanvas: %f, %f \n",A.x, A.y);
	myCanvas.print();

//	Point B = L.getCenter();
//	printf("Center of L: %f, %f \n",B.x, B.y);


}
/**
 * comparative test, use its outcome to judge whether the draw() gives right result
 */
void test_Canvas_draw(){
	Point start(1.0f,1.0f);
	Point end(5.0f, 5.0f);
	Line L(start, end, Color(0.0f,0.0f,0.0f));

	//myCanvas.draw();

}
void test_fill_helper(){

}

void test_reapplyAllFills(){

}
/**
 * test transformations include scaling, rotation, and transposition
 */
void test_transformation(){
//	Line L;
//
//	L.setStart(Point(0.0f,0.0f));
//	L.setEnd(Point(2.0f,2.0f));

	Line myLine;
	Point A(0.0f, 0.0f);
	Point B(2.0f, 2.0f);


	myLine = Line(A,B,Color(0.0f, 0.0f, 0.0f));
	myLine.draw();
	//myLine.printTransform();
	BBox bbox = myLine.getBBox();
	bbox.print();
//	L.setTranslation(1.1f,2.2f);
//	L.setRotation(1.1);
	myLine.setScale(4.0f,4.0f);

	//myLine.printTransform();
	bbox = myLine.getBBox();
	myLine.draw();


	std::cout<<"end test of test_start_end()"<<std::endl;
}

int main() {
	std::cout<<"Welcome to Canvas test"<<std::endl;
	//test_CanvasConstructor_with_parameters();
	test_CanvasConstructor_with_parameters2();
//	test_Canvas_draw();
//	test_fill_helper();
//	test_reapplyAllFills();
//	test_transformation();

	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}

