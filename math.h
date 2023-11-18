#pragma once

#include <SFML/Graphics.hpp>

namespace math {
	void			Normalize(float* VectX,float* VectY);
	float			RoundFloat(float number, int roundingNum);
	sf::Vector2f	RotateVect(float VectX, float VectY, float angle);
}
