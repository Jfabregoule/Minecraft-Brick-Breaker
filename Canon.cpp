#include "Canon.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Canon::Canon(sf::Sprite* sprite) : GameObject(sprite) {
	o_sprite.setOrigin(25.f, 0.f);
	o_width = 50.f;
	o_height = 100.f;
}

void	Canon::FollowMouse(GameWindow *window) {
	if (window->w_window->mapPixelToCoords(Mouse::getPosition(*window->w_window)).y < o_posY);
	SetOrientation(window->w_window->mapPixelToCoords(Mouse::getPosition(*window->w_window)).x, window->w_window->mapPixelToCoords(Mouse::getPosition(*window->w_window)).y);
	//if (Mouse::getPosition(*window->w_window).y < o_posY - 50) 
		//SetOrientation(Mouse::getPosition(*window->w_window).x, Mouse::getPosition(*window->w_window).y);
}

void Canon::SetOrientation(int x, int y)
{

	o_angle = -atan2(x - o_posX, y - o_posY) * 180 / 3.14159f;
	o_sprite.setRotation(o_angle);
}