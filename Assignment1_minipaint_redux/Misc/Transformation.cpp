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
<<<<<<< HEAD

=======
	Translation = vmath::translate(xTrans, yTrans, 0.0f);
	Rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	Scale = vmath::scale(xScale, yScale, 0.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;
>>>>>>> origin/DavidWin
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

/**
<<<<<<< HEAD
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
=======
 * sets the rotation matrix of transformation.
 *
 * @param theta rotation of 2d point
 */
void Transformation::setRotation(float theta) {
	Rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;
}

/**Put in two parameters xScale and yScale to scale in x and y axis
 *
 * @param xScale scaling factor in x-axis
 * @param yScale scaling factor in y-axis
 */
void Transformation::setScale(float xScale, float yScale)
{

	Scale = vmath::scale(xScale, yScale, 0.0f);
	Transform.identity();
	Transform = Translation * Rotation * Scale;

}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::mat4 Transformation::getRotation() {
	return Rotation;
}

/**Gets current 4x4 scaling transformation matrix
 *
 * @return It is in the form of (xScale, yScale, 0.0, 1.0)
 */
vmath::mat4 Transformation::getScale()
{
	return Scale;
}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::mat4 Transformation::getTransformation() {
	return Transform;
}


>>>>>>> origin/DavidWin
