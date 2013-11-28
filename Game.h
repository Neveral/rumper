#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Statistics.h"
#include "Menu.h"
//#include "Map.h"

class Game
{
private:
	sf::RenderWindow mainWindow;
	sf::SoundBuffer soundBuffer;
	sf::Sound soundJump;

	sf::View gameView;
	sf::View menuView;
	bool menuVisible;

	static const sf::Time timePerFrame;

	sf::Event gameEvent;
	sf::Event menuEvent;

	Player player;
	Statistics statistics;
	Menu menu;


	/* for player */
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
	/* end for player */


	void processEvent();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void screenScrolling();
	void showMenu();
	void showGame();


public:
	Game();
	void run();

};

#endif