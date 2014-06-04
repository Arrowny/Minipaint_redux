/*
 * test_Transformation.cpp
 *
 *  Created on: May 31, 2014
 *      Author: David
 */

#include <Transformation.h>
#include <vmath.h>
#include <iostream>

/* include test_versions of helper functions here */
namespace {

	bool test_invertMatrix(const float m[16], float invOut[16])
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

		for (i = 0; i < 16; i++) {
			invOut[i] = inv[i] * det;
			//std::cout<<invOut[i]<<"\n";
		}

		return true;
	}

}

bool test_Inverse_Transformation() {

	Transformation transform(0.0, 3.0, 17.0, 8.0, 7.0);

	float matArray[16];
	float invMatArray[16];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			matArray[4*i + j] = transform.getTransformation()[i][j];
			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<transform.getTransformation()[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	test_invertMatrix(matArray, invMatArray);

	vmath::Tmat4<float> invTrans;
	std::cout<<"\n";

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			invTrans[i][j] = invMatArray[4*i + j];

			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<invTrans[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	vmath::mat4 checkmat = invTrans;
	std::cout<<"\n";

	//check to make sure passing invTrans back to function will work correctly
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(j == 0) {
				std::cout<<"|";
			}

			std::cout<<" "<<checkmat[i][j];

			if(j == 3) {
				std::cout<<" |\n";
			}
		}
	}

	return true;
}

bool test_scale() {

	Transformation testScale(0.0, 0.0, 0.0, 2.5, 3.5);
	testScale.print();
}


int main() {

	std::cout<<"Welcome to Transformation test!!"<<std::endl;
	test_Inverse_Transformation();
	test_scale();
	std::cout<<"All Tests passed! Well kind of This is a terrible test class."<<std::endl;
	return 0;
}

