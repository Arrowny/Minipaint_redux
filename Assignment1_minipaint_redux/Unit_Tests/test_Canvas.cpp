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

void test_CanvasConstructor_Object(){
	std::cout<<"test of CanvasConstructor_Object"<<std::endl;
	Point start(1.0f,1.0f);
	Point end(6.0f, 6.0f);
	Color color(0.0f, 0.0f, 0.0f);

	Object* object1;
	object1 = new Line(start, end, color);
			//new Line(start, end, Color(0.0f,0.0f,0.0f));
	Canvas myCanvas(object1);


	Point A = myCanvas.getCenter();
	printf("Center of myCanvas: %f, %f \n",A.x, A.y);
	myCanvas.print();

//	Point B = L.getCenter();
//	printf("Center of L: %f, %f \n",B.x, B.y);


}

void test_CanvasConstructor_Vector(){
	std::cout<<"test of CanvasConstructor_Vector"<<std::endl;
	Point start(1.0f,1.0f);
	Point end(6.0f, 6.0f);

	std::vector<Object*> Objs;

	Object* object1 = new Line(start, end, Color(0.0f,0.0f,0.0f));
	Objs.push_back(object1);
	Object* object2 = new Line(Point(2.0f, 2.0f), Point(5.0f, 5.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object2);

	std::cout<<Objs.size()<<std::endl;
	Canvas myCanvas(Objs);

	Point A = myCanvas.getCenter();
	printf("Center of myCanvas: %f, %f \n",A.x, A.y);
	myCanvas.print();

}

void test_CanvasDraw(){
	std::cout<<"test of CanvasConstructor_Vector"<<std::endl;
	Point start(1.0f,1.0f);
	Point end(6.0f, 6.0f);

	std::vector<Object*> Objs;

	Object* object1 = new Line(start, end, Color(0.0f,0.0f,0.0f));
	Objs.push_back(object1);
	Object* object2 = new Line(Point(2.0f, 2.0f), Point(5.0f, 5.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object2);
	Object* object3 = new drawableEllipse(Point(1.0f, 1.0f), Point(10.0f, 10.0f));
	Objs.push_back(object3);

	std::cout<<Objs.size()<<std::endl;
	Canvas myCanvas(Objs);

	std::vector<PointAndColor> drawVector = myCanvas.draw();

	for(int ii = 0; ii < drawVector.size(); ii++) {

		std::cout<<"Point "<<ii<<" = ("<<drawVector[ii].point.x<<","<<drawVector[ii].point.y<<")"<<std::endl;

	}


}

void test_CanvasFill(){
	std::cout<<"test of CanvasConstructor_Fill"<<std::endl;
	std::vector<Object*> Objs;

	Object* object1 = new Line(Point(1.0f, 1.0f), Point(1.0f, 4.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object1);
	Object* object2 = new Line(Point(1.0f, 4.0f), Point(4.0f, 4.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object2);
	Object* object3 = new Line(Point(4.0f, 4.0f), Point(4.0f, 1.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object3);
	Object* object4 = new Line(Point(4.0f, 1.0f), Point(1.0f, 1.0f), Color(0.0f,0.0f,0.0f));
	Objs.push_back(object4);
//	Object* object5 = new drawableEllipse(Point(1.0f, 1.0f), Point(4.0f, 4.0f));
//	Objs.push_back(object5);

	std::cout<<Objs.size()<<std::endl;
	Canvas myCanvas(Objs);

	PointAndColor PAC(Point(2.0f, 2.0f), Color(0.0f,0.0f,0.0f));

	std::vector<PointAndColor> fillVector = myCanvas.fill(PAC);

	for(int ii = 0; ii < fillVector.size(); ii++) {

		Point fillPoint = fillVector[ii].point;
		assert(myCanvas.inside(fillPoint));
		std::cout<<"Greetings from inside the object"<<std::endl;
		std::cout<<"Point "<<ii<<" = ("<<fillVector[ii].point.x<<","<<fillVector[ii].point.y<<")"<<std::endl;

		}

}

void test_CanvasReapplyFill(){
	std::cout<<"test of CanvasConstructor_Fill"<<std::endl;
	std::vector<Object*> Objs;

//	Object* object1 = new Line(Point(1.0f, 1.0f), Point(1.0f, 4.0f), Color(0.0f,0.0f,0.0f));
//	Objs.push_back(object1);
//	Object* object2 = new Line(Point(1.0f, 4.0f), Point(4.0f, 4.0f), Color(0.0f,0.0f,0.0f));
//	Objs.push_back(object2);
//	Object* object3 = new Line(Point(4.0f, 4.0f), Point(4.0f, 1.0f), Color(0.0f,0.0f,0.0f));
//	Objs.push_back(object3);
//	Object* object4 = new Line(Point(4.0f, 1.0f), Point(1.0f, 1.0f), Color(0.0f,0.0f,0.0f));
//	Objs.push_back(object4);
	Object* object5 = new drawableEllipse(Point(1.0f, 1.0f), Point(4.0f, 4.0f));
	Objs.push_back(object5);

	std::cout<<Objs.size()<<std::endl;
	Canvas myCanvas(Objs);

	PointAndColor PAC(Point(4.0f, 2.0f), Color(0.0f,0.0f,0.0f));

	std::vector<PointAndColor> fillVector = myCanvas.fill(PAC);

	for(int ii = 0; ii < fillVector.size(); ii++) {

		Point fillPoint = fillVector[ii].point;
		assert(myCanvas.inside(fillPoint));
		std::cout<<"Greetings from inside the object"<<std::endl;
		std::cout<<"Point "<<ii<<" = ("<<fillVector[ii].point.x<<","<<fillVector[ii].point.y<<")"<<std::endl;

		}

}

/**
 * test canvas scale
 */
void test_Scale() {
	std::cout << "\ntest_Scale" << std::endl;

	Point lStart(1.0f, 1.0f);
	Point lEnd(3.0f, 3.0);

	Point eStart(4.0f, 1.0f);
	Point eEnd(6.0f, 7.0f);

	Object* line = new Line(lStart, lEnd, Color(0.0f, 0.0f, 0.0f));
	Object* ellipse = new drawableEllipse(eStart, eEnd);

	std::vector<Object*> canvasObjs;
	canvasObjs.push_back(line);
	canvasObjs.push_back(ellipse);

	Canvas transCanvas(canvasObjs);
	transCanvas.print();
	transCanvas.setScale(2.0f, 2.0f);
	transCanvas.print();
}

/**
 * test canvas translation
 */
void test_Translation() {
	std::cout << "\ntest_Translation" << std::endl;

	Point lStart(1.0f, 1.0f);
	Point lEnd(3.0f, 5.0f);

	Point eStart(4.0f, 1.0f);
	Point eEnd(6.0f, 7.0f);

	Object* line = new Line(lStart, lEnd, Color(0.0f, 0.0f, 0.0f));
	Object* ellipse = new drawableEllipse(eStart, eEnd);

	std::vector<Object*> canvasObjs;
	canvasObjs.push_back(line);
	canvasObjs.push_back(ellipse);

	Canvas transCanvas(canvasObjs);
	transCanvas.print();
	transCanvas.setTranslation(0.0f, 0.0f);
	transCanvas.print();
}

/**
 * test canvas rotation
 */
void test_Rotation() {
	std::cout << "\ntest_Rotation" << std::endl;

	Point lStart(1.0f, 1.0f);
	Point lEnd(3.0f, 5.0f);

	Point eStart(4.0f, 1.0f);
	Point eEnd(6.0f, 7.0f);

	Object* line = new Line(lStart, lEnd, Color(0.0f, 0.0f, 0.0f));
	Object* ellipse = new drawableEllipse(eStart, eEnd);

	std::vector<Object*> canvasObjs;
	canvasObjs.push_back(line);
	canvasObjs.push_back(ellipse);

	Canvas transCanvas(canvasObjs);
	transCanvas.print();
	transCanvas.setRotation(30.0f);
	transCanvas.print();
}

void test_fill_Transform() {
	std::cout << "\ntest_fill_Transform" << std::endl;
	Point lStart(1.0f, 1.0f);
	Point lEnd(3.0f, 5.0f);

	Point eStart(4.0f, 1.0f);
	Point eEnd(6.0f, 7.0f);

	Object* line = new Line(lStart, lEnd, Color(0.0f, 0.0f, 0.0f));
	Object* ellipse = new drawableEllipse(eStart, eEnd);

	std::vector<Object*> canvasObjs;
	canvasObjs.push_back(line);
	canvasObjs.push_back(ellipse);

	Canvas transCanvas(canvasObjs);
	Point fillPoint(transCanvas.getCenter());
	Color fillColor(0.5, 0.5, 0.5);
	transCanvas.fill(PointAndColor(fillPoint, fillColor));

	transCanvas.print();
	transCanvas.setTranslation(0.0f, 0.0f);
	transCanvas.print();
}

int main() {
	std::cout<<"Welcome to Canvas test"<<std::endl;
//	test_CanvasConstructor_Object();
//	test_CanvasConstructor_Vector();
//	test_CanvasDraw();
//	test_CanvasFill();
//	test_CanvasReapplyFill();
	test_Scale();
//	test_Translation();
//	test_Rotation();
//	test_fill_Transform();

	std::cout<<"All Tests passed!"<<std::endl;
	return 0;
}

