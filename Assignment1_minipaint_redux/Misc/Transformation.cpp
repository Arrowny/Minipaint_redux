/*
 * Transformation.cpp
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#include <Transformation.h>

Transformation::Transformation() {
	Translation.identity();
	Rotation.identity();
	Scale.identity();
	Transform.identity();
}

Transformation::Transformation(float theta, float xTrans, float yTrans, float xScale, float yScale) {

}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

/**
 *  This setTranslation is used to move objects along vector ( xTrans , yTrans ), and then set the new Transformation matrix
 *
 * @param xTrans : the amount of translations along x direction
 * @param yTrans : the amount of translations along y direction
 */
void Transformation::setTranslation(float xTrans, float yTrans){

	Translation = vmath::translate(xTrans, yTrans, 0.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;
}
/**
 * This getTranslation is use to get the current Translation matrix
 *
 * @return
 */
vmath::mat4 Transformation::getTranslation(){
	return Translation;
}
