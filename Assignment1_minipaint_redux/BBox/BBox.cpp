/*
 * BBox.cpp
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#include "BBox.h"

namespace {

	/**
	 * Find the min max x values
	 *
	 * @param a first point
	 * @param b second point
	 * @param min pointer to the address of min point
	 * @param max pointer to the address of max point
	 * @return void
	 */
	void setMinMaxX(Point a, Point b, Point &min, Point &max) {
		if (a.x <= b.x) {
			min.x = a.x;
			max.x = b.x;
		} else {
			min.x = b.x;
			max.x = a.x;
		}
	}

	/**
	 * Find the world min max y values
	 *
	 * @param a first point
	 * @param b second point
	 * @param min pointer to the address of min point
	 * @param max pointer to the address of max point
	 * @return void
	 */
	void setMinMaxY(Point a, Point b, Point &min, Point &max) {
		if (a.y <= b.y) {
			min.y = a.y;
			max.y = b.y;
		} else {
			min.y = b.y;
			max.y = a.y;
		}
	}

	/**
	 * set all internal variables based on worldMax and worldMin.
	 *
	 * @param worldMin world space representation of min
	 * @param worldMax world space representation of max
	 * @param transform object to world transformation variable
	 * @param min object space min variable
	 * @param max object space max variable
	 */
	void setVariables(Point worldMin, Point worldMax, Transformation* &transform, Point* &min, Point* &max) {
		float transX = (worldMax.x - worldMin.x)/2.0f + worldMin.x;
		float transY = (worldMax.y - worldMin.y)/2.0f + worldMin.y;

		transform = new Transformation(0.0, transX, transY, 1.0, 1.0);
		min = new Point(worldMin.x - transX, worldMin.y - transY);
		max = new Point(worldMax.x - transX, worldMax.y - transY);
	}

	/**
	 * Finds minimum of uMin and min sets this value into tmpMin.
	 *
	 * @param uMin union min in object space
	 * @param min minimum point in object space
	 * @return point representing the min of the unioned BBox
	 */
	Point findMinOfUnionedBBox(Point uMin, Point min) {
		Point tmpMin;

		if(uMin.x > min.x) 	{ tmpMin.x = min.x; }
		else 				{ tmpMin.x = uMin.x;}
		if(uMin.y > min.y) 	{ tmpMin.y = min.y; }
		else				{ tmpMin.y = uMin.y;}

		return tmpMin;
	}

	/**
	 * Finds maximum of uMax and max sets this value into tmpMax.
	 *
	 * @param uMax union max in object space
	 * @param max maximum point in object space
	 * @return point representing the max of the unioned BBOx
	 */
	Point findMaxOfUnionedBBox(Point uMax, Point max) {
		Point tmpMax;

		if(uMax.x < max.x) 	{ tmpMax.x = max.x; }
		else				{ tmpMax.x = uMax.x;}
		if(uMax.y < max.y) 	{ tmpMax.y = max.y; }
		else				{ tmpMax.y = uMax.y;}

		return tmpMax;
	}

	/**
	 * Checks to see whether or not the transformation matrix sent is an identity
	 * matrix. This is specially written for BBox transformations as these transformations
	 * only affect translation.
	 *
	 * @param t transformation to check for identity property
	 * @return
	 */
	bool isIdentity(Transformation t) {
		if(	t.getTransformation()[0][0] < (1.0f + .000001f) &&
			t.getTransformation()[0][0] > (1.0f - .000001f) &&
			t.getTransformation()[1][1] < (1.0f + .000001f) &&
			t.getTransformation()[1][1] > (1.0f - .000001f) &&
			t.getTransformation()[2][2] < (1.0f + .000001f) &&
			t.getTransformation()[2][2] > (1.0f - .000001f) &&
			t.getTransformation()[3][3] < (1.0f + .000001f) &&
			t.getTransformation()[3][3] > (1.0f - .000001f)   )
			{return true;}
		else
			{return false;}
	}

	/**
	 * Checks to see whether min and max have been set to default values
	 * ie default constructor was called.
	 *
	 * @param min
	 * @param max
	 * @return boolean representing whether or not default constructor was called
	 */
	bool isDefault(Point min, Point max) {

		return 	min.x == 0.0f &&
				min.y == 0.0f &&
				max.x == -1.0f &&
				max.y == -1.0f;
	}
}

/**
 * Basic BBox constructor. Sets bounding box to impossible values Max: (-1.0, -1.0
 * Min: (0.0, 0.0). This ensures that inside test will fail if performed on default BBox.
 * unioning a default BBox with an initialized BBox will result in a BBox that is a copy of
 * the initialized BBox.
 */
BBox::BBox() {
	min = new Point(0.0,0.0);
	max = new Point(-1.0,-1.0);
	transform = new Transformation();
}

/**
 * BBox constructor that takes two input points. Will create a
 * bounding box "BBox" based on the minimum and maximum Points (x,y) of a and b.
 *
 * @param a first input point
 * @param b second input point
 */
BBox::BBox(Point a, Point b) {
	Point worldMin;
	Point worldMax;
	setMinMaxX(a, b, worldMin, worldMax);
	setMinMaxY(a, b, worldMin, worldMax);
	setVariables(worldMin, worldMax, transform, min, max);
}

BBox::~BBox() {
}

/**
 * Union input bounding box with a Point.
 *
 * @param uPoint point to be unioned with this BBox's bounding box
 * @return new BBox representing the union of this BBox's bounding box with point uPoint
 */
BBox BBox::unionBBox(Point uPoint) {
	//TODO: clean up function

	//check to see whether or not this BBox is a default BBox
	if(isIdentity(*transform) && isDefault(*min, *max)) {
		BBox constructedBBox(uPoint, uPoint);
		return constructedBBox;
	}

	//Transform union box to object space for comparison with current objMin/ objMax
	Point uPointObj = transform->worldtoObj(uPoint);

	Point uMinObj = findMinOfUnionedBBox(uPointObj, *min);
	Point uMaxObj = findMaxOfUnionedBBox(uPointObj, *max);

	//Transform unioned min and max to world space to create new BBox
	Point uMinWorld = transform->objToWorld(uMinObj);
	Point uMaxWorld = transform->objToWorld(uMaxObj);

	BBox unionedBBox(uMinWorld, uMaxWorld);
	return unionedBBox;
}

/**
 * Union input bounding box with bounding box of this BBox.
 *
 * @param uBox input bounding box to union with this bounding box
 * @return unioned bounding box
 */
BBox BBox::unionBBox(BBox uBox) {
	//TODO: clean up function

	//check to see whether or not this BBox is a default BBox
	if(isIdentity(*transform) && isDefault(*min, *max)) {

		//check to see whether or not BBox to be unioned is a default BBox
		if(isDefault(uBox.getMin(), uBox.getMax())) {
			return *this;
		}

		BBox constructedBBox(uBox.getMin(), uBox.getMax());
		return constructedBBox;
	}

	//Transform union box to object space for comparison with current objMin/ objMax
	Point uMinObj = transform->worldtoObj(uBox.getMin());
	Point uMaxObj = transform->worldtoObj(uBox.getMax());

	uMinObj = findMinOfUnionedBBox(uMinObj, *min);
	uMaxObj = findMaxOfUnionedBBox(uMaxObj, *max);

	//Transform unioned min and max to world space to create new BBox
	Point uMinWorld = transform->objToWorld(uMinObj);
	Point uMaxWorld = transform->objToWorld(uMaxObj);

	BBox unionedBBox(uMinWorld, uMaxWorld);
	return unionedBBox;
}

/**
 * Return a BBox with a bounding box expanded in the x axis by expX and expanded in the y axis
 * by expY. Note: you cannot expand a default BBox ie a BBox initialized using the default constructor
 *
 * @param expX expansion in the x axis
 * @param expY expansion in the y axis
 * @return new expanded bounding box
 */
BBox BBox::expandBBox(float expX, float expY) {

	//make sure that this is not a default BBox before expansion
	if(isDefault(*min,*max)) {
		return *this;
	}

	Point tmpMin = transform->objToWorld(*min);
	Point tmpMax = transform->objToWorld(*max);

	tmpMin.x -= expX; tmpMax.x += expX;
	tmpMin.y -= expY; tmpMax.y += expY;

	BBox expandedBBox(tmpMin, tmpMax);
	return expandedBBox;
}


bool BBox::insideBBox(Point testPt) {

	Point objTestPt = transform->worldtoObj(testPt);

	if(	objTestPt.x <= max->x &&
		objTestPt.x >= min->x &&
		objTestPt.y <= max->y &&
		objTestPt.y >= min->y	)
		{return true;}

	return false;
}

/**
 * returns the 4 vertices representing the 4 corners of the BBox's bounding box. Corners are inserted
 * into a Point array in the following order: [0]bottom-left, [1]bottom-right, [2]top-right, [3] top-left.
 *
 * @return Point array representing 4 corners of BBox's bounding box
 */
Point* BBox::getCorners() {
	Point corners[4];

	Point minWorld = transform->objToWorld(*min);
	Point maxWorld = transform->objToWorld(*max);

	corners[0].update(minWorld.x,minWorld.y);
	corners[1].update(maxWorld.x,minWorld.y);
	corners[2].update(maxWorld.x,maxWorld.y);
	corners[3].update(minWorld.x,maxWorld.y);

	return corners;
}

/**
 * return min of bounding box
 */
Point BBox::getMax() {
	return transform->objToWorld(*max);
}

/**
 * return max of bounding box
 */
Point BBox::getMin() {
	return transform->objToWorld(*min);
}

void BBox::print() {
	std::cout<<"obj space min: ("<<(*min).x<<","<<(*min).y<<")\n";
	std::cout<<"obj space max: ("<<(*max).x<<","<<(*max).y<<")\n";

	Point wldMin = transform->objToWorld(*min);
	Point wldMax = transform->objToWorld(*max);
	std::cout<<"wld space min: ("<<wldMin.x<<","<<wldMin.y<<")\n";
	std::cout<<"wld space max: ("<<wldMax.x<<","<<wldMax.y<<")\n";

	std::cout<<"\nTransformation information: \n";
	transform->print();

}

