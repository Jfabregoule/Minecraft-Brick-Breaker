#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "GameObject.h"

class Border : public GameObject
{
public:
	sf::RectangleShape		*o_shape;

	Border(char position, GameWindow* window);
	~Border();

	void SetBorderPos(float posX, float posY);
};

