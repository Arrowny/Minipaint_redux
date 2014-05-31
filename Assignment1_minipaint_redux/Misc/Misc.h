/*
 * Misc.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef MISC_H_
#define MISC_H_

/**
 * Simple 2D point struct. Represents point (x,y)
 */
struct Point{
public:
	float x, y;

	Point() {
		x = 0.0;
		y = 0.0;
	}

	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void update(float x, float y) {
		this->x = x;
		this->y = y;
	}

	bool isApproxEqual(Point b) {
		if( (b.x <= x + .00001) && (b.x >= x -.00001)
			&&
			(b.y <= y + .00001) && (b.y >= y -.00001) )
		{return true;}
		else
		{return false;}
	}
	void printP(){
		std::cout<<"The Point is: ( "<<x<<" , "<<y<<" )"<<std::endl;
	}

	//TODO Add assignment, addition, subtraction, multiplication operations if time allows

};

struct Color {
public:
	float red, green, blue;

	Color(float red, float green, float blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}
};

struct PointAndColor {
public:
	Point point;
	Color color;

	PointAndColor(Point point, Color color) {
		this->point = point;
		this->color = color;
	}
};

#endif /* MISC_H_ */
