/*
 * Canvas.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#include "Canvas.h"

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
						std::pair<int,int> 							fillLocation) {
		std::map<std::pair<int,int>,PointAndColor>::iterator it;

		//find iterator to point to check if point is occupied if occupied clear point
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
		PointAndColor newFill = PointAndColor(fillPoint,fillColor);
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
	void updateBoundaryPoints(	std::map<std::pair<int,int>, bool> 	&boundaryPoints,
								Object* 							Obj) {
		std::vector<PointAndColor> boundaryPAC = Obj->draw();
		for(int ii = 0; ii < boundaryPAC.size(); ii++) {
			setAsBoundary(boundaryPoints ,boundaryPAC[ii].point);
		}
	}

	void updateVariablesUsingObject(	Object* updateObj, BBox* 				&bbox,
										std::vector<Object*> 					&drawableObjects,
										std::map<std::pair<int,int>, bool> 		&boundaryPoints) {

		//update drawable objects, bbox, and boundary points using new object
		drawableObjects.push_back(updateObj);
		*bbox = bbox->unionBBox(updateObj->getBBox());
		updateBoundaryPoints(boundaryPoints,updateObj);
	}

	/**
	 * transform all the fill points of the canvas
	 *
	 * @param transform Tmat4<float>
	 * @param fillStartPointMap
	 * @return
	 */
	std::map<std::pair<int,int>, PointAndColor>
	transformFillPoints(vmath::Tmat4<float> 							transform,
						std::map<std::pair<int,int>, PointAndColor> 	fillStartPointMap) {
		std::map<std::pair<int,int>,PointAndColor>::iterator it;
		std::map<std::pair<int,int>, PointAndColor> newFSPMap;

		//transform fill points using transformation transform
		for(it = fillStartPointMap.begin(); it != fillStartPointMap.end(); it++) {
			Point fillPoint = (*it).second.point;
			Color fillColor = (*it).second.color;
			Point newFillPoint = fillPoint.transform(transform);
			setFillPoint(newFSPMap,fillColor,newFillPoint);
		}

		return newFSPMap;
	}

}

Canvas::Canvas() {
	// TODO Auto-generated constructor stub
}

Canvas::Canvas(Object* initialObject) {
	bbox = new BBox();
	updateVariablesUsingObject(initialObject,bbox,drawableObjects,boundaryPoints);
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

std::vector<PointAndColor> Canvas::reapplyAllFills() {
	std::vector<PointAndColor> coloredPoints;
	std::vector<PointAndColor> takePACs;

	std::map<std::pair<int,int>,PointAndColor>::iterator it;
	for(it = fillStartPointMap.begin(); it != fillStartPointMap.end(); it++){
		takePACs = fill((*it).second);
		coloredPoints.insert(coloredPoints.end(),takePACs.begin(),takePACs.end());
	}

	return coloredPoints;
}

void Canvas::setScale(float xScale, float yScale) {

	//calculate pipe line for rotation
	Point canvasCenter = bbox->getCenter();
	vmath::Tmat4<float> translation		= vmath::translate(- canvasCenter.x, - canvasCenter.y, 0.0f);
	vmath::Tmat4<float> scale			= vmath::scale(xScale,yScale,1.0f);
	vmath::Tmat4<float> invTranslation	= vmath::translate(  canvasCenter.x,   canvasCenter.y, 0.0f);
	vmath::Tmat4<float> tPipeline		= translation*scale*invTranslation;

	//transform all objects
	boundaryPoints.clear();	//boundary points must be reinitialized
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		Point objCenter = drawableObjects[ii]->getCenter();
		Point translatedCenter = objCenter.transform(tPipeline);
		drawableObjects[ii]->setTranslation(translatedCenter.x,translatedCenter.y);
		drawableObjects[ii]->setScale(xScale,yScale);
		updateBoundaryPoints(boundaryPoints,drawableObjects[ii]);
	}

	//updateBBox
	bbox = new BBox();
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		bbox->unionBBox(drawableObjects[ii]->getBBox());
	}

	fillStartPointMap = transformFillPoints(tPipeline,fillStartPointMap);
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
	vmath::Tmat4<float> translation = vmath::translate(xTrans - canvasCenter.x, yTrans - canvasCenter.y, 0.0f);

	//transform all objects
	boundaryPoints.clear();	//boundary points must be reinitialized
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		Point objCenter = drawableObjects[ii]->getCenter();
		Point translatedCenter = objCenter.transform(translation);
		drawableObjects[ii]->setTranslation(translatedCenter.x,translatedCenter.y);
		updateBoundaryPoints(boundaryPoints,drawableObjects[ii]);
	}

	//updateBBox
	bbox = new BBox();
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		bbox->unionBBox(drawableObjects[ii]->getBBox());
	}

	fillStartPointMap = transformFillPoints(translation,fillStartPointMap);
}

void Canvas::setRotation(float theta) {

	//calculate pipe line for rotation
	Point canvasCenter = bbox->getCenter();
	vmath::Tmat4<float> translation		= vmath::translate(- canvasCenter.x, - canvasCenter.y, 0.0f);
	vmath::Tmat4<float> rotation		= vmath::rotate(theta,0.0f,0.0f,1.0f);
	vmath::Tmat4<float> invTranslation	= vmath::translate(  canvasCenter.x,   canvasCenter.y, 0.0f);
	vmath::Tmat4<float> tPipeline		= translation*rotation*invTranslation;

	//transform all objects
	boundaryPoints.clear();	//boundary points must be reinitialized
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		Point objCenter = drawableObjects[ii]->getCenter();
		Point translatedCenter = objCenter.transform(tPipeline);
		drawableObjects[ii]->setTranslation(translatedCenter.x,translatedCenter.y);
		drawableObjects[ii]->setRotation(theta);
		updateBoundaryPoints(boundaryPoints,drawableObjects[ii]);
	}

	//updateBBox
	bbox = new BBox();
	for(int ii = 0; ii < drawableObjects.size(); ii++) {
		bbox->unionBBox(drawableObjects[ii]->getBBox());
	}

	fillStartPointMap = transformFillPoints(tPipeline,fillStartPointMap);
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
 * add a new object to canvas
 *
 * @param newObj object pointer to new object to be added
 */
void Canvas::add(Object* newObj) {
	updateVariablesUsingObject(newObj,bbox,drawableObjects,boundaryPoints);
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
	std::map<std::pair<int,int>,bool>::iterator it;
	it = boundaryPoints.find(chkLocation);
	return (it != boundaryPoints.end());
}

void Canvas::print() {

	std::cout<<std::endl;
	std::cout<<"//////////////////////BBox Information: //////////////////////"<<std::endl;
	std::cout<<std::endl;

	bbox->print();


	std::cout<<std::endl;
	std::cout<<"//////////////////////Object Information: //////////////////////"<<std::endl;
	std::cout<<std::endl;

	for(int ii = 0; ii < drawableObjects.size();ii++) {
		drawableObjects[ii]->print();
	}

	std::cout<<"Fill information"<<std::endl;
	std::map<std::pair<int,int>,PointAndColor>::iterator it;
	Point fillPoint;
	Color fillColor;
	for(it = fillStartPointMap.begin(); it != fillStartPointMap.end(); it++){
		fillPoint = (*it).second.point;
		fillColor = (*it).second.color;
		std::cout<<"("<<fillPoint.x<<","<<fillPoint.y<<"): ";
		std::cout<<"red: "	<<fillColor.red
				 <<"green: "<<fillColor.green
				 <<"blue: "	<<fillColor.blue<<std::endl;
	}
}

