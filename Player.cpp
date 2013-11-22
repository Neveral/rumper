#include "Player.h"

//=============================================================
const float Player::speed = 5.0f;
//=============================================================
Player::Player()
{
	if (!texture.loadFromFile("Media/player.png"))
		{//throw "The player.png file not found!"
	}
	direction = sf::Vector2f(0,0);
	sprite.setTexture(texture);
	sprite.setPosition(100.f,50.f);
	onGround = false;
}
//=============================================================
void Player::display(sf::RenderWindow &window)
{
	window.draw(sprite);
}
//=============================================================
void Player::setDirection(sf::Vector2f &direct)
{
	direction = direct;
}
//=============================================================
void Player::setDirectionX(float dirX)
{
	direction = sf::Vector2f(dirX, direction.y);
}
//=============================================================
void Player::setDirectionY(float dirY)
{
	direction = sf::Vector2f(direction.x, dirY);
}
//=============================================================
sf::Vector2f Player::getDirection() const
{
	return direction;
}
//=============================================================
void Player::setPosition(sf::Vector2f &position)
{
	sprite.setPosition(position);
}
//=============================================================
sf::Vector2f Player::getPosition()const
{
	return sprite.getPosition();
}
//=============================================================
void Player::update()
{
	bottom = sprite.getPosition().y + texture.getSize().y;
	left = sprite.getPosition().x;
	right = sprite.getPosition().x + texture.getSize().x;
	top = sprite.getPosition().y;
	
	sprite.move(direction);
	if (!onGround)
	{
		direction = sf::Vector2f(direction.x, speed/2);
	}
	setDirectionX(0);
}
//=============================================================
//=============================================================
//=============================================================
//=============================================================
