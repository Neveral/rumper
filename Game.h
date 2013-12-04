#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Statistics.h"
#include "Menu.h"
#include "Map.h"
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow mainWindow;
	sf::SoundBuffer soundBufferJump;
	sf::Sound soundJump;
	sf::SoundBuffer soundBufferHurt;
	sf::Sound soundHurt;

	sf::View gameView;
	sf::View menuView;
	bool menuVisible;

	int currentLevel;

	static const sf::Time timePerFrame;

	sf::Event gameEvent;
	sf::Event menuEvent;

	Map* map;
	Player player;
	Enemy* enemy1;
	Enemy* enemy2;
	std::vector<Enemy*> enemyArmy;
	Statistics statistics;
	Menu menu;


	/* for player */
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
	/* end for player */


	void processEvent();
	void update(Map* &map, int &currentLevel);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void screenScrolling();
	void showMenu();
	void showGame();

	void newGame();
	void saveGame();
	void loadGame();


public:
	Game();
	void run();

};

#endif