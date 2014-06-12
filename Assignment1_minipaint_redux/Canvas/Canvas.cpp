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
		clearFillPoint(fillStartPointMap,fillLocation);
		PointAndColor newFill(fillPoint,fillColor);
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

	/**
	 * Check to see if fill location is colored or not
	 *
	 * @param locationColored map representing all currently colored locations
	 * @param fillLocation location to check for coloredness
	 * @return bool representing whether or not fillLocation was colored
	 */
	bool isColored(std::map<std::pair<int,int>, bool> locationColored,std::pair<int,int> fillLocation) {
		std::map<std::pair<int,int>,bool>::iterator it;
		it = locationColored.find(fillLocation);
		bool chkColored = (it != locationColored.end());
		return chkColored;
	}

	bool isOutOfBounds(std::pair<int,int> fillLocation, int width, int height) {
		int xLoc = fillLocation.first;
		int yLoc = fillLocation.second;
		return 	!((xLoc < width  ) && (xLoc > 0)	&& (yLoc < height )	&& (yLoc > 0));
	}
}

Canvas::Canvas() {
	bbox = new BBox();
}

Canvas::Canvas(Object* initialObject) {
	bbox = new BBox();
	updateVariablesUsingObject(initialObject,bbox,drawableObjects,boundaryPoints);
}

Canvas::Canvas(std::vector<Object*> initialObjs) {
	bbox = new BBox();
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
 * recursive flood fill
 *
 * @param fillLocation location of start of this recursion
 * @param locationColored map of already colored locations
 * @param fillColor	color of floodfill
 * @param width screen width
 * @param height screen height
 * @param coloredPoints	vector representing all of the filled points and the colors at those points
 */
void Canvas::fill_helper(	std::pair<int,int> fillLocation,
							std::vector<std::vector<bool> > &locationColored,
							Color fillColor,
							std::vector<PointAndColor> &coloredPoints,
							int width, int height) {

	int xLoc = fillLocation.first;
	int yLoc = fillLocation.second;
	Point fillPoint(fillLocation.first,fillLocation.second);
	PointAndColor fillPAC(fillPoint,fillColor);

	//end recursion if point represents a boundary point or the location has already been colored
	if(	!isOccupied(fillLocation) 	&&
		(xLoc < width  )			&&
		(xLoc > 0)				&&
		(yLoc < height )			&&
		(yLoc > 0)			) {

		if (!locationColored[xLoc][yLoc]) {
			coloredPoints.push_back(fillPAC); 				//add new fill point to vector
			clearFillPoint(fillStartPointMap,fillLocation);	//remove fill point to prevent filling with incorrect color after transformation
			locationColored[xLoc][yLoc] = true;			//mark location as colored


			std::pair<int,int> north(fillLocation.first,fillLocation.second+1);
			std::pair<int,int> south(fillLocation.first,fillLocation.second-1);
			std::pair<int,int> east (fillLocation.first+1,fillLocation.second);
			std::pair<int,int> west (fillLocation.first-1,fillLocation.second);

			//recurse
			fill_helper(north,locationColored,fillColor,coloredPoints,width,height);
			fill_helper(south,locationColored,fillColor,coloredPoints,width,height);
			fill_helper(east ,locationColored,fillColor,coloredPoints,width,height);
			fill_helper(west ,locationColored,fillColor,coloredPoints,width,height);

		}
	}
}

/**
 * fills until boundary (ie the lines of the objects) a color passed in using floodfill algorithm
 *
 * @param fillPoint Point at which fill is called
 * @param fillColor color at fill point
 * @param width screen width
 * @param height screen height
 */
std::vector<PointAndColor> Canvas::fill(PointAndColor fillPAC, int width, int height) {

	std::vector<PointAndColor> coloredPoints;
	Point fillPoint = fillPAC.point;
	Color fillColor = fillPAC.color;
	int xLoc = fillPoint.x;
	int yLoc = fillPoint.y;
	std::pair<int,int> fillLocation(xLoc, yLoc);
	std::queue<std::pair<int,int> > fillLocations;

	if(	!isOccupied(fillLocation) 	&&
		!isOutOfBounds(fillLocation,width,height)) {

		std::vector<std::vector<bool> > locationColored(width,std::vector<bool>(height,false));

		locationColored[xLoc][yLoc] = true;						//mark location as colored
		coloredPoints.push_back(fillPAC);						//add fill Point and Color to vector
		setFillPoint(fillStartPointMap, fillColor, fillPoint); 	//set a new fill point

		std::pair<int,int> north(fillLocation.first,fillLocation.second+1);
		std::pair<int,int> south(fillLocation.first,fillLocation.second-1);
		std::pair<int,int> east (fillLocation.first+1,fillLocation.second);
		std::pair<int,int> west (fillLocation.first-1,fillLocation.second);

		fillLocations.push(north);
		fillLocations.push(south);
		fillLocations.push(east);
		fillLocations.push(west);

		while(!fillLocations.empty()) {
			fillLocation = fillLocations.front();
			fillLocations.pop();

			if(	!isOccupied(fillLocation) 	&&
				!isOutOfBounds(fillLocation,width,height)) {

				xLoc = fillLocation.first;
				yLoc = fillLocation.second;

				if(!locationColored[xLoc][yLoc]) {

					fillPoint = Point(xLoc,yLoc);
					fillPAC = PointAndColor(fillPoint,fillColor);

					locationColored[xLoc][yLoc] = true;				//mark location as colored
					coloredPoints.push_back(fillPAC);				//add fill Point and Color to vector
					clearFillPoint(fillStartPointMap,fillLocation); //set a new fill point

					north = std::make_pair(fillLocation.first,fillLocation.second+1);
					south = std::make_pair(fillLocation.first,fillLocation.second-1);
					east  = std::make_pair(fillLocation.first+1,fillLocation.second);
					west  = std::make_pair(fillLocation.first-1,fillLocation.second);

					fillLocations.push(north);
					fillLocations.push(south);
					fillLocations.push(east);
					fillLocations.push(west);
				}
			}
		}
	}
}

/**
 * fills until boundary (ie the lines of the objects) a color passed in using floodfill algorithm
 *
 * @param fillPoint Point at which fill is called
 * @param fillColor color at fill point
 * @param width screen width
 * @param height screen height

std::vector<PointAndColor> Canvas::fill(PointAndColor fillPAC, int width, int height) {

	std::vector<PointAndColor> coloredPoints;
	Point fillPoint = fillPAC.point;
	Color fillColor = fillPAC.color;
	int xLoc = fillPoint.x;
	int yLoc = fillPoint.y;
	std::pair<int,int> fillLocation(xLoc, yLoc);

	//occupied points cannot be filled. Points outside of screen cannot be filled
	if(	!isOccupied(fillLocation) 	&&
		(xLoc < width)				&&
		(xLoc > 0)					&&
		(yLoc < height)				&&
		(yLoc > 0)			) {

		std::vector<std::vector<bool> > locationColored(width,std::vector<bool>(height,false));
		locationColored[xLoc][yLoc] = true;						//mark location as colored
		coloredPoints.push_back(fillPAC);						//add fill Point and Color to vector
		setFillPoint(fillStartPointMap, fillColor, fillPoint); 	//set a new fill point

		std::pair<int,int> north(fillLocation.first,fillLocation.second+1);
		std::pair<int,int> south(fillLocation.first,fillLocation.second-1);
		std::pair<int,int> east (fillLocation.first+1,fillLocation.second);
		std::pair<int,int> west (fillLocation.first-1,fillLocation.second);

		fill_helper(north,locationColored,fillColor,coloredPoints,width,height);
		fill_helper(south,locationColored,fillColor,coloredPoints,width,height);
		fill_helper(east ,locationColored,fillColor,coloredPoints,width,height);
		fill_helper(west ,locationColored,fillColor,coloredPoints,width,height);
	}

	return coloredPoints;
}
 */

std::vector<PointAndColor> Canvas::reapplyAllFills(int width, int height) {
	std::vector<PointAndColor> coloredPoints;
	std::vector<PointAndColor> takePACs;

	std::map<std::pair<int,int>,PointAndColor>::iterator it;
	for(it = fillStartPointMap.begin(); it != fillStartPointMap.end(); it++){
		takePACs = fill((*it).second,width,height);
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
	vmath::Tmat4<float> tPipeline		= invTranslation*scale*translation;

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
		*bbox = bbox->unionBBox(drawableObjects[ii]->getBBox());
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
		*bbox = bbox->unionBBox(drawableObjects[ii]->getBBox());
	}

	fillStartPointMap = transformFillPoints(translation,fillStartPointMap);
}

void Canvas::setRotation(float theta, Point canvasCenter) {

	//calculate pipe line for rotation
	vmath::Tmat4<float> translation		= vmath::translate(- canvasCenter.x, - canvasCenter.y, 0.0f);
	vmath::Tmat4<float> rotation		= vmath::rotate(theta,0.0f,0.0f,1.0f);
	vmath::Tmat4<float> invTranslation	= vmath::translate(  canvasCenter.x,   canvasCenter.y, 0.0f);
	vmath::Tmat4<float> tPipeline		= invTranslation*rotation*translation;

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
		*bbox = bbox->unionBBox(drawableObjects[ii]->getBBox());
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

BBox Canvas::getBBox() {
	return *bbox;
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
	bool chkOccupied = (it != boundaryPoints.end());
	return chkOccupied;
}

void Canvas::print() {
	std::cout<<"\n\n//////////////////////BBox Information: //////////////////////"<<std::endl;
	bbox->print();

	std::cout<<"\n\n//////////////////////Object Information: //////////////////////"<<std::endl;

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

