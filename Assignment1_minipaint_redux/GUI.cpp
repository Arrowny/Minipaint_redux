#include <string>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "Object.h"
#include "Misc.h"
#include "Line.h"
#include "Canvas.h"
#include "Ellipse.h"


typedef std::vector<int> list;
std::vector<list> ls, cs, es;
int old_x, old_y, new_x, new_y, cx, cy, cr, xc, yc, rx, ry;
Point* lineStart;
Point* lineEnd;
Point* ellStart;
Point* ellRad;
Point initCanvasCenter; //used in rotation
Canvas* myCanvas;
Object* currObj;
std::vector<PointAndColor> objPACs;
std::vector<PointAndColor> canvasPACs;
int mouse_type;
bool keystates[256];
bool mouseButtonStates[3];
bool manipulateObject, manipulateCanvas;
float screenWidth = 1000.0f;
float screenHeight = 1000.0f;
int xPress;
int yPress;

void drawObjectOrCanvas(std::vector<PointAndColor> objOrCanVec) {
	Point currPt;
	Color currCol;
	glBegin(GL_POINTS);
		for(int ii = 0; ii < objOrCanVec.size(); ii++) {
			currPt  = objOrCanVec[ii].point;
			currCol = objOrCanVec[ii].color;
			glColor3f(currCol.red,currCol.green,currCol.blue);
			glVertex2i(currPt.x,currPt.y);
		}
	glEnd();
}

void drawBBox(BBox bbox) {
	Point* bboxPoints;
	bbox.getCorners(bboxPoints);
	Color bboxCol(1.0f, 0.0f, 0.0f);

	glEnable (GL_LINE_STIPPLE);
	glLineStipple(2, 0x00FF);
	glBegin(GL_LINES);
	//Debug: std::cout<<bboxPoints[0].x<<","<<bboxPoints[1].x<<","<<bboxPoints[2].x<<","<<bboxPoints[3].x<<","<<std::endl;
	//Debug: std::cout<<bboxPoints[0].y<<","<<bboxPoints[1].y<<","<<bboxPoints[2].y<<","<<bboxPoints[3].y<<","<<std::endl;
		for(int ii = 0; ii < 4 ; ii++) {
			glColor3f(bboxCol.red,bboxCol.green,bboxCol.blue);
			glVertex2f(bboxPoints[ii].x, bboxPoints[ii].y);
			if(ii < 3) {
			glVertex2f(bboxPoints[ii+1].x, bboxPoints[ii+1].y);
			}
		}
	glVertex2f(bboxPoints[0].x, bboxPoints[0].y);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

}

void draw() {
	if(manipulateObject) {
		drawObjectOrCanvas(objPACs);
		drawObjectOrCanvas(canvasPACs);
		drawBBox(currObj->getBBox());
	} else if(manipulateCanvas) {
		drawObjectOrCanvas(canvasPACs);
		drawBBox(myCanvas->getBBox());
	} else {
		drawObjectOrCanvas(canvasPACs);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3i(0, 0, 0);
	draw();
	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {

	keystates[key] = true;

	if((keystates['r'] || keystates['R']) &&
		manipulateCanvas == true) {
		initCanvasCenter = myCanvas->getCenter();
	}

}

void keyboardUp(unsigned char key, int x, int y) {

	keystates[key] = false;
}

void createLine(int x, int y) {
	if(mouseButtonStates[GLUT_LEFT_BUTTON] == true) {
		//Debug: std::cout<<"Drawing Line"<<std::endl;
		old_x = x;
		old_y = screenWidth - y;
		lineStart = new Point(old_x, old_y);
	}

	if(mouseButtonStates[GLUT_LEFT_BUTTON] == false) {
		//Debug: std::cout<<"Drawing Line"<<std::endl;
		new_x = x;
		new_y = screenWidth - y;
		lineEnd = new Point(new_x, new_y);
		currObj = new drawableLine(*lineStart, *lineEnd, Color(0.0f, 0.0f, 0.0f));
		lineStart = new Point(*lineEnd);
		objPACs = currObj->draw();
		manipulateObject = true;
		glutPostRedisplay();
	}
}

void createEllipse(int x, int y) { //TODO: create create Ellipse function
	if(mouseButtonStates[GLUT_LEFT_BUTTON] == true) {
		//Debug: std::cout<<"Drawing Ellipse"<<std::endl;
		old_x = x;
		old_y = screenHeight - y;
		ellStart = new Point(old_x, old_y);
		glutPostRedisplay();
	}

	if(mouseButtonStates[GLUT_LEFT_BUTTON] == false) {
		//Debug: std::cout<<"Drawing Ellipse"<<std::endl;
		new_x = int(sqrt(double(x - old_x) * (x - old_x)+ (screenWidth - y - old_y) * (screenWidth - y - old_y)) + 0.5f);
		new_y = int(sqrt(double(screenWidth - x - y) * (screenWidth - x - old_x)+ (y - old_y) * (y - old_y)) + 0.5f);
		ellRad = new Point(new_x, new_y);
		currObj = new drawableEllipse(*ellStart, *ellRad);
		objPACs = currObj->draw();
		manipulateObject = true;
		glutPostRedisplay();
	}

}

void mouseClick(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) {
		xPress = x;
		yPress = y;
		mouseButtonStates[button] = true;
	} else {

		/* TODO: figure out why fill is not working*/
		if(	(state == GLUT_UP)			&&
			(manipulateObject == false) &&
			(manipulateCanvas == false) &&
			(keystates['f'] || keystates['F'])
			) {
			Point fillPoint(xPress,yPress);
			Color fillColor(0.0f,1.0f,0.0f);
			PointAndColor fillPAC(fillPoint,fillColor);
			std::vector<PointAndColor> fillPACs;
			fillPACs = myCanvas->fill(fillPAC,screenWidth,screenHeight);
			//Debug:
			std::cout<<fillPACs.size()<<std::endl;
			canvasPACs.insert(canvasPACs.end(),fillPACs.begin(),fillPACs.end());
			glutPostRedisplay();
		}

		xPress = 0;
		yPress = 0;
		mouseButtonStates[button] = false;
	}

	//check to see if canvas is being manipulated. Note: cannot manipulate canvas while manipulating object
	if(	 myCanvas->inside(Point(x,y)) 	&&
		 !manipulateObject 				&&
		(!keystates['f'] && !keystates['F'])
		) {
		manipulateCanvas = true;
		glutPostRedisplay();
	}

	//check to see if no longer manipulating canvas
	if(manipulateCanvas == true) {
		if(	 !myCanvas->inside(Point(x,y)) 		&&
			(!keystates['r'] && !keystates['R'] &&
			 !keystates['s'] && !keystates['S']	&&
			 !keystates['t'] && !keystates['T'])
			 ) {
			manipulateCanvas = false;
			glutPostRedisplay();
		}
	}

	//check to see if no longer manipulating object
	if(manipulateObject == true) {

		//if user has clicked off of current object send that object to the canvas
		//if user is pressing r = rotation
		//if user is pressing s = scale not currently working
		//if user is pressing t = translation
		if(	 !currObj->inside(Point(x,y)) 		&&
			(!keystates['r'] && !keystates['R'] &&
			 !keystates['s'] && !keystates['S']	&&
			 !keystates['t'] && !keystates['T'])
			 ) {
			manipulateObject = false;
			myCanvas->add(currObj);
			canvasPACs = myCanvas->draw();
			glutPostRedisplay();
		}

		if ((keystates['s'] || keystates['S']) &&
			(state == GLUT_UP))
		{
			//TODO: work out algorithm for setting scale
			//currObj->setScale((float(x)/screenWidth)*5.0f,(float(y)-screenHeight/screenWidth)*5.0f);
			//objPACs = currObj->draw();
			//glutPostRedisplay();
		}

	} else {
		if (keystates['e'] || keystates['E']) {
			createEllipse(x,y); //TODO: finish ellipse
		}

		if (keystates['l'] || keystates['L']) {
			createLine(x,y);
		}

		if(keystates['c'] || keystates['C']) {
			manipulateCanvas = true;
		}

	}
}


void mouseMotion (int x, int y)
{
	if(	mouseButtonStates[GLUT_LEFT_BUTTON] == true &&
		manipulateObject == true						) {
		if (keystates['r'] || keystates['R'])
		{
			currObj->setRotation(yPress - y);
			objPACs = currObj->draw();
			glutPostRedisplay();
		}

		if (keystates['t'] || keystates['T'])
		{
			currObj->setTranslation(x,(screenHeight - y));
			objPACs = currObj->draw();
			glutPostRedisplay();
		}
	}

	if(	mouseButtonStates[GLUT_LEFT_BUTTON] == true &&
		manipulateCanvas == true						) {
		if (keystates['r'] || keystates['R'])
		{
			//TODO: figure out problem with canvas rotation
			//myCanvas->setRotation(yPress - y, initCanvasCenter);
			//canvasPACs = myCanvas->draw();
			//std::vector<PointAndColor> fillPACs;
			//fillPACs = myCanvas->reapplyAllFills(screenWidth,screenHeight);
			//glutPostRedisplay();
		}

		if (keystates['t'] || keystates['T'])
		{
			myCanvas->setTranslation(x,(screenHeight - y));
			canvasPACs = myCanvas->draw();
			std::vector<PointAndColor> fillPACs;
			fillPACs = myCanvas->reapplyAllFills(screenWidth,screenHeight);
			glutPostRedisplay();
		}
	}
}

void screenmotion(int x, int y) {
	if (mouse_type == 1) {
		new_x = x;
		new_y = screenWidth - y;

		std::cout << std::endl << "new-line:" << old_x << "," << old_y << "   " << new_x << "," << new_y << std::endl;

	} else if (mouse_type == 3) {
		cr = int(sqrt(double(x - cx) * (x - cx)+ (screenWidth - y - cy) * (screenWidth - y - cy)) + 0.5);

		std::cout << std::endl << "new-circle: " << cx << "," << cy << "   " <<cr<< std::endl;

	} else if (mouse_type == 2) {
		rx = int(sqrt(double(x - xc) * (x - xc)+ (screenWidth - y - yc) * (screenWidth - y - yc)) + 0.5);
		ry = int(sqrt(double(screenWidth - x - y) * (screenWidth - x - xc) + (y - yc) * (y - yc)) + 0.5);

		std::cout << std::endl << "new-ellipse: " << xc << "," << yc << "   " << rx << "," << ry << std::endl;
	}

	glutPostRedisplay();
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, screenWidth, 0.0, screenWidth+1);
	myCanvas = new Canvas();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("3DS - Minipaint");
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;
}
