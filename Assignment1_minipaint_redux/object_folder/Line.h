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
	std::vector<PointAndColor> draw();
	Point getStart();
	Point getEnd();
	void setStart(Point new_start);
	void setEnd( Point new_end);

};

#endif /* LINE_H_ */
