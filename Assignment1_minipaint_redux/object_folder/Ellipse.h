/*
 * Ellipse.h
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "object.h"

class drawableEllipse: public Object {

private:
	Point start;
	Point end;
	Point color;

public:
	drawableEllipse();
	drawableEllipse(Point ellStart, Point ellEnd);
	virtual ~drawableEllipse();
	std::vector<PointAndColor> draw();
	void update(Point ellStart, Point ellEnd);
	void setTranslation(float xTrans, float yTrans);
	void setRotation(float theta);
	void setScale(float xScale, float yScale);
	vmath::mat4 getTransformation();
	vmath::mat4 getTranslation();
	vmath::mat4 getRotation();
	vmath::mat4 getScale();
	void PrintTransform();
	Point getMax();
	Point getMin();
	void print();


};

#endif /* ELLIPSE_H_ */
