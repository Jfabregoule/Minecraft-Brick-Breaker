#pragma once

#include "GameObject.h"

class Canon : public GameObject
{
public:
	Canon(sf::Sprite* sprite);

	void	FollowMouse(GameWindow* window);
	void	SetOrientation(int x, int y);
};

