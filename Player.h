#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include "Map.h"


class Player {

private:
	sf::Texture texture;
	sf::Sprite sprite;
	static const sf::Vector2i textureFrameSize;
	sf::Vector2f direction;

	sf::Texture healthTexture;
	sf::Sprite healthSprite;
	short int health;
	float currentFrame;

public:
	Player();
	sf::FloatRect rect;
	void display(sf::RenderWindow* window);

	void setDirection(sf::Vector2f &direct);
	void setDirectionX(float dirX);
	void setDirectionY(float dirY);
	void setPosition(sf::Vector2f &position);
	void update(Map* &map, int &currentLevel);
	void collision(Map* &map, int &currentLevel, bool isMovingX);
	void reduceHealth();
	void updateHealth();
	void setHealth(short int hp);
	short int getHealth()const;
	void setHealthSpritePosition(float x, float y);

	sf::Vector2f getDirection()const;
	sf::Vector2f getPosition()const;

	bool onGround;
	static const float speed;
	//float bottom, left, right, top;

	//Map map;
};
#endif PLAYER_H