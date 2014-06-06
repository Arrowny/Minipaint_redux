/*
 * Transformation.cpp
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#include <Transformation.h>
#include <iostream>


namespace {

	bool invertMatrix(const float m[16], float invOut[16])
	{
		float inv[16], det;
		int i;

		inv[0] = m[5]  * m[10] * m[15] -
				 m[5]  * m[11] * m[14] -
				 m[9]  * m[6]  * m[15] +
				 m[9]  * m[7]  * m[14] +
				 m[13] * m[6]  * m[11] -
				 m[13] * m[7]  * m[10];

		inv[4] = -m[4]  * m[10] * m[15] +
				  m[4]  * m[11] * m[14] +
				  m[8]  * m[6]  * m[15] -
				  m[8]  * m[7]  * m[14] -
				  m[12] * m[6]  * m[11] +
				  m[12] * m[7]  * m[10];

		inv[8] = m[4]  * m[9] * m[15] -
				 m[4]  * m[11] * m[13] -
				 m[8]  * m[5] * m[15] +
				 m[8]  * m[7] * m[13] +
				 m[12] * m[5] * m[11] -
				 m[12] * m[7] * m[9];

		inv[12] = -m[4]  * m[9] * m[14] +
				   m[4]  * m[10] * m[13] +
				   m[8]  * m[5] * m[14] -
				   m[8]  * m[6] * m[13] -
				   m[12] * m[5] * m[10] +
				   m[12] * m[6] * m[9];

		inv[1] = -m[1]  * m[10] * m[15] +
				  m[1]  * m[11] * m[14] +
				  m[9]  * m[2] * m[15] -
				  m[9]  * m[3] * m[14] -
				  m[13] * m[2] * m[11] +
				  m[13] * m[3] * m[10];

		inv[5] = m[0]  * m[10] * m[15] -
				 m[0]  * m[11] * m[14] -
				 m[8]  * m[2] * m[15] +
				 m[8]  * m[3] * m[14] +
				 m[12] * m[2] * m[11] -
				 m[12] * m[3] * m[10];

		inv[9] = -m[0]  * m[9] * m[15] +
				  m[0]  * m[11] * m[13] +
				  m[8]  * m[1] * m[15] -
				  m[8]  * m[3] * m[13] -
				  m[12] * m[1] * m[11] +
				  m[12] * m[3] * m[9];

		inv[13] = m[0]  * m[9] * m[14] -
				  m[0]  * m[10] * m[13] -
				  m[8]  * m[1] * m[14] +
				  m[8]  * m[2] * m[13] +
				  m[12] * m[1] * m[10] -
				  m[12] * m[2] * m[9];

		inv[2] = m[1]  * m[6] * m[15] -
				 m[1]  * m[7] * m[14] -
				 m[5]  * m[2] * m[15] +
				 m[5]  * m[3] * m[14] +
				 m[13] * m[2] * m[7] -
				 m[13] * m[3] * m[6];

		inv[6] = -m[0]  * m[6] * m[15] +
				  m[0]  * m[7] * m[14] +
				  m[4]  * m[2] * m[15] -
				  m[4]  * m[3] * m[14] -
				  m[12] * m[2] * m[7] +
				  m[12] * m[3] * m[6];

		inv[10] = m[0]  * m[5] * m[15] -
				  m[0]  * m[7] * m[13] -
				  m[4]  * m[1] * m[15] +
				  m[4]  * m[3] * m[13] +
				  m[12] * m[1] * m[7] -
				  m[12] * m[3] * m[5];

		inv[14] = -m[0]  * m[5] * m[14] +
				   m[0]  * m[6] * m[13] +
				   m[4]  * m[1] * m[14] -
				   m[4]  * m[2] * m[13] -
				   m[12] * m[1] * m[6] +
				   m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
				  m[1] * m[7] * m[10] +
				  m[5] * m[2] * m[11] -
				  m[5] * m[3] * m[10] -
				  m[9] * m[2] * m[7] +
				  m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
				 m[0] * m[7] * m[10] -
				 m[4] * m[2] * m[11] +
				 m[4] * m[3] * m[10] +
				 m[8] * m[2] * m[7] -
				 m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
				   m[0] * m[7] * m[9] +
				   m[4] * m[1] * m[11] -
				   m[4] * m[3] * m[9] -
				   m[8] * m[1] * m[7] +
				   m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
				  m[0] * m[6] * m[9] -
				  m[4] * m[1] * m[10] +
				  m[4] * m[2] * m[9] +
				  m[8] * m[1] * m[6] -
				  m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
			return false;

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		return true;
	}

}
Transformation::Transformation() {
	translation = translation.identity();
	rotation = rotation.identity();
	scale = scale.identity();
	transform = transform.identity();
	invTransform = invTransform.identity();
}

Transformation::Transformation(float theta, float xTrans, float yTrans, float xScale, float yScale) {

	translation = vmath::translate(xTrans, yTrans, 0.0f);
	rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	scale = vmath::scale(xScale, yScale, 1.0f);
	transform = transform.identity();
	transform = scale * rotation * translation;
	invTransform = setInvTransform();
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
}

/**  This setTranslation is used to move objects along vector ( xTrans , yTrans ), and then set the new Transformation matrix
*
* @param xTrans : the amount of translations along x direction
* @param yTrans : the amount of translations along y direction
*/
void Transformation::setTranslation(float xTrans, float yTrans){

	translation = vmath::translate(xTrans, yTrans, 0.0f);
	transform = transform.identity();
	transform = scale * rotation * translation;
	invTransform = setInvTransform();
}

/**
 * sets the rotation matrix of transformation.
 *
 * @param theta rotation of 2d point
 */
void Transformation::setRotation(float theta) {
	rotation = vmath::rotate(theta, 0.0f, 0.0f, 1.0f);
	transform = transform.identity();
	transform = scale * rotation * translation;
	invTransform = setInvTransform();
}

/**Put in two parameters xScale and yScale to scale in x and y axis
 *
 * @param xScale scaling factor in x-axis
 * @param yScale scaling factor in y-axis
 */
void Transformation::setScale(float xScale, float yScale)
{

	scale = vmath::scale(xScale, yScale, 1.0f);
	transform = transform.identity();
	transform = scale * rotation * translation;
	invTransform = setInvTransform();
}

/**
 * This getTranslation is use to get the current Translation matrix
 *
 * @return 4x4 matrix representing Translation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::Tmat4<float> Transformation::getTranslation(){
	return translation;
}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::Tmat4<float> Transformation::getRotation() {
	return rotation;
}

/**Gets current 4x4 scaling transformation matrix
 *
 * @return It is in the form of (xScale, yScale, 0.0, 1.0)
 */
vmath::Tmat4<float> Transformation::getScale()
{
	return scale;
}

/**
 * gets rotation matrix of transformation.
 *
 * @return 4x4 matrix representing rotation matrix of transformation.
 * Note: this transformation requires that points be represented in the form
 * 		 [x,y,0.0f,1.0f].
 */
vmath::Tmat4<float> Transformation::getTransformation() {
	return transform;
}

/**
 * Transform worldPoint to object space equivalent point based on this transformation
 *
 * @param worldPoint world space point
 * @return equivalent point in object space
 */
Point Transformation::worldtoObj(Point worldPoint) {
	return worldPoint.transform(invTransform);
}

/**
 * Transform objPoint to world space equivalent point based on this transformation
 *
 * @param objPoint object space point
 * @return equivalent point in world space
 */
Point Transformation::objToWorld(Point objPoint) {
	return objPoint.transform(transform);
}

vmath::Tmat4<float> Transformation::getInverseTransformation() {
	return invTransform;
}

vmath::Tmat4<float> Transformation::setInvTransform() {

	float matArray[16];
	float invMatArray[16];

	//copy transformation to array
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			matArray[4*i + j] = transform[i][j];
		}
	}

	//invert array
	invertMatrix(matArray, invMatArray);
	vmath::Tmat4<float> invTrans;

	//copy inverted array back to mat4
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			invTrans[i][j] = invMatArray[4*i + j];
		}
	}

	return invTrans;
}

void Transformation::print() {

	std::cout<<"Translation: "<<std::endl;
	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<translation[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	std::cout<<"Scale: "<<std::endl;
	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<scale[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	std::cout<<"Rotation: "<<std::endl;
	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<rotation[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	std::cout<<"Transformation: "<<std::endl;
	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			if(j == 0) {
				std::cout<<"|";
			}
			std::cout<<" "<<transform[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}
	std::cout<<std::endl;
}

