#include "Brick.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Brick::Brick(int hp, sf::Sprite *sprite) : GameObject(sprite) {
	o_width = 50.f;
	o_height = 50.f;
	o_sprite.setOrigin(25.f, 25.f);
	o_life = hp;
	switch (o_life) {
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
