#pragma once
class GameWindow;
class Hud;
class Map;
class Canon;
class Ball;
class Brick;
class Border;

#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Music.hpp>
#include <xstring>

class Game
{
private:

	// Main Attributes

	GameWindow*					g_window;
	sf::Image					*g_icon;
	Hud*						g_hud;
	bool						g_menu;
	bool						g_win;
	bool						g_lose;
	int							g_level;

	Map*						g_map;
	std::string					*g_filePath;
	sf::Music					*g_music;
	std::vector<sf::Sprite*>	g_backgrounds;

	// Time Attributes

	bool						g_isRunning;
	sf::Clock					g_Clock;
	float						g_deltaTime;
	float						g_fpsLimit;
	int							g_numSim;

	// Game Objects

	int							g_bricksNum;
	std::vector<Brick*>			g_bricks;

	int							g_ballNum;
	std::vector<Ball*>			g_remainingBalls;
	Ball*						g_currentBall;

	Border*						g_borders[4];

	Canon*						g_canon;

	// Textures

	std::vector<sf::Sprite*>	g_sprites;


public:

	Game();

	// Called in main

	void						Menu();
	void						Start();
	void						Generate();

	~Game();
private:
	
	// Menu
	void						DrawMenu();
	void						InitLevel();
	void						GetPath(sf::Vector2i MousePos);
	void						ChooseLevel();
	void						LoosingScreen();
	void						WinningScreen();

	// Generation

	void						GenerateTerrain();
	void						SetBorder(Border* border, char id);
	void						GenerateBorders();
	void						GenerateCanon();
	void						GenerateBalls();
	void						GenerateHud();

	// Window related

	void						SetIcon();
	void						RefreshWindow();
	void						CloseWindow();
	void						LimitFps(float fps);

	// Music related
	void						PlayMusic();
	void						ChangetoEndMusic();

	// Obj related

	void						AddBall();
	int							NewBall();
	void						SendBall();
	void						DestroyBall();

	void						ClearBricks();

	void						GenerateSprites();

	// Checks Related
	
	void						HandleEvents();
	void						CollCheck();
	void						EndCheck();
};

