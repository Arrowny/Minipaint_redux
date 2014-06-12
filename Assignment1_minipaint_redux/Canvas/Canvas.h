/*
 * Canvas.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef CANVAS_H_
#define CANVAS_H_
#include <iostream>
#include <map>
#include <BBox.h>
#include <stddef.h>
#include <utility>
#include <vector>
#include <queue>
#include "Misc.h"
#include "Object.h"
#include "vmath.h"


class Canvas {

private:
	BBox* bbox;
	std::vector<Object*> drawableObjects;
	std::map<std::pair<int,int>, PointAndColor> fillStartPointMap;
	std::map<std::pair<int,int>, bool> boundaryPoints;

	void fill_helper(	std::pair<int,int> fillLocation,
						std::vector<std::vector<bool> > &locationColored,
						Color fillColor,
						std::vector<PointAndColor> &coloredPoints,
						int width, int height);
	bool isOccupied(std::pair<int,int> chkLocation);
public:
	Canvas();
	Canvas(Object* initialObj);
	Canvas(std::vector<Object*> initialObjs);
	std::vector<PointAndColor> draw();
	std::vector<PointAndColor> fill(PointAndColor fillPAC, int width, int height);
	std::vector<PointAndColor> reapplyAllFills(int width, int height);
	void setScale(float xScale, float yScale);
	void setTranslation(float xTrans, float yTrans);
	void setRotation(float theta, Point canvasCenter);
	Point getCenter();
	BBox getBBox();
	bool inside(Point a);
	void add(Object* newObj);
	void print();
	virtual ~Canvas();
};

#endif /* CANVAS_H_ */
