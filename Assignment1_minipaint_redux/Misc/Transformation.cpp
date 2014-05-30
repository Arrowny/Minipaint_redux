/*
 * Transformation.cpp
 *
 *  Created on: May 30, 2014
 *      Author: David
 */

#include "Transformation.h"

Transformation::Transformation() {
	Translation.identity();
	Rotation.identity();
	Scale.identity();
	Transform.identity();
}

Transformation::~Transformation() {
	// TODO Auto-generated destructor stub
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

/**Gets current 4x4 scaling transformation matrix
 *
 * @return It is in the form of (xScale, yScale, 0.0, 1.0)
 */
vmath::mat4 Transformation::getScale()
{
	return Scale;
}
