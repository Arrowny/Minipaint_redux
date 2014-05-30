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
