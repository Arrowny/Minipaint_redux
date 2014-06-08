/*
 * Line.cpp
 *
 *  Created on:
 *      Author: Supert Albert Chen & Super Sherry
 */

#include "Line.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

/**
 * This function is used to swap the coordinates of start point and end point
 *
 * @param start_p: start point
 * @param end_p: end point
 */
void SwapPoints(Point &start_p, Point &end_p) {
	std::swap(start_p.x, end_p.x);
	std::swap(start_p.y, end_p.y);
}
void exchangePoints(Point &old_point, Point &new_point){
	old_point.x=new_point.x;
	old_point.y=new_point.y;
}

/**
 * This function defines the way to draw lines according to the slop, which equals to dy/dx.
 *
 * @param slop : the slop of the line, here we use it as a parameter to judge the situation.
 * @param larger: the larger one between dx and dy.
 * @param smaller:the smaller one between dx and dy
 * @param start_p : the start point.
 * @param end_p : the end point.
 */
std::vector<PointAndColor> Line::BresenhamLine(
		int line_type,
		float larger,
		float smaller,
		Point start_p,
		Point end_p,
		Color line_color) {

	std::vector<PointAndColor> linePointColor;
	float p = 2.0f * smaller - larger;
	float dd2 = 2.0f * (smaller - larger);
	printf("In BresenHam \n");

	if (line_type == 1) {
		printf("type=1  \n");
		printf("startx = %f, starty = %f\n", start_p.x, start_p.y);
		printf("endx = %f, endy = %f\n", end_p.x, end_p.y);

		float incy = (smaller != 0.0f ? smaller / (end_p.y - start_p.y) : 0.0f);
		float dy2 = 2.0f * smaller;
		float x, y = start_p.y;
		for (x = start_p.x + 1.0f; x <= end_p.x; x += 1.0f) {
			if (p < 0) {
				glColor3f(line_color.red,line_color.green,line_color.blue);
				glVertex2i(x, y);
				//linePointColor.push_back(PointAndColor(Point(x,y), line_color));
				linePointColor.push_back(PointAndColor(Point(x,y), Color(0.0f,0.0f,0.0f)));
				printf("p =%f, x = %f, y = %f\n",p,x,y);
				p += dy2;
			} else {
				y += incy;
//				y++;
				glColor3f(line_color.red,line_color.green,line_color.blue);
				glVertex2i(x, y);
				//linePointColor.push_back(PointAndColor(Point(x,y), line_color));
				linePointColor.push_back(PointAndColor(Point(x,y), Color(0.0f,0.0f,0.0f)));
				printf("p =%f x = %f, y = %f\n",p,x,y);
				p += dd2;
			}
		}
	} else if (line_type == 2) {
//		if (start_p.y > end_p.y) {
//			SwapPoints(start_p, end_p);
//			printf("SwapPoints  \n");
//		}
		printf("type=2  \n");
		printf("startx = %f, starty = %f\n", start_p.x, start_p.y);
		printf("endx = %f, endy = %f\n", end_p.x, end_p.y);

		float incx = (smaller != 0 ? smaller / (end_p.x - start_p.x) : 0.0f);
		float dx2 = 2.0f * smaller;
		float x = start_p.x, y;
		for (y = start_p.y + 1.0f; y <= end_p.y; y += 1.0f) {
			if (p < 0) {
				glColor3f(line_color.red,line_color.green,line_color.blue);
				glVertex2i(x, y);
				//linePointColor.push_back(PointAndColor(Point(x,y), line_color));
				printf("p =%f,  x = %f, y = %f\n",p,x,y);
				linePointColor.push_back(PointAndColor(Point(x,y), Color(0.0f,0.0f,0.0f)));
				p += dx2;
			} else {
				x += incx;
				glColor3f(line_color.red,line_color.green,line_color.blue);
				glVertex2i(x, y);
				//linePointColor.push_back(PointAndColor(Point(x,y), line_color));
				printf("p =%f, x = %f, y = %f\n",p,x,y);
				linePointColor.push_back(PointAndColor(Point(x,y), Color(0.0f,0.0f,0.0f)));
				p += dd2;
			}
		}
	}

	return linePointColor;
}

//void Line::swap(float& x1, float& x2){
//	float t = x1;
//	x1 = x2;
//	x2 = t;
//}
//
//
//void Line::drawLine(float x1, float y1, float x2, float y2) {
//
//	glBegin(GL_POINTS);
//	if (x1==x2 && y1==y2) {
//		glVertex2i(x1, y1);
//		return;
//	}
//
//	if (x1>x2) {
//		swap(x1, x2);
//		swap(y1, y2);
//	}
//
//	glVertex2d(x1, y1);
//	printf("x1 = %f, y1 = %f\n",x1,y1);
//	float dy=abs(y2-y1);
//	float dx=abs(x2-x1);
//	printf("dx = %f, dy = %f\n",dx,dy);
//	if (dx>=dy) {
//		float incy=(dy!=0?dy/(y2-y1):0);
//		float p=2*dy-dx;
//		float dy2=2*dy;
//		float dd2=2*(dy-dx);
//		float x, y=y1;
//		for (x=x1+1; x<=x2; ++x) {
//			if (p<0) {
//				glVertex2i(x, y);
//				printf("p=%f, x = %f, y = %f\n",p,x,y);
//				p+=dy2;
//			}else {
//				y+=incy;
//				glVertex2i(x, y);
//				printf("p=%f, x = %f, y = %f\n",p,x,y);
//				p+=dd2;
//			}
//		}
//	}else {
//		if (y1>y2) {
//			swap(x1, x2);
//			swap(y1, y2);
//		}
//		float incx=(dx!=0?dx/(x2-x1):0);
//		float p=2*dx-dy;
//		float dx2=2*dx;
//		float dd2=2*(dx-dy);
//		float x=x1, y;
//		for (y=y1+1; y<=y2; ++y) {
//			if (p<0) {
//				glVertex2i(x, y);
//				printf("x = %f, y = %f\n",x,y);
//				p+=dx2;
//			}else {
//				x+=incx;
//				glVertex2i(x, y);
//				printf("x = %f, y = %f\n",x,y);
//				p+=dd2;
//			}
//		}
//	}
//	glEnd();
//}

/**
 * Default Line Constructor without parameters
 */
Line::Line() {
	start.update(0.0f, 0.0f);
	end.update(0.0f, 0.0f);

 	bbox = new BBox( start, end);
	transform = new Transformation(0.0f,0.0f,0.0f,0.0f,0.0f);

}

/**
 * Line Constructor with parameters
 * @param lineStart
 * @param lineEnd
 * @param color
 */
Line::Line(Point lineStart, Point lineEnd, Color color) {
	start.x = lineStart.x;
	start.y = lineStart.y;
	end.x = lineEnd.x;
	end.y = lineEnd.y;
	color = line_color;
	//line_color = lineColor;
	bbox = new BBox( start, end);

	Point translate;
	Point scale;
	float rotate;

	if (start.x == end.x && start.y == end.y){
		translate.x = start.x ;
		translate.y =  translate.x;

//		scale.x = 1.0f;
//		scale.y = 1.0f;
//
//		rotate = 1.0f;
		}
	else{

		translate.x = (start.x + end.x)/2.0f;
		translate.y = (start.y + end.y)/2.0f;

		float dy = end.y - start.y;
		float dx = end.x - start.x;
		scale.x = sqrt(pow(dy, 2.0) + pow(dx , 2.0))/2.0f;
		scale.y = scale.x;

		dx = dx/2.0f;
		if(dy > 0){
			printf("dy > 0 \n");
			rotate = acos (dx/scale.x) * 180.0f / PI;
		}
		else if(dy == 0){
			if(start.x < end.x){
				printf("dy = 0 && start.x < end.x \n");
				rotate = acos (dx/scale.x) * 180.0f / PI;
			}else{ //start.x > end.x
				printf("dy = 0 && start.x > end.x \n");
				rotate = acos (-dx/scale.x) * 180.0f / PI;
			}

		}else{
			printf("dy < 0 \n");
			rotate = acos (-dx/scale.x) * 180.0f / PI;
			//rotate = rotate - 180.0f;
		}

		transform = new Transformation(rotate, translate.x, translate.y, scale.x, scale.y);
	}
}

Line::~Line() {

}

//vmath::Tvec4<float> Line::start_vecInit(vmath::Tvec4<float> start_vec){
//	start_vec[0] = -1.0f;
//	start_vec[1] = 0.0f;
//	start_vec[2] = 0.0f;
//	start_vec[3] = 1.0f;
//
//	start_vec = start_vec * transform ->getScale() * transform ->getRotation() * transform ->getTranslation();
//	return start_vec;
//}
//vmath::Tvec4<float> Line::end_vecInit(vmath::Tvec4<float> end_vec){
//	end_vec[0] = 1.0f;
//	end_vec[1] = 0.0f;
//	end_vec[2] = 0.0f;
//	end_vec[3] = 1.0f;
//
//	end_vec = end_vec * transform ->getScale() * transform ->getRotation() * transform ->getTranslation();
//	return end_vec;
//}


/**
 *  This function judges the type of the line first and then use Breseman algorithm to draw lines.
 *
 * @param start_p: the start point
 * @param end_p: the end point
 */
std::vector<PointAndColor>  Line::draw() {

	Point start_p(-1.0f, 0.0f) ;
	Point end_p(1.0f, 0.0f) ;
	Color line_color(0.0f,0.0f,0.0f);
	std::vector<PointAndColor> linePointColor;

//	start_vec[0] = -1.0f;
//	start_vec[1] = 0.0f;
//	start_vec[2] = 0.0f;
//	start_vec[3] = 1.0f;
//
//	end_vec[0] = 1.0f;
//	end_vec[1] = 0.0f;
//	end_vec[2] = 0.0f;
//	end_vec[3] = 1.0f;

//	vmath::Tmat4<float> mat = transform ->getTranslation() * transform ->getRotation() * transform ->getScale();
//	std::cout<<"mat: "<<std::endl;
//	    for( int i = 0; i < 4; i++) {
//	        for( int j = 0; j < 4; j++) {
//	            if(j == 0) {
//	                std::cout<<"|";
//	            }
//
//	            std::cout<<" "<<mat[i][j];
//
//	            if(j == 3) {
//	                std::cout<<" |\n";
//	            }
//	        }
//	    }
//
//	start_vec = start_vec * mat;
//	end_vec =  end_vec * mat ;

//	start_vec = start_vec * transform ->getScale() * transform ->getRotation() * transform ->getTranslation();
//	end_vec = end_vec * transform ->getScale() * transform ->getRotation() * transform ->getTranslation();

//	start_vec = start_vec * transform ->getScale();
//	start_vec = start_vec * transform ->getRotation();
//	start_vec = start_vec *  transform ->getTranslation();
//
//	end_vec = end_vec * transform ->getScale();
//	end_vec = end_vec * transform ->getRotation();
//	end_vec = end_vec * transform ->getTranslation();

//	start_vec = start_vec * transform ->getTransformation();
//	end_vec = end_vec * transform ->getTransformation();
//
//	start_p.x = start_vec[0];
//	start_p.y = start_vec[1];
//	end_p.x = end_vec[0];
//	end_p.y = end_vec[1];

	start_p = transform->objToWorld(start_p);
	end_p = transform->objToWorld(end_p);

	glBegin (GL_POINTS);
	if (start_p.x == end_p.x)
	if (start_p.x > end_p.x) {
		SwapPoints(start_p , end_p);
		printf("SwapPoints  \n");
	}


	glVertex2f(start_p.x, start_p.y);
	linePointColor.push_back(PointAndColor(start, Color(0.0f,0.0f,0.0f)));
	printf("startx = %f, starty = %f\n", start_p.x, start_p.y);
	printf("endx = %f, endy = %f\n", end_p.x, end_p.y);
	float dy = fabs(end_p.y - start_p.y);
	float dx = fabs(end_p.x - start_p.x);
	if (dx >= dy) {
		// slop <=1
		std::cout<<"dx >= dy"<<std::endl;
		int line_type = 1;
		std::vector<PointAndColor> BresenhamVec = BresenhamLine(line_type, dx, dy, start_p, end_p, line_color );
		linePointColor.insert(linePointColor.end(),BresenhamVec.begin(),BresenhamVec.end());
		//linePointColor = BresenhamLine(line_type, dx, dy, start_p, end_p);

	} else {
		//slop>1
		std::cout<<"dx <= dy"<<std::endl;
		int line_type = 2;
		if (start_p.y > end_p.y) {
			SwapPoints(start_p, end_p);
			printf("SwapPoints  \n");
		}
		std::vector<PointAndColor> BresenhamVec = BresenhamLine(line_type, dy, dx, start_p, end_p, line_color);
		linePointColor.insert(linePointColor.end(),BresenhamVec.begin(),BresenhamVec.end());
		//linePointColor = BresenhamLine(line_type, dy, dx, start_p, end_p);
	}

	glEnd();

	return linePointColor;
}


/**
 * This getStart is used to get the position of the start point of the line.
 *
 */
Point Line::getStart(){
	//start.printP();
	return start;
}

/**
 * This getEnd is used to get the position of the end point of the line.
 * @return
 */
Point Line::getEnd(){
	//end.printP();
	return end;
}

/**
 * This setStart is used to set the new start point of the line, and then update the bounding box.
 * @param new_start
 */
void Line::setStart(Point new_start){
	start = new_start;
	updateBBox(start,end);
}

/**
 * This setEnd is used to set the new end point of the current line, and then update the bounding box
 * @param new_end
 */
void Line::setEnd(Point new_end){
	end=new_end;
	updateBBox(start,end);
}

/**
 * Moves object across screen.
 */
void Line::setTranslation(float xTrans, float yTrans){
	transform -> setTranslation(xTrans, yTrans);
	start = transform->objToWorld(Point(-1.0f,0.0f));
	end = transform->objToWorld(Point(1.0f,0.0f));

	updateBBox(start, end);
}

/**
 * Rotate objects in a direction
 */
void Line::setRotation(float theta){
	transform -> setRotation(theta);
	start = transform->objToWorld(Point(-1.0f,0.0f));
	end = transform->objToWorld(Point(1.0f,0.0f));
	updateBBox(start, end);
}

/**
 * Increase/Decrease size of an object
 */
void Line::setScale(float xScale, float yScale){
	transform -> setScale(xScale, yScale);
//	vmath::Tvec4<float> new_start_vec;
//	vmath::Tvec4<float> new_end_vec;
//	new_start_vec[0] = -1.0f;
//	new_start_vec[1] = 0.0f;
//	new_start_vec[2] = 0.0f;
//	new_start_vec[3] = 1.0f;
//
//
//	new_end_vec[0] = 1.0f;
//	new_end_vec[1] = 0.0f;
//	new_end_vec[2] = 0.0f;
//	new_end_vec[3] = 1.0f;
//
//	new_start_vec = new_start_vec * transform ->getTransformation();
//	new_end_vec = new_end_vec * transform ->getTransformation();
//
//	start.x = new_start_vec[0];
//	start.y = new_start_vec[1];
//	end.x = new_end_vec[0];
//	end.y = new_end_vec[1];
	start = transform->objToWorld(Point(-1.0f,0.0f));
	end = transform->objToWorld(Point(1.0f,0.0f));

	updateBBox(start, end);
}

/**
 * gets matrix of each transformation.
 *
 * @return 4x4 matrix representing transformation/translation/rotation/scale matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
void Line::getTransformation(){
	transform -> getTransformation();
}
void Line::getTranslation(){
	transform -> getTranslation();
}
void Line::getRotation(){
	transform -> getRotation();
}
void Line::getScale(){
	transform -> getScale();
}

void Line::printTransform(){
	transform -> print();
}
void Line::print(){
	bbox->print();
	printf("This line starts from (%f, %f) , ends at (%f , %f) \n", start.x, start.y,end.x,end.y);
}
