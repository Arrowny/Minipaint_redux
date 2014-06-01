/*
 * Ellipse.h
 *
 *  Created on: 2014��5��29��
 *      Author: yellow
 */

#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "Object.h"

class Ellipse: public Object {
private:
	Point start;
	Point end;

public:
	Ellipse();
	Ellipse(Point ellStart, Point ellEnd);
	~Ellipse();
	std::vector<PointAndColor> draw();
	void update(Point ellStart, Point ellEnd);
	void setTranslation(float xTrans, float yTrans);
	void setRotation(float theta);
	void setScale(float xScale, float yScale);
	void getTranslation();
	void getRotation();
	void getScale();


};

#endif /* ELLIPSE_H_ */
