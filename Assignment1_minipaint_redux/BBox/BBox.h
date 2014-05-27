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
	vert min;
	vert max;
public:
	BBox();
	BBox(vert)
	~BBox();

};

#endif /* BBOX_H_ */
