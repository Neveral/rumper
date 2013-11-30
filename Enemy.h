#ifndef ENEMY_H
#define ENEMY_H
#include "Map.h"

#include "SFML\Graphics.hpp"

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f direction;
	bool onGround;
	float currentFrame;

public:
	Enemy();
	Enemy(float x, float y);

	static const float speed;
	static int changeDirectionCounter;
	static const sf::Vector2i textureFrameSize;

	void display(sf::RenderWindow* window);
	void update(Map* map);
	void collision(Map* map, bool isMovingX);
	void setDirectionX(float dirX);
	void setDirectionY(float dirY);
	void setPosition(sf::Vector2f &position);
	sf::Vector2f getPosition()const;

};


#endif