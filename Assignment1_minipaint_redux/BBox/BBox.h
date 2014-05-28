/*
 * BBox.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef BBOX_H_
#define BBOX_H_

class BBox {
private:
	Point min;
	Point max;
public:
	BBox();
	BBox(Point min, Point max);
	~BBox();
	bool unionBBox(BBox uBox);
	bool insideBBox(Point testPt);
	void expandBBox(float expX, float expY);
};

#endif /* BBOX_H_ */
