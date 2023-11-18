#pragma once

#include <SFML/Graphics.hpp>

enum CollisionSide { Left, Right, Up, Down, Diagonal, None };
class GameWindow;

class GameObject {

private:

	bool			o_InCollision;

public:
	// Main Attributes

	float			o_width;
	float			o_height;
	int				o_life;

	// Pos and Mov related

	float			o_posX;
	float			o_posY;
	float			o_directionX;
	float			o_directionY;
	float			o_angle;
	bool			o_shouldMove;
	CollisionSide   o_lastSide;

	sf::Sprite		o_sprite;

	GameObject(sf::Sprite *sprite);
	~GameObject();

private:

	void			ChangeCollideBool();
	void			ResetAngle();

public:
	
	// Object parameters related

	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
	void			SetOrientation(int x, int y);
	void			SetDirection(float angle);
	void			DecreaseLife(GameObject* Object, int value);

	// Collision related

	bool			CheckCollision( GameObject* Object, float deltaTime);
	void			virtual OnCollisionEnter(const GameObject& Object, float deltaTime);
	void			virtual OnCollisionStay(float deltaTime);
	void			virtual OnCollisionExit();
};

