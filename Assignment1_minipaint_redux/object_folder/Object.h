/*
 * Object.h
 *
 *  Created on: 2014��5��27��
 *      Author: yellow
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
public:
	Object();
	virtual ~Object();
	virtual void draw() = 0;
	virtual void rotate() = 0;
};

#endif /* OBJECT_H_ */
