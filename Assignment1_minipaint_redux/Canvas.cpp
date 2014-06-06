/*
 * Canvas.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#include "Canvas.h"

#include <BBox.h>
#include <stddef.h>
#include <map>
#include <utility>
#include <vector>

namespace {

	/**
	 * calculate the BBox representing the Point and Color vector passed to the function
	 *
	 * @param PAC Point and Color array
	 * @return BBox representing the boundaries of PAC vector
	 */
	BBox calculatePACBBox(std::vector<PointAndColor> PAC) {
		Point unionPt;
		BBox PACBBox;
		for(int ii = 0; ii < PAC.size(); ii++) {
			unionPt = PAC[ii].point;
			PACBBox.unionBBox(unionPt);
		}
		return PACBBox;
	}

	/**
	 * check to see if a fill point and Color was stored at fill location. If so erase.
	 *
	 * @param fillStartPointMap fill map to check for prexisiting PAC
	 * @param fillLocation	location on fill map to check against
	 */
	void clearFillPoint(std::map<std::pair<int,int>, PointAndColor> &fillStartPointMap,
						std::pair<int,int> fillLocation) {
		std::map<std::pair<int,int>,PointAndColor>::iterator it;

		//
		it = fillStartPointMap.find(fillLocation);
		if(it != fillStartPointMap.end()) {
			fillStartPointMap.erase(fillLocation);
		}
	}

	/**
	 * Sets a new fill at position fillPoint with color fillColor
	 *
	 * @param fillStartPointMap fill map that will be updated with new fill information
	 * @param fillColor	color at new fill point
	 * @param fillPoint location of new fill point
	 */
	void setFillPoint(std::map<std::pair<int,int>, PointAndColor> &fillStartPointMap, Color fillColor, Point fillPoint) {
		const std::pair<int,int> fillLocation(fillPoint.x,fillPoint.y);
		std::pair<std::pair<int,int>,PointAndColor> newFill(fillLocation,PointAndColor(fillPoint,fillColor));
		clearFillPoint(fillStartPointMap,fillLocation);
		fillStartPointMap[fillLocation] = newFill; //set new fill in empty fill slot
	}


	/**
	 * sets point boundPt as a boundary point in boundaryPoints
	 *
	 * @param boundaryPoints map of current boundary points
	 * @param boundPt new boundary point
	 */
	void setAsBoundary( std::map<std::pair<int,int>, bool> &boundaryPoints , Point boundPt) {
		std::pair<int,int> boundLocation(boundPt.x,boundPt.y);
		boundaryPoints[boundLocation] = true;
	}

	/**
	 * set new boundary points according to Object Obj
	 *
	 * @param boundaryPoints map representing the boundary points of the Object Obj
	 * @param Obj Object that will be used to find boundary points
	 */
	void updateBoundaryPoints(	std::map<std::pair<int,int>, bool> &boundaryPoints,
								Object* Obj) {
		std::vector<PointAndColor> boundaryPAC = Obj->draw();
		for(int ii = 0; ii < boundaryPAC.size(); ii++) {
			setAsBoundary(boundaryPoints ,boundaryPAC[ii].point);
		}
	}

	void updateVariablesUsingObject(	Object* updateObj, BBox* &bbox,
										std::vector<Object*> &drawableObjects,
										std::map<std::pair<int,int>, bool> &boundaryPoints) {

		//update drawable objects, bbox, and boundary points using new object
		drawableObjects.push_back(updateObj);
		bbox->unionBBox(updateObj->getBBox());
		updateBoundaryPoints(boundaryPoints,updateObj);
	}

}

Canvas::Canvas() {
	// TODO Auto-generated constructor stub
}

Canvas::Canvas(Object* initialObject) {
	bbox = new BBox();
	updateVariablesUsingObject(initialObject,bbox,drawableObjects,boundaryPoints)
}

Canvas::Canvas(std::vector<Object*> initialObjs) {
	for(int ii = 0; ii < initialObjs.size(); ii++) {
		updateVariablesUsingObject(initialObjs[ii],bbox,drawableObjects,boundaryPoints);
	}
}

/**
 * draw all objects to canvas
 *
 * @return vector of Points and Colors representing all the boundary points of all of the objects on the canvas
 */
std::vector<PointAndColor> Canvas::draw() {

	std::vector<PointAndColor> objPACs;	//object Point and Color vector
	std::vector<PointAndColor> accPACs; //accumulate Point and Color vector
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		objPACs = drawableObjects[ii]->draw();
		accPACs.insert(accPACs.end(), objPACs.begin(), objPACs.end());
	}
	return accPACs;
}

/**
 * fills until boundary (ie the lines of the objects) a color passed in using floodfill algorithm
 *
 * @param fillPoint Point at which fill is called
 * @param fillColor color at fill point
 */
std::vector<PointAndColor> Canvas::fill(PointAndColor fillPAC) {
	std::vector<PointAndColor> coloredPoints;

	Point fillPoint = fillPAC.point;
	Color fillColor = fillPAC.color;
	std::pair<int,int> fillLocation(fillPoint.x, fillPoint.y);

	//occupied points cannot be filled
	if(!isOccupied(fillLocation)) {
		std::map<std::pair<int,int>, bool> locationColored;

		coloredPoints.push_back(fillPAC);						//add fill Point and Color to vector
		setFillPoint(fillStartPointMap, fillColor, fillPoint); 	//set a new fill point
		locationColored[fillLocation] = true;					//mark location as colored

		std::pair<int,int> north(fillLocation.first,fillLocation.second+1);
		std::pair<int,int> south(fillLocation.first,fillLocation.second-1);
		std::pair<int,int> east (fillLocation.first+1,fillLocation.second);
		std::pair<int,int> west (fillLocation.first-1,fillLocation.second);

		fill_helper(north,locationColored,fillColor,coloredPoints);
		fill_helper(south,locationColored,fillColor,coloredPoints);
		fill_helper(east ,locationColored,fillColor,coloredPoints);
		fill_helper(west ,locationColored,fillColor,coloredPoints);
	}

	return coloredPoints;
}

/**
 * recursive flood fill
 *
 * @param fillLocation location of start of this recursion
 * @param locationColored map of already colored locations
 * @param fillColor	color of floodfill
 * @param coloredPoints	vector representing all of the filled points and the colors at those points
 */
void Canvas::fill_helper(	std::pair<int,int> fillLocation,
							std::map<std::pair<int,int>, bool> &locationColored,
							Color fillColor,
							std::vector<PointAndColor> &coloredPoints) {

	Point fillPoint(fillLocation.first,fillLocation.second);
	PointAndColor fillPAC(fillPoint,fillColor);

	//end recursion if point represents a boundary point or the location has alread been colored
	if(!isOccupied(fillLocation) && !locationColored[fillLocation]) {
		coloredPoints.push_back(fillPAC); 				//add new fill point to vector
		clearFillPoint(fillStartPointMap,fillLocation);	//remove fill point to prevent filling with incorrect color after transformation
		locationColored[fillLocation] = true;			//mark location as colored

		std::pair<int,int> north(fillLocation.first,fillLocation.second+1);
		std::pair<int,int> south(fillLocation.first,fillLocation.second-1);
		std::pair<int,int> east (fillLocation.first+1,fillLocation.second);
		std::pair<int,int> west (fillLocation.first-1,fillLocation.second);

		//recurse
		fill_helper(north,locationColored,fillColor,coloredPoints);
		fill_helper(south,locationColored,fillColor,coloredPoints);
		fill_helper(east ,locationColored,fillColor,coloredPoints);
		fill_helper(west ,locationColored,fillColor,coloredPoints);
	}
}

void Canvas::setScale(float xScale, float yScale) {
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		drawableObjects[ii]->setScale(xScale,yScale);
	}

	//TODO: address scaling and refill
}

/**
 * sets the position of the canvas to xTrans yTrans
 *
 * @param xTrans new x position of canvas
 * @param yTrans new y position of canvas
 */
void Canvas::setTranslation(float xTrans, float yTrans) {

	//calculate needed pipeline to reach (xTrans,yTrans)
	Point canvasCenter = bbox->getCenter();
	vmath::Tmat4<float> Translation = vmath::translate(xTrans - canvasCenter.x, yTrans - canvasCenter.y, 0.0f);

	//transform all objects
	boundaryPoints.clear();	//boundary points must be reinitialized
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		Point objCenter = drawableObjects[ii]->getCenter();
		Point translatedCenter = objCenter.transform(Translation);
		drawableObjects[ii]->setTranslation(translatedCenter.x,translatedCenter.y);
		updateBoundaryPoints(boundaryPoints,drawableObjects[ii]);
	}

	//updateBBox
	bbox = new BBox();
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		bbox->unionBBox(drawableObjects[ii]->getBBox());
	}

	//transform all fill points
	std::map<std::pair<int,int>,PointAndColor>::iterator it;
	std::map<std::pair<int,int>, PointAndColor> newFSPMap;
	for(it = fillStartPointMap.begin(); it != fillStartPointMap.end(); it++) {
		Point fillPoint = (*it).second.point;
		Color fillColor = (*it).second.color;
		Point newFillPoint = fillPoint.transform(Translation);
		setFillPoint(newFSPMap,fillColor,newFillPoint);
	}

	fillStartPointMap = newFSPMap;
}

void Canvas::setRotation(float theta) {
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		drawableObjects[ii]->setRotation(theta);
	}

	//TODO: address rotation and refill
}

/**
 * check if point is inside bounding box of canvas
 *
 * @param a point to perform insideness test on
 * @return boolean representing whether or not point is inside bounding box of canvas
 */
bool Canvas::inside(Point a) {
	return bbox->insideBBox(a);
}

/**
 * return the center of the canvas object
 *
 * @return Point representing the center of the canvas object
 */
Point Canvas::getCenter() {
	bbox->getCenter();
}

Canvas::~Canvas() {
	// TODO Auto-generated destructor stub
}

////////////////Private functions///////////////////////

/**
 * Check if a location is occupied
 *
 * @param chkLocation point of ints representing location to be checked
 * @return bool representing whether or not location is occupied
 */
bool Canvas::isOccupied(std::pair<int,int> chkLocation) {
	std::map<std::pair<int,int>,PointAndColor>::iterator it;
	it = boundaryPoints.find(chkLocation);
	return (it != boundaryPoints.end());
}

