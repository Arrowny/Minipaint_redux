/*
 * Line.h
 *
 *  Created on: 2014��5��27��
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
	void draw();
	Point getStart();
	Point getEnd();
	Point setStart();
	Point setEnd();

};

#endif /* LINE_H_ */
