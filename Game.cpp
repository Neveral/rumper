#include "Game.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);
const sf::Vector2i screenDimensions(800, 600);
const sf::Vector2i blockDimensions(32,32);


Game::Game() : mainWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), 
						  "Rumper"),
						  isMovingDown(false),
						  isMovingUp(false),
						  isMovingLeft(false),
						  isMovingRight(false)
{
	
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

		float time = elapsedTime.asMicroseconds();

		while(timeSinseLastUpadate > timePerFrame)
		{
			timeSinseLastUpadate -= timePerFrame;
			

			processEvent();
			update(time);
			screenScrolling();
		}
		render();
	}	
}
//==================================================================
void Game::render()
{
	mainWindow.clear(sf::Color(56, 120, 55));
	player.map.display(mainWindow);
	mainWindow.setView(view);
	player.display(mainWindow);
	statistics.display(mainWindow);
	mainWindow.display();
}
//==================================================================
void Game::processEvent()
{
	sf::Event event;
	while(mainWindow.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				mainWindow.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
					mainWindow.close();
				else
					handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
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
void Game::update(float time)
{
	if (isMovingUp)
		if (player.onGround==true)
		{
			player.setDirectionY(-3*player.speed);
			player.onGround = false;
		}
	if (isMovingDown)
		player.setDirectionY(player.speed);
	if (isMovingLeft)
		player.setDirectionX(-2*player.speed);
	if (isMovingRight)
		player.setDirectionX(2*player.speed);

	player.update(time);	
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

	view.reset (sf::FloatRect(
								curPosX, 
								curPosY, 
								screenDimensions.x, 
								screenDimensions.y
							)
				);
}
//==================================================================

//==================================================================
//==================================================================
//==================================================================
//==================================================================