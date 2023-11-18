#include <SFML/Graphics.hpp>
#include <iostream>

#include "Hud.h"

#include "GameWindow.h"

Hud::Hud() {

	if (!h_font.loadFromFile("rsrc/font/font.ttf"))
	{
		std::cout << "Error Loading font" << std::endl;
		exit(1);
	}
	h_balls.setFont(h_font);
	h_balls.setCharacterSize(24);
	h_balls.setFillColor(sf::Color::White);
	h_balls.setStyle(sf::Text::Bold);
	h_balls.setPosition(755, 0);
}

void	Hud::DrawHud(GameWindow *window, int ball_num) {
	h_balls.setString(std::to_string(ball_num));
	window->w_window->draw(h_balls);
}
