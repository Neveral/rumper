#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include "Map.h"


class Player {

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f direction;

	sf::Texture healthTexture;
	sf::Sprite healthSprite;
	short int health;
	float currentFrame;

public:
	Player();
	
	void display(sf::RenderWindow* window);

	void setDirection(sf::Vector2f &direct);
	void setDirectionX(float dirX);
	void setDirectionY(float dirY);
	void setPosition(sf::Vector2f &position);
	void update();
	void collision(bool isMovingX);
	void reduceHelth();
	void updateHelth();

	sf::Vector2f getDirection()const;
	sf::Vector2f getPosition()const;

	bool onGround;
	static const float speed;
	float bottom, left, right, top;

	Map map;
};
#endif PLAYER_H