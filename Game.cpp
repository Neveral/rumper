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

		while(timeSinseLastUpadate > timePerFrame)
		{
			timeSinseLastUpadate -= timePerFrame;
			processEvent();
			update();
			screenScrolling();
		}
		render();
	}	
}
//==================================================================
void Game::render()
{
	mainWindow.clear(sf::Color(56, 120, 55));
	map.display(mainWindow);
	mainWindow.setView(view);
	player.display(mainWindow);
	statistics.display(mainWindow);
	mainWindow.display();
}
//==================================================================
void Game::processEvent()
{
	sf::Event event;
	//isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;
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
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.setDirection(sf::Vector2f(-player.speed, 0)); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.setDirection(sf::Vector2f(player.speed, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		if (player.onGround)
		{
			player.setDirection(sf::Vector2f(0, -25*player.speed));
			player.onGround = false;
		}*/
}
//==================================================================
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	//isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;
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
void Game::update()
{
	//sf::Vector2f direction(0.f, 0.f);
	if (isMovingUp)
		if (player.onGround)
		{
			player.setDirectionY(-30*player.speed);
			player.onGround = false;
		}
	if (isMovingDown)
		player.setDirectionY(player.speed);
	if (isMovingLeft)
		player.setDirectionX(-player.speed);
	if (isMovingRight)
		player.setDirectionX(player.speed);

	//player.setDirection(direction);
	player.update();	
	collision();
}
//==================================================================
void Game::screenScrolling()
{
	float curPosX = player.getPosition().x - screenDimensions.x/4;
	float curPosY = player.getPosition().y - screenDimensions.y/4;

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
void Game::collision(/*bool isMovingX*/)
{
	/*for ( int i = player.getPosition().y/32; 
		i<(player.getPosition().y + 32)/32;
		++i)
		for ( int j = player.getPosition().x/32; 
		j<(player.getPosition().x + 32)/32;
		++j)
			{
				// processing
				if (map.mapArray[i][j] == 'b' || map.mapArray[i][j] == 'p' || map.mapArray[i][j] == '0')
				{
					if (player.getDirection().y > 0)
						player.setPosition(sf::Vector2f(player.getPosition().x, i*32 - 32));
					if (player.getDirection().y < 0)
						player.setPosition(sf::Vector2f(player.getPosition().x, i*32 + 32));
				}
			}*/

	/*for (int i=0; i<map.mapArray.size(); ++i)
	{
		for (int j=0; j<map.mapArray[0].size(); ++j)
		{*/
	bool col=false;
	for ( int i = player.getPosition().y/32; i<(player.getPosition().y + 32)/32; ++i)
	{
		for ( int j = player.getPosition().x/32; j<(player.getPosition().x + 32)/32; ++j)
		{
			if (map.mapArray[i][j] == 'b' || map.mapArray[i][j] == 'p' /*|| map.mapArray[i][j] == '0'*/)
			{	
				int bottom, top, left, right;
				bottom = i * 32 + 32;
				top = i * 32;
				left = j * 32;
				right = j * 32 + 32;
				
				if (player.right >= left && player.getDirection().x > 0){
					player.setPosition(sf::Vector2f(j*32-32, player.getPosition().y));
					break;
				}
				else if (player.left <= right && player.getDirection().x < 0){
					player.setPosition(sf::Vector2f(j*32 + 32, player.getPosition().y));
					break;
				}
				else if (player.bottom >= top && player.getDirection().y > 0){
					player.setPosition(sf::Vector2f(player.getPosition().x, i*32-32));
					player.onGround = true;
					break;
				}
				else if (player.top <= bottom && player.getDirection().y < 0){
					player.setPosition(sf::Vector2f(player.getPosition().x, i*32 + 32));
					break;
				}
			}
		}
	}
}
//==================================================================
//==================================================================
//==================================================================
//==================================================================