/*
 * BBox.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef BBOX_H_
#define BBOX_H_

/**
 * Generates a 2D box with that streches from Point min(x,y) to Point max(x,y)
 */
class BBox {
private:
	Point min;
	Point max;
public:
	BBox();
	BBox(Point min, Point max);
	~BBox();
	//BBox& BBox::operator=( const BBox& other );
	BBox unionBBox(Point uPoint);
	BBox unionBBox(BBox uBox);
	BBox expandBBox(float expX, float expY);
	bool insideBBox(Point testPt);
	Point getMin() const;
	Point getMax() const;
};

#endif /* BBOX_H_ */