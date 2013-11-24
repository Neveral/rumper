#include "Player.h"

//=============================================================
const float Player::speed = 0.12f;
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
void Player::update(float time)
{
	time = time / 400;
	//if(time>20) time = 20;
	
	bottom = sprite.getPosition().y + texture.getSize().y;
	left = sprite.getPosition().x;
	right = sprite.getPosition().x + texture.getSize().x;
	top = sprite.getPosition().y;
	
	sprite.move(direction.x*time,0);
	collision(true);

	sprite.move(0, direction.y*time);
	onGround=false;
	collision(false);

	if (!onGround)
		direction.y = direction.y + 0.0005*time;

	direction.x=0.f;
}
//=============================================================
void Player::collision(bool isMovingX)
{
	for ( int i = getPosition().y/32; i<(getPosition().y + 32)/32; ++i)
	{
		for ( int j = getPosition().x/32; j<(getPosition().x + 32)/32; ++j)
		{
			if (map.mapArray[i][j] == 'b' || map.mapArray[i][j] == 'p' /*|| map.mapArray[i][j] == '0'*/)
			{	
				int bottom, top, left, right;
				bottom = i * 32 + 32;
				top = i * 32;
				left = j * 32;
				right = j * 32 + 32;
				
				if (/*right >= left &&*/ getDirection().x > 0 && isMovingX==true){
					setPosition(sf::Vector2f(j*32-32, getPosition().y));
					//break;
				}
				if (/*left <= right &&*/ getDirection().x < 0 && isMovingX==true){
					setPosition(sf::Vector2f(j*32 + 32, getPosition().y));
					//break;
				}
				if (/*bottom >= top &&*/ getDirection().y > 0 && isMovingX==false){
					setPosition(sf::Vector2f(getPosition().x, i*32-32));
					onGround = true;
					setDirectionY(0.f);
					//break;
				}
				if (/*top <= bottom &&*/ getDirection().y < 0 && isMovingX==false){
					setPosition(sf::Vector2f(getPosition().x, i*32 + 32));
					setDirectionY(0.f);
					//break;
				}
			}
		}
	}
}
//=============================================================
//=============================================================
//=============================================================
