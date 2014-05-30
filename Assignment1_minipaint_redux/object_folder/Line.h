/*
 * Line.h
 *
 *  Created on: 2014Äê5ÔÂ27ÈÕ
 *      Author: yellow
 */

#ifndef LINE_H_
#define LINE_H_

#include "object.h"

class Line: public Object {

private:
	Point start;
	Point end;
public:

	Line();
	Line(Point lineStart, Point lineEnd);
	virtual ~Line();
	/**
	 * inherit object draw function. Draws lines to screen
	 */
	void draw();

	/**
	 * get the position of start point and return its coordinate.
	 * @return: its coordinate
	 */
	Point getStart();

	/**
	 * get the position of end point and return its coordinate.
	 * @return: its coordinate
	 */
	Point getEnd();

	/**
	 * set a new start point of the current line.
	 * @param new_start: the coordinate of the new start point
	 */
	void setStart(Point new_start);

	/**
	 * set a new end point of the current line.
	 * @param new_end: the coordinate of the new end point
	 */
	void setEnd( Point new_end);

	/**
	 * Moves object across screen.
	 */
	void setTranslation(float xTrans, float yTrans) = 0;

	/**
	 * Rotate objects in a direction
	 */
	void setRotation(float theta) = 0;

	/**
	 * Increase/Decrease size of an object
	 */
	void setScale(float xScale, float yScale) = 0;

};

#endif /* LINE_H_ */
