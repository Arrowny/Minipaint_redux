/*
 * Ellipse.cpp
 *
 *  Created on: 2014Äê5ÔÂ29ÈÕ
 *      Author: yellow
 */

#include "Ellipse.h"

Ellipse::Ellipse() {
	// TODO Auto-generated constructor stub

}

Ellipse::~Ellipse() {
	// TODO Auto-generated destructor stub
}

namespace{

void FourPointSymmetry(Point start_p, float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2i(start_p.x+x, start_p.y+y);
	glVertex2i(start_p.x-x, start_p.y+y);
	glVertex2i(start_p.x+x, start_p.y-y);
	glVertex2i(start_p.x-x, start_p.y-y);
	glEnd();
}
//void MidPointEllipseRegionOne(Point start_p,float x,float y, float p,float px,float py,float rxSq,float rySq ){
//	p = rySq - (rxSq * start_p.y) + (0.25 * rxSq);
//	while (px < py)
//	    {
//		FourPointSymmetry(start_p,x,y);
//	        x++;
//	        px = px + 2 * rySq;
//
//	        if (p < 0){
//	            p = p + rySq + px;
//	        }
//	        else{
//	            y--;
//	            py = py - 2 * rxSq;
//	            p = p + rySq + px - py;
//	        }
//
//	    }
//}
//
//void MidPointEllipseRegionTwo(Point start_p,float x,float y, float p,float px,float py,float rxSq,float rySq){
//	p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
//		while (y > 0)
//		{
//			FourPointSymmetry(start_p,x,y);
//
//			y--;
//			py = py - 2 * rxSq;
//			if (p > 0){
//				p = p + rxSq - py;
//			}
//			else{
//				x++;
//				px = px + 2 * rySq;
//				p = p + rxSq - py + px;
//			}
//		}
//}
//
}
//void Ellipse(Point start_p, float rx, float ry)
//{
//	float rxSq = rx * rx;
//	float rySq = ry * ry;
//	float x = 0, y = ry, p;
//	float px = 0, py = 2 * rxSq * y;
//
//	MidPointEllipseRegionOne(start_p,x,y,p,px,py,rxSq,rySq);
//	MidPointEllipseRegionTwo(start_p,x,y,p,px,py,rxSq,rySq);
//
//
//}


void Ellipse(Point start_p, float rx, float ry)
{
	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0, y = ry, p;
	float px = 0, py = 2 * rxSq * y;

	//Region 1
	p = rySq - (rxSq * ry) + (0.25 * rxSq);
	//p = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);

	while (px < py)
	{
		FourPointSymmetry(start_p,x,y);
		x++;
		px = px + 2 * rySq;

		if (p < 0)
		{
			p = p + rySq + px;
		}

		else
		{
			y--;
			py = py - 2 * rxSq;
			p = p + rySq + px - py;
		}

	}

	//Region 2
	p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;

	while (y > 0)
	{
		FourPointSymmetry(start_p,x,y);

		y--;
		py = py - 2 * rxSq;

		if (p > 0)
		{
			p = p + rxSq - py;
		}

		else
		{
			x++;
			px = px + 2 * rySq;
			p = p + rxSq - py + px;
		}

	}

}
