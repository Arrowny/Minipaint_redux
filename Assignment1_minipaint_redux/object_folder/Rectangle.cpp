/*
 * Rectangle.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Rectangle.h"

Rectangle::Rectangle() {
	// TODO Auto-generated constructor stub

}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

/*Draw rectangle, for now we can only draw in one direction*/

void Rectangle(Point start_p, Point end_p) {
	glBegin(GL_LINES);
		glVertex2f(start_p.x,start_p.y);
		glVertex2f(end_p.x,start_p.y);
		glVertex2f(end_p.x,start_p.y);
		glVertex2f(end_p.x,end_p.y);
		glVertex2f(end_p.x,end_p.y);
		glVertex2f(start_p.x,end_p.y);
		glVertex2f(start_p.x,end_p.y);
		glVertex2f(start_p.x,start_p.y);

	glEnd();
}
