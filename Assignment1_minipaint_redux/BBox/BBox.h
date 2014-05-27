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
	void expand(float );
};

#endif /* BBOX_H_ */
