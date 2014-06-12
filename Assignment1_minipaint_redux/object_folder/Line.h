/*
 * Line.h
 *
 *  Created on:
 *      Author: Super Albert Chen & Super Sherry
 */

#ifndef LINE_H_
#define LINE_H_

#include "object.h"

class drawableLine: public Object {
public:
//private:
	Point start;
	Point end;
	Color line_color;

	Point translate;
	Point scale;
	float rotate;

	vmath::Tvec4<float> start_vec;
	vmath::Tvec4<float> end_vec;
//public:

	drawableLine();
	//Line(Point lineStart, Point lineEnd, Color line_color);
	drawableLine(Point lineStart, Point lineEnd, Color color);
	virtual ~drawableLine();
	void UpdateTransformation(Point lineStart, Point lineEnd, Color color);

	/**
	 * inherit object draw function. Draws lines to screen
	 */
	std::vector<PointAndColor>  draw();



	/**
	 * The Algorithm of drawing a line
	 *
	 * @param line_type
	 * @param larger
	 * @param smaller
	 * @param start_p
	 * @param end_p
	 * @return
	 */
	std::vector<PointAndColor> BresenhamLine(
			int line_type,
			float larger,
			float smaller,
			Point start_p,
			Point end_p,
			Color line_color);

	/**
	 *
	 * @param x1
	 * @param x2
	 */
	void swap(float& x1, float& x2);

	/**
	 *
	 * @param x1
	 * @param y1
	 * @param x2
	 * @param y2
	 */
	void drawLine(float x1, float y1, float x2, float y2);

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
	void setTranslation(float xTrans, float yTrans);

	/**
	 * Rotate objects in a direction
	 */
	void setRotation(float theta);

	/**
	 * Increase/Decrease size of an object
	 */
	void setScale(float xScale, float yScale);

	/**
		 * gets matrix of each transformation.
		 *
		 * @return 4x4 matrix representing transformation/translation/rotation/scale matrix of transformation.
		 * Note: this transformation requires that points be represented in the form
		 * 		 [x,y,0.0f,1.0f].
		 */
	void getTransformation();
	void getTranslation();
	void getRotation();
	void getScale();
	void printTransform();
	void print();
};

#endif /* LINE_H_ */
