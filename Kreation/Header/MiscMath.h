#ifndef MISCMATH_H
#define MISCMATH_H

#define PI 3.14159

#include <math.h>
#include <sstream>
#include "GLM/ext.hpp"


namespace MiscMath
{
	float DegToRad(float _Angle);

	//Caution!
	//This function may be very inspecific.
	//Converts polar to cartesian coords when mapping out verts for polys(only on one occaision).
	//glm::vec2 PolToCartCoords(float _Angle, float _Radius);

	//makes sure whatever value inputted is less than 90, originally for sometrigonometry to do with mapping out poly verts.
	double Ninety(float _Angle);

	//Any trigonometry can be done in this function
	//Just pass a '0' or NULL in to the param you do not know.
	//float Trigonometry(float _Opposite = NULL, float _Adjacent = NULL, float _Hypotenuse = NULL, float _Angle = NULL);

	//This function will perform pythagorus theorum
	//Just pass a '0' or NULL in to the params you do not know.
	//There should always be 2 blank params & 2 non-blank params
	//This function does not alter the values that are passed in
	float Pythagorus(float _A = NULL, float _B = NULL, float _C = NULL);
	
	//This Function is only to be used in the above pythagorus function.
	//Perfomrms C^2 - A^2 = B^2
	float CalcB(float _A, float _C);

	//Compare parts of strings with other strings or parts of strings.
	//Mainy for use in Shader class for testing the type of shader being imported.
	//Automatically checks the _StringB against the _StringA char + _StringB.length
	//bool StrPartCompare(/*char is to be mid string character*/char _StringA, std::string _StringB);
	//bool StrPartCompare();
	//bool StrPartCompare();
};

#endif