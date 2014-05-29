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
};



#endif /* MISC_H_ */
