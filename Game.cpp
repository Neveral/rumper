#include "Game.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);
const sf::Vector2i screenDimensions(800, 600);
const sf::Vector2i blockDimensions(32,32);




Game::Game() : mainWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), 
						  "Rumper", sf::Style::Close),
						  isMovingDown(false),
						  isMovingUp(false),
						  isMovingLeft(false),
						  isMovingRight(false),
						  menuVisible(false)
{
	if(!soundBuffer.loadFromFile("Media/jump.wav"))
		throw "Sound file jump.wav not found!";
	soundJump.setBuffer(soundBuffer);

	map = new Map('1');
}
//==================================================================
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinseLastUpadate = sf::Time::Zero;

	
	while(mainWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinseLastUpadate += elapsedTime;
		statistics.updateStatistics(elapsedTime);


		while(timeSinseLastUpadate > timePerFrame)
		{
			timeSinseLastUpadate -= timePerFrame;

			processEvent();
			update(map);
		}

		render();
	}	
}
//==================================================================
void Game::render()
{
	if(!menuVisible)
	{
		showGame();
	}
	else
		showMenu();
}
//==================================================================
void Game::processEvent()
{
	if(!menuVisible) // event processing for game
	{
		while(mainWindow.pollEvent(gameEvent))
		{
			switch(gameEvent.type)
			{
				case sf::Event::Closed:
					mainWindow.close();
					break;
				case sf::Event::KeyPressed:
					if(gameEvent.key.code == sf::Keyboard::Escape)
						menuVisible = true;
					else if (gameEvent.key.code == sf::Keyboard::Num5)
						player.reduceHelth();
					else
						handlePlayerInput(gameEvent.key.code, true);
					break;
				case sf::Event::KeyReleased:
					handlePlayerInput(gameEvent.key.code, false);
					break;
			}
		}
	}
	else // event processing for menu
	{
		while(mainWindow.pollEvent(menuEvent))
		{
			switch(menuEvent.type)
			{
				case sf::Event::Closed:
					mainWindow.close();
					break;
				case sf::Event::KeyPressed:
					if(menuEvent.key.code == sf::Keyboard::Escape)
						menuVisible = false;
					if(menuEvent.key.code == sf::Keyboard::Num2)
						menuVisible = false;
					if(menuEvent.key.code == sf::Keyboard::Num5)
						mainWindow.close();
					break;
			}
		}
	}
}
//==================================================================
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
		isMovingUp = isPressed;
	if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
		isMovingDown = isPressed;
	if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
		isMovingLeft = isPressed;
	if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
		isMovingRight = isPressed;
}
//==================================================================
void Game::update(Map* &map)
{
	if (isMovingUp)
		if (player.onGround == true)
		{
			player.setDirectionY(-3*player.speed);
			player.onGround = false;
			soundJump.play();
		}
	if (isMovingDown)
		player.setDirectionY(2*player.speed);
	if (isMovingLeft)
		player.setDirectionX(-2*player.speed);
	if (isMovingRight)
		player.setDirectionX(2*player.speed);

	player.update(map);
	enemy.update(map);
}
//==================================================================
void Game::screenScrolling()
{
	float curPosX = player.getPosition().x - screenDimensions.x/4;
	float curPosY = player.getPosition().y - screenDimensions.y/2;

	if (curPosX < 0.f)
		curPosX = 0.f;
	if (curPosY < 0.f)
		curPosY = 0.f;

	player.setHealthSpritePosition(curPosX + screenDimensions.x*0.02, 10.f);
	statistics.setStatisticsTextPosition(curPosX + screenDimensions.x*0.8, 10.f);
	gameView.reset (sf::FloatRect(
								curPosX, 
								0.f, 
								screenDimensions.x, 
								screenDimensions.y
							)
				);
}
//==================================================================
void Game::showGame()
{
	screenScrolling();
	mainWindow.setView(gameView);
	mainWindow.clear(sf::Color(125, 206, 250, 87));
	//std::cout << map->mapArray[0][0] << std::endl;
	map->display(&mainWindow);
	player.display(&mainWindow);
	enemy.display(&mainWindow);
	statistics.display(&mainWindow);
	mainWindow.display();
}
//==================================================================
void Game::showMenu()
{
	menuView.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	mainWindow.setView(menuView);
	mainWindow.clear(sf::Color::Black);
	menu.display(mainWindow);
	mainWindow.display();
};
//==================================================================
//==================================================================
//==================================================================