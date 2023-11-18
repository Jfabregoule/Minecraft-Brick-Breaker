#include <cmath>
#include <iostream>

#include "math.h"

/*
---------------------------------------------------------------------------------
|						 Here are the Main Functions							|
---------------------------------------------------------------------------------
*/

void math::Normalize(float* VectX, float* VectY) {
	*VectX = *VectX / (float)sqrt(pow(*VectX, 2) + pow(*VectY, 2));
	*VectY = *VectY / (float)sqrt(pow(*VectX, 2) + pow(*VectY, 2));
}

float math::RoundFloat(float number, int roundingNum) {
	int temp = (number * pow(10, roundingNum));
	number = temp / 1000;
	return number;
}

// Return a vector with an angle given by x an y

sf::Vector2f math::RotateVect(float X, float Y, float angle) {
	float rad = (3.1415926535 / 180) * angle;
	sf::Vector2f Vect;
	Vect.x = X * cos(rad) - Y * sin(rad);
	Vect.y = X * sin(rad) + Y * cos(rad);

	const double tolerance = 1e-5;
	if (fabs(Vect.x) < tolerance) {
		Vect.x = 0.0;
	}
	if (fabs(Vect.y) < tolerance) {
		Vect.y = 0.0;
	}

	Normalize(&Vect.x, &Vect.y);
	return Vect;
}