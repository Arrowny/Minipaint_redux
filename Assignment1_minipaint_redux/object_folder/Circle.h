/*
 * Circle.h
 *
<<<<<<< HEAD
 *  Created on: 2014��5��27��
=======
 *  Created on: 2014��5��29��
>>>>>>> ca1f7edfe47a1cfe6a467b8cdb923ce761ee8c6c
 *      Author: yellow
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "object.h"

class Circle: public Ellipse {

public:
	Circle();
	virtual ~Circle();
	void draw(Point start_p, Point end_p);
};

#endif /* CIRCLE_H_ */
