#include <SFML/Graphics.hpp>

#include "GameObject.h"

#include "math.h"

using namespace sf;
using namespace std;
using namespace math;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

GameObject::GameObject(sf::Sprite *sprite) {
	o_height = 0;
	o_width = 0;
	o_posX = 0.f;
	o_posY = 0.f;
	o_directionX = 0.f;
	o_directionY = 0.f;
	o_InCollision = false;
	o_life = NULL;
	o_shouldMove = true;
	o_lastSide = None;
	o_angle = 0.f;

	o_sprite = *new sf::Sprite;
	if (sprite != NULL)
		o_sprite = *sprite;
}

/*
---------------------------------------------------------------------------------
|				Here are the object parameters related methods					|
---------------------------------------------------------------------------------
*/

void GameObject::SetPos(float posX, float posY) {
	o_posX = posX;
	o_posY = posY;
	o_sprite.setPosition(posX, posY);
}

void GameObject::SetColor(int r, int g, int b) {
	o_sprite.setColor(Color(r, g, b));
}

void GameObject::SetOrientation(int x, int y)
{

	o_angle = -atan2(x - o_posX, y - o_posY) * 180 / 3.14159f;
	o_sprite.setRotation(o_angle);
}

void GameObject::SetDirection(float angle) {
	o_directionX = RotateVect(0, 1, angle).x;
	o_directionY = RotateVect(0, 1, angle).y;
}

void GameObject::ResetAngle() {
	if (o_angle >= 0 and o_angle < 100) {
		o_angle = 100;
	}
	else o_angle = -100;
}

void GameObject::DecreaseLife(GameObject* Object, int value){
	if (Object->o_life != NULL)
		Object->o_life = Object->o_life - value;
	switch (Object->o_life) {
	case (1):
		o_sprite.setColor(sf::Color::White);
		break;
	case (2):
		o_sprite.setColor(sf::Color::Yellow);
		break;
	case (3):
		o_sprite.setColor(sf::Color::Green);
		break;
	case (4):
		o_sprite.setColor(sf::Color::Cyan);
		break;
	case (5):
		o_sprite.setColor(sf::Color::Blue);
		break;
	case (6):
		o_sprite.setColor(sf::Color::Magenta);
		break;
	case (7):
		o_sprite.setColor(sf::Color::Red);
		break;
	case (8):
		o_sprite.setColor(sf::Color::Black);
		break;
	}
}


/*
---------------------------------------------------------------------------------
|				Here are the Collisions related methods							|
---------------------------------------------------------------------------------
*/

void GameObject::ChangeCollideBool() {
	o_InCollision = not o_InCollision;
}

bool GameObject::CheckCollision(GameObject* Object, float deltaTime) {
	bool collision = (o_posX-o_width/2 <= Object->o_posX + Object->o_width/2 and o_posX + o_width/2 >= Object->o_posX - Object->o_width/2) and (o_posY - o_height / 2 <= Object->o_posY + Object->o_height / 2 and o_posY + o_height / 2 >= Object->o_posY - Object->o_height / 2);
	if (collision) {
		if (not Object->o_InCollision) {
			OnCollisionEnter(*Object, deltaTime);
			Object->ChangeCollideBool();
		}
		else {
			OnCollisionStay(deltaTime);
		}
	}
	else {
		if (Object->o_InCollision) {
			OnCollisionExit();
			Object->ChangeCollideBool();
			Object->DecreaseLife(Object, 1);
		}
	}

	if (collision) {
		return 1;
	}
	else return 0;
}

void GameObject::OnCollisionEnter(const GameObject& Object, float deltaTime) {
	o_shouldMove = false;
	char direction = NULL;
	float overlapLR = min(o_posY + o_height / 2, Object.o_posY + Object.o_height / 2) - max(o_posY - o_height / 2, Object.o_posY - Object.o_height / 2);
	float overlapUD = min(o_posX + o_width / 2, Object.o_posX + Object.o_width / 2) - max(o_posX - o_width / 2, Object.o_posX - Object.o_width / 2);
	if (overlapLR > overlapUD) {
		if (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX and o_lastSide != Left) {
			o_directionX = -o_directionX;
			o_lastSide = Left;
		}
		else if (o_lastSide != Left) {
			o_directionX = -o_directionX;
			o_lastSide = Right;
		}
	}
	else if (overlapLR < overlapUD) {
		if (o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY and o_lastSide != Up) {
			o_directionY = -o_directionY;
			o_lastSide = Up;
		}
		else if (o_lastSide != Down) {
			o_directionY = -o_directionY;
			o_lastSide = Down;
		}
	}
	else  {
		o_directionY = -o_directionY;
		o_directionX = -o_directionX;
		o_lastSide = Diagonal;
	}
	
}

void GameObject::OnCollisionStay(float deltaTime){
	
}

void GameObject::OnCollisionExit(){
	//cout << "EXIT" << endl;
	o_shouldMove = true;
}

GameObject::~GameObject() {

}