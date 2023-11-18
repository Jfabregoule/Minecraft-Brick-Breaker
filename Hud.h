#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;

class Hud
{
private:

	// Main Attributes
	sf::Font					h_font;

public:

	sf::Text					h_balls;

	Hud();

	//Main Methods

	void	DrawHud(GameWindow *window, int ball_num);
};

