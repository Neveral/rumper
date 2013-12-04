#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);
const sf::Vector2i screenDimensions(800, 600);
const sf::Vector2i blockDimensions(32,32);
bool spike = true;



Game::Game() : mainWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), 
						  "Rumper", sf::Style::Close),
						  isMovingDown(false),
						  isMovingUp(false),
						  isMovingLeft(false),
						  isMovingRight(false),
						  menuVisible(false),
						  currentLevel(1)
{
	if(!soundBufferJump.loadFromFile("Media/jump.wav"))
		throw "Sound file jump.wav not found!";
	soundJump.setBuffer(soundBufferJump);

	if(!soundBufferHurt.loadFromFile("Media/hurt.wav"))
		throw "Sound file hurt.wav not found!";
	soundHurt.setBuffer(soundBufferHurt);

	map = new Map(currentLevel);
	enemy1 = new Enemy(600.f, 50.f);
	enemy2 = new Enemy(1000.f, 50.f);
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
			update(map, currentLevel);
		}

		if(player.getHealth() <= 0)
		{
			menu.menuTextPause.setString("Game Over");
			showMenu();
			menuVisible = true;
			enemy1->life=false;
			enemy2->life=false;
		}
		else
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
						player.reduceHealth();
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
					if(player.getHealth() > 0)
					{
						if(menuEvent.key.code == sf::Keyboard::Escape)
							menuVisible = false;
						if(menuEvent.key.code == sf::Keyboard::Num2)
						menuVisible = false;
					}
					if(menuEvent.key.code == sf::Keyboard::Num1)
						newGame();
					if(menuEvent.key.code == sf::Keyboard::Num3)
						loadGame();
					if(menuEvent.key.code == sf::Keyboard::Num4)
						saveGame();
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
void Game::update(Map* &map, int &currentLevel)
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

		if  (player.rect.intersects( enemy1-> rect ) )
		{
			if (enemy1->life) {
				if (!player.onGround) 
				{ 
					enemy1->setDirectionX(0); 
					enemy1->setDirectionY(-0.2); 
					enemy1->life=false;
				}
				else
				{
					player.reduceHealth();
					player.setPosition(sf::Vector2f(player.getPosition().x - 50, player.getPosition().y));
					soundHurt.play();
				}
			}
		}

		if  (player.rect.intersects( enemy2 -> rect ) )
		{
			if (enemy2->life) {
				if (!player.onGround) 
				{ 
					enemy2->setDirectionX(0); 
					enemy2->setDirectionY(-0.2); 
					enemy2->life=false;
				}
				else 
				{
					player.reduceHealth();
					player.setPosition(sf::Vector2f(player.getPosition().x - 50, player.getPosition().y));
					soundHurt.play();
				}
			}
		}

		player.update(map, currentLevel);
		if(currentLevel >= 3)
		{
			menu.menuTextPause.setString("Congratulations! Victory!");
			showMenu();
			menuVisible = true;
			exit;
		}
		enemy1->update(map);
		enemy2->update(map);



		if(currentLevel == 2 && spike == true)
		{
			if(enemy1->life == false)
				enemy1->life = true;
			enemy2->life = true;
			spike = false;
		}

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
	mainWindow.clear(sf::Color(128, 166, 255,  87));
	map->display(&mainWindow);
	player.display(&mainWindow);
	enemy1->display(&mainWindow);
	enemy2->display(&mainWindow);
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
void Game::newGame()
{
	currentLevel = 1;
	map = new Map(currentLevel);
	player.setPosition(sf::Vector2f(100.f, 50.f));
	enemy1->setPosition(sf::Vector2f(300.f, 50.f));
	enemy2->setPosition(sf::Vector2f(800.f, 50.f));
	enemy1->life = true;
	enemy2->life = true;
	player.setHealth(3);
	player.setDirection(sf::Vector2f(0,0));
	menu.menuTextPause.setString("Pause");
	isMovingDown = false;
	isMovingUp = false;
	isMovingLeft = false;
	isMovingRight = false;
	spike = true;
	menuVisible = false;
}
//==================================================================
void Game::saveGame()
{
	std::ofstream outFile("settings.ini");
	outFile << currentLevel;
	outFile << std::endl;
	outFile << player.getHealth();
	
	menuVisible = false;
}
//==================================================================
void Game::loadGame()
{
	short int hp;
	std::ifstream inFile("settings.ini");
	inFile >> currentLevel;
	inFile >> hp;

	switch (currentLevel)
	{
	case 1:
		if (map) delete map;
		map = new Map(currentLevel);
		player.setPosition(sf::Vector2f(100.f, 50.f));
		enemy1->setPosition(sf::Vector2f(300.f, 50.f));
		enemy2->setPosition(sf::Vector2f(800.f, 50.f));
		enemy1->life = true;
		enemy2->life = true;
		player.setHealth(hp);
		player.setDirection(sf::Vector2f(0,0));
		menu.menuTextPause.setString("Pause");
		isMovingDown = false;
		isMovingUp = false;
		isMovingLeft = false;
		isMovingRight = false;
		menuVisible = false;
		break;
	case 2:
		if (map) delete map;
		map = new Map(currentLevel);
		player.setPosition(sf::Vector2f(100.f, 50.f));
		enemy1->setPosition(sf::Vector2f(300.f, 50.f));
		enemy2->setPosition(sf::Vector2f(800.f, 50.f));
		enemy1->life = true;
		enemy2->life = true;
		player.setHealth(hp);
		player.setDirection(sf::Vector2f(0,0));
		menu.menuTextPause.setString("Pause");
		isMovingDown = false;
		isMovingUp = false;
		isMovingLeft = false;
		isMovingRight = false;
		menuVisible = false;
		break;
	}
	menuVisible = false;
}
//==================================================================