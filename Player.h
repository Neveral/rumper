#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include "Map.h"


class Player {

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f direction;

	
public:
	Player();
	
	void display(sf::RenderWindow &window);

	void setDirection(sf::Vector2f &direct);
	void setDirectionX(float dirX);
	void setDirectionY(float dirY);
	sf::Vector2f getDirection()const;
	void setPosition(sf::Vector2f &position);
	sf::Vector2f getPosition()const;

	void update(float time);
	void collision(bool isMovingX);

public:
	bool onGround;
	static const float speed;
	float bottom, left, right, top;

	Map map;
};
#endif PLAYER_H