#include <iostream>
#include <iostream>
#include <errno.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

#include "GameWindow.h"
#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Canon.h"
#include "Border.h"
#include "Map.h"
#include "Hud.h"

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Game::Game() {

	g_level = 0;
	g_window = new GameWindow();
	g_icon = new sf::Image();
	g_music = new Music();

	g_menu = true;
	g_win = false;
	g_lose = false;
	g_deltaTime = 0.f;
	g_isRunning = true;
	g_numSim = 10;

	g_filePath = new std::string();

	g_ballNum = 0;
	g_currentBall = NULL;

	g_canon = NULL;
	g_bricksNum = NULL;
	*g_borders = NULL;

	g_map = new Map();

	g_fpsLimit = 1.0f / 120.0f;
}

/*
---------------------------------------------------------------------------------
|				Here are all the generation methods								|
---------------------------------------------------------------------------------
*/

void Game::GenerateSprites() {
	sf::Texture* ballTexture = new sf::Texture();
	sf::Texture* canonTexture = new sf::Texture();
	sf::Texture* brickTexture = new sf::Texture();
	if (!ballTexture->loadFromFile("rsrc/img/objects/ball.png") or !canonTexture->loadFromFile("rsrc/img/objects/canon.png") \
		or !brickTexture->loadFromFile("rsrc/img/objects/brick.png")) {
		std::cout << "Error loading object textures." << std::endl;
		exit(1);
	}

	sf::Sprite* ballSprite = new sf::Sprite();
	ballSprite->setTexture(*ballTexture);
	g_sprites.push_back(ballSprite);

	sf::Sprite* canonSprite = new sf::Sprite();
	canonSprite->setTexture(*canonTexture);
	g_sprites.push_back(canonSprite);

	sf::Sprite* brickSprite = new sf::Sprite();
	brickSprite->setTexture(*brickTexture);
	g_sprites.push_back(brickSprite);
}

void	Game::GenerateTerrain() {
	float	x = 40;
	float	y = 65;
	int		sizeX = g_map->GetWidth();
	int		sizeY = g_map->GetHeight();

	g_bricksNum = 0;
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			if (g_map->m_vstr->at(i).at(j) - 48 != 0) {
				Brick* brick = new Brick(g_map->m_vstr->at(i).at(j) - 48, g_sprites.at(2));
				brick->SetPos(x, y);
				g_bricks.push_back(brick);
				g_bricksNum++;
			}
			x += (60);
		}
		x = 40;
		y += 40;
	}
	if (g_bricks.empty())
	{
		std::cout << "Error Generating Terrain. Terrain must not be empty" << std::endl;
		exit(1);
	}
}

void	Game::SetBorder(Border* border, char id) {
	switch (id) {
	case('l'):
		border->SetBorderPos(-25, g_window->GetHeight() / 2);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('u'):
		border->SetBorderPos(g_window->GetWidth() / 2, -25);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('r'):
		border->SetBorderPos(g_window->GetWidth() + 25, g_window->GetHeight() / 2);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('d'):
		border->SetBorderPos(g_window->GetWidth() / 2, g_window->GetHeight() + 25);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	}
}

void	Game::GenerateBorders() {
	Border* leftWall = new Border('l', g_window);
	Border* rightWall = new Border('r', g_window);
	Border* upWall = new Border('u', g_window);
	Border* downWall = new Border('d', g_window);

	SetBorder(leftWall, 'l');
	SetBorder(upWall, 'u');
	SetBorder(rightWall, 'r');
	SetBorder(downWall, 'd');

	g_borders[0] = leftWall;
	g_borders[1] = upWall;
	g_borders[2] = rightWall;
	g_borders[3] = downWall;
}

void	Game::GenerateBalls() {
	for (int i = 0; i < g_ballNum - 1; i++) {
		Ball* ball = new Ball(g_sprites.at(0));
		g_remainingBalls.push_back(ball);
	}
}

void	Game::GenerateCanon() {
	g_canon = new Canon(g_sprites.at(1));
	g_canon->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
	g_canon->SetOrientation(0, 1);
}
void	Game::GenerateHud() {
	g_hud = new Hud(g_window);
}


/*
---------------------------------------------------------------------------------
|				Here are all the window related methods							|
---------------------------------------------------------------------------------
*/

void Game::SetIcon() {
	if (!g_icon->loadFromFile("rsrc/img/icon/icon.png"))
	{
		std::cout << "Error loading icon" << std::endl;
		exit(1);
	}
	g_window->w_window->setIcon(g_icon->getSize().x, g_icon->getSize().y, g_icon->getPixelsPtr());
}

void Game::RefreshWindow() {
	g_window->RefreshScreen();
	g_window->w_window->draw(*g_backgrounds.at(0));
	if (g_currentBall && g_currentBall->isMoving)
		g_window->DrawObject(g_currentBall);
	if (!g_bricks.empty())
		for (int i = 0; i < g_bricksNum; ++i) {
			g_window->DrawObject(g_bricks.at(i));
		}
	g_window->DrawObject(g_canon);
	g_hud->DrawHud(g_window, g_ballNum);
	g_window->w_window->display();
}

void	Game::CloseWindow() {
	g_music->stop();
	delete g_music;
	g_window->w_window->close();
	exit(0);
}

void Game::LimitFps(float fps) {
	g_deltaTime = g_Clock.restart().asSeconds();
	if (g_deltaTime < g_fpsLimit) {
		sleep(seconds(g_fpsLimit - g_deltaTime));
		g_deltaTime += g_fpsLimit - g_deltaTime;
	}
	fps = 1.0f / g_deltaTime;
}

/*
---------------------------------------------------------------------------------
|				Here are all the music related methods							|
---------------------------------------------------------------------------------
*/

void	Game::PlayMusic() {
	g_music->play();
	g_music->setLoop(true);
}

void	Game::ChangetoEndMusic() {
	g_music->stop();
	if (g_win)
	{
		if (!g_music->openFromFile("rsrc/music/Win.ogg"))
		{
			std::cout << "Error loading Win.ogg" << std::endl;
			exit(1);
		}
	}
	else if (g_lose)
	{
		if (!g_music->openFromFile("rsrc/music/Lose.ogg"))
		{
			std::cout << "Error loading Lose.ogg" << std::endl;
			exit(1);
		}
	}
	g_music->setVolume(10.0f);
	g_music->play();
	g_music->setLoop(true);
}

/*
---------------------------------------------------------------------------------
|				Here are all the objects related methods						|
---------------------------------------------------------------------------------
*/

void Game::AddBall() {
	g_ballNum += 1;
	Ball* ball = new Ball(g_sprites.at(0));
	g_remainingBalls.push_back(ball);
}

int	Game::NewBall() {
	if (!g_remainingBalls.empty()) {
		g_currentBall = g_remainingBalls.at(g_remainingBalls.size() - 1);
		g_remainingBalls.pop_back();
		g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
		return 1;
	}
	return 0;
}

void	Game::SendBall() {
	if (g_currentBall->isMoving == false) {
		g_ballNum--;
		g_currentBall->SetDirection(g_canon->o_angle);
		g_currentBall->isMoving = true;
	}
}

void Game::DestroyBall() {
	delete g_currentBall;
}

void Game::ClearBricks() {
	Brick* brick;
	if (g_bricks.empty() == false) {
		for (int i = 0; i < g_bricksNum; i++) {
			if (g_bricks.at(i)->o_life == 0)
			{
				AddBall();
				brick = g_bricks.at(i);
				g_bricks.erase(g_bricks.begin() + i);
				delete brick;
				g_bricksNum--;
			}
		}
	}
}

/*
---------------------------------------------------------------------------------
|				Here are all the checks related methods							|
---------------------------------------------------------------------------------
*/

void Game::HandleEvents() {
	Event event;

	while (g_window->w_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			CloseWindow();
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			if (!g_currentBall) {
				g_lose = true;
				g_isRunning = false;
			}
			else {
				SendBall();
			}
		}
	}
}

void Game::CollCheck() {
	for (int i = 0; i < g_bricks.size(); i++) {
		g_currentBall->CheckCollision(g_bricks.at(i), g_deltaTime);
	}

	for (int i = 0; i < 4; i++) {

		if (g_currentBall->CheckCollision(g_borders[i], g_deltaTime)) {
			if (i == 3) {
				if (!NewBall()) {
					g_lose = true;
					g_isRunning = false;
					g_hud->h_balls.setString(std::to_string(g_ballNum));
				}
			}

		}
	}
}

void Game::EndCheck() {
	if (g_bricks.empty()) {
		g_win = true;
		g_isRunning = false;
	}
	if (g_remainingBalls.empty() && !g_currentBall) {
		g_lose = true;
		g_isRunning = false;
	}
}

/*
---------------------------------------------------------------------------------
|				Here are the texture path method								|
---------------------------------------------------------------------------------
*/

void Game::InitLevel() {
	const	char* filepath;
	const	char* texturepath;
	const	char* musicpath;

	// Init all the texture related variables

	sf::Texture* backgroundTexture = new sf::Texture();
	sf::Sprite* background = new sf::Sprite();
	filepath = NULL;
	texturepath = NULL;
	musicpath = NULL;

	// Load ressources based on the level num

	switch (g_level) {
	case 1:
		filepath = "rsrc/levels/Level1.txt";
		texturepath = "rsrc/img/backgrounds/Level1_Background.png";
		musicpath = "rsrc/music/Level1.ogg";
		break;
	case 2:
		filepath = "rsrc/levels/Level2.txt";
		texturepath = "rsrc/img/backgrounds/Level2_Background.png";
		musicpath = "rsrc/music/Level2.ogg";
		break;
	case 3:
		filepath = "rsrc/levels/Level3.txt";
		texturepath = "rsrc/img/backgrounds/Level3_Background.png";
		musicpath = "rsrc/music/Level3.ogg";
		break;
	case 4:
		filepath = "rsrc/levels/Level4.txt";
		texturepath = "rsrc/img/backgrounds/Level4_Background.png";
		musicpath = "rsrc/music/Level4.ogg";
		break;
	case 5:
		filepath = "rsrc/levels/Level5.txt";
		texturepath = "rsrc/img/backgrounds/Level5_Background.png";
		musicpath = "rsrc/music/Level5.ogg";
		break;
	case 6:
		filepath = "rsrc/levels/Level6.txt";
		texturepath = "rsrc/img/backgrounds/Level6_Background.png";
		musicpath = "rsrc/music/Level6.ogg";
		break;
	}

	if (filepath)
		*g_filePath = filepath;
	if (texturepath) {
		if (!backgroundTexture->loadFromFile(texturepath))
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
	}
	background->setTexture(*backgroundTexture);
	g_backgrounds.push_back(background);
	if (musicpath)
		if (!g_music->openFromFile(musicpath)) {
			std::cout << "Error" << std::endl;
			exit(1);
		}
	g_music->setVolume(10.0f);
	g_menu = false;
}

void Game::GetPath(Vector2i MousePos) {
	g_menu = true;

	if (MousePos.y >= 22 && MousePos.y <= 276 && MousePos.x >= 22 && MousePos.x <= 246)
		g_level = 1;
	else if (MousePos.y >= 22 && MousePos.y <= 276 and MousePos.x >= 288 && MousePos.x <= 512)
		g_level = 2;
	else if (MousePos.y >= 22 && MousePos.y <= 276 and MousePos.x >= 554 && MousePos.x <= 778)
		g_level = 3;
	else if (MousePos.y >= 322 && MousePos.y <= 576 and MousePos.x >= 22 && MousePos.x <= 246)
		g_level = 4;
	else if (MousePos.y >= 322 && MousePos.y <= 576 and MousePos.x >= 288 && MousePos.x <= 512)
		g_level = 5;
	else if (MousePos.y >= 322 && MousePos.y <= 576 and MousePos.x >= 554 && MousePos.x <= 778)
		g_level = 6;
	if (g_level != 0) {
		InitLevel();
		g_menu = false;
	}
}
/*
---------------------------------------------------------------------------------
|				Here are the menu related methods								|
---------------------------------------------------------------------------------
*/

void	Game::LoosingScreen() {
	sf::Texture loseTexture;
	sf::Sprite	lose;
	Event		event;
	bool		loop = true;

	if (!loseTexture.loadFromFile("rsrc/hud/lose.png")) {
		std::cout << "Error loading lose.png" << std::endl;
		exit(1);
	}
	lose.setTexture(loseTexture);
	lose.setColor(sf::Color(255, 255, 255, 128));
	g_window->w_window->draw(lose);
	g_window->w_window->display();

	while (loop)
	{
		while (g_window->w_window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					loop = false;
			if (event.type == Event::Closed)
				CloseWindow();
		}
	}
}

void	Game::WinningScreen() {
	sf::Texture winTexture;
	sf::Sprite	win;
	Event		event;
	bool		loop = true;

	if (!winTexture.loadFromFile("rsrc/hud/win.png")) {
		std::cout << "Error loading win.png" << std::endl;
		exit(1);
	}
	win.setTexture(winTexture);
	win.setColor(sf::Color(255, 255, 255, 128));
	g_window->w_window->draw(win);
	g_window->w_window->display();

	while (loop)
	{
		while (g_window->w_window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					loop = false;
			if (event.type == Event::Closed)
				CloseWindow();
		}
	}
}

void	Game::DrawMenu() {
	sf::Texture menuTexture;
	sf::Sprite menu;

	if (!menuTexture.loadFromFile("rsrc/hud/menu.png")) {
		std::cout << "Error loading menu.png" << std::endl;
		exit(1);
	}
	menu.setTexture(menuTexture);
	g_window->RefreshScreen();
	g_window->w_window->draw(menu);
	g_window->w_window->display();
}

void Game::ChooseLevel() {
	Event event;
	while (g_menu) {
		while (g_window->w_window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				CloseWindow();
			if (Mouse::isButtonPressed(Mouse::Button::Left))
				GetPath(Mouse::getPosition(*g_window->w_window));
		}
	}

}

void Game::Menu() {
	g_menu = true;

	SetIcon();

	if (!g_music->openFromFile("rsrc/music/menu.ogg"))
	{
		std::cout << "Error loading menu.ogg" << std::endl;
		exit(1);
	}
	g_music->play();
	g_music->setVolume(10.0f);
	g_music->setLoop(true);
	DrawMenu();
	while (g_menu)
		ChooseLevel();
	g_window->RefreshScreen();
}

/*
---------------------------------------------------------------------------------
|				Here are all the main methods									|
---------------------------------------------------------------------------------
*/

void Game::Generate() {
	g_map->ParseMap(g_filePath);
	g_map->CheckMap();
	GenerateSprites();
	g_currentBall = new Ball(g_sprites.at(0));
	g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
	g_ballNum = g_map->GetBall();
	GenerateTerrain();
	GenerateBorders();
	GenerateCanon();
	GenerateBalls();
	GenerateHud();
	PlayMusic();
}


void Game::Start() {
	float	fps = 0;

	while (g_isRunning)
	{
		HandleEvents();
		ClearBricks();
		RefreshWindow();
		EndCheck();
		LimitFps(fps);
		g_canon->FollowMouse(g_window);
		for (int i = 0; i < g_numSim; i++) {
			CollCheck();
			if (g_currentBall->o_shouldMove) {
				g_currentBall->Move(g_deltaTime / g_numSim);
			}
		}
	}
	ChangetoEndMusic();
	if (g_lose)
		LoosingScreen();
	if (g_win)
		WinningScreen();
}

Game::~Game() {
	delete g_window;
	delete g_icon;
	delete g_hud;
	delete g_map;
	delete g_filePath;
	delete g_music;
	delete g_currentBall;
	delete g_canon;
	for (int i = 0; i < 4; ++i)
		delete g_borders[i];
	g_bricks.clear();
	g_remainingBalls.clear();
	g_backgrounds.clear();
	g_sprites.clear();
}