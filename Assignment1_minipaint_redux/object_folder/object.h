/*
 * object.h
 *
 *  Created on: May 27, 2014
 *      Author: DavidsMac
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class object {
public:
	object();
	virtual ~object();
	virtual void draw() = 0;
	virtual void rotate() = 0;
};

#endif /* OBJECT_H_ */
