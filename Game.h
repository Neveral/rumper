#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Statistics.h"
#include "Map.h"

class Game
{
private:
	sf::RenderWindow mainWindow;
	sf::View view;

	/* for player */
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
	/* end for player */

	static const sf::Time timePerFrame;

private:
	void processEvent();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void screenScrolling();
	void collision(/*bool isMovingX*/);

public:
	Game();
	void run();

	Player player;
	Statistics statistics;
	Map map;
};

#endif