#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

int main()
{
    Game        game;

    game.Menu();
    game.Generate();
    sf::sleep(sf::milliseconds(200));
    game.Start();
    return 0;
}