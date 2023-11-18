#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	bool			isMoving;
	float			speed;

	Ball(sf::Sprite* sprite);

private:
	void			Rebound(CollisionSide direction, float deltaTime);

public:
	void			Move(float deltaTime);

	// Collisions Override

	void			OnCollisionEnter(const GameObject& Object, float deltaTime) override;
	void			OnCollisionStay(float deltaTime) override;
};

