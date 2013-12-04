#include "Player.h"

//=============================================================
const float Player::speed = 0.12f;
const sf::Vector2i Player::textureFrameSize = sf::Vector2i(48, 48);
//=============================================================
Player::Player()
{
	if (!texture.loadFromFile("Media/player3.png"))
		throw "The player.png file not found!";
	direction = sf::Vector2f(0,0);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, textureFrameSize.x, textureFrameSize.y));
	rect = sf::FloatRect(100, 50, textureFrameSize.x, textureFrameSize.y);
	sprite.setPosition(100.f,50.f);
	onGround = false;

	if(!healthTexture.loadFromFile("Media/health.png"))
		throw "The health.png file not found!";
	healthSprite.setTexture(healthTexture);
	healthSprite.setPosition(200, 10);
	healthSprite.setTextureRect(sf::IntRect(0, 0, 152, 38));
	health = 3;
	currentFrame = 0;
}
//=============================================================
void Player::display(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(healthSprite);
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
void Player::update(Map* &map, int &currentLevel)
{
	updateHealth();

	const float time = 20;

	/*bottom = sprite.getPosition().y + texture.getSize().y;
	left = sprite.getPosition().x;
	right = sprite.getPosition().x + texture.getSize().x;
	top = sprite.getPosition().y;*/
	
	sprite.move(direction.x*time,0);
	collision(map, currentLevel, true);

	sprite.move(0, direction.y*time*2); 
	direction.y = direction.y + 0.001*time;
	collision(map, currentLevel, false);

	currentFrame += time * 0.006;
	if(currentFrame > 5) 
		currentFrame -= 5;

	if(direction.x > 0)
		sprite.setTextureRect(sf::IntRect(textureFrameSize.x*int(currentFrame), 0, textureFrameSize.x , textureFrameSize.y));
	if(direction.x == 0)
		sprite.setTextureRect(sf::IntRect(0, 0, textureFrameSize.x, textureFrameSize.y));
	if(direction.x < 0)
		sprite.setTextureRect(sf::IntRect(textureFrameSize.x*int(currentFrame)+textureFrameSize.x, 0, -textureFrameSize.x, textureFrameSize.y));

	/*if (!onGround)
		direction.y = direction.y + 0.001*time;*/

	rect.left = getPosition().x;
	rect.top = getPosition().y;

	direction.x=0.f;
}
//=============================================================
void Player::collision(Map* &map, int &currentLevel, bool isMovingX)
{
	for ( int i = getPosition().y/32; i<(getPosition().y + textureFrameSize.y)/32; ++i)
	{
		for ( int j = getPosition().x/32; j<(getPosition().x + 32)/32; ++j)
		{
			if (map->mapArray[i][j] == 'b' || map->mapArray[i][j] == 'p' || map->mapArray[i][j] == '0')
			{	
				int bottom, top, left, right;

				bottom = i * 32 + 32;
				top = i * 32;
				left = j * 32;
				right = j * 32 + 32;
				
				if (/*right >= left &&*/ direction.x > 0 && isMovingX==true){
					setPosition(sf::Vector2f(j*32-32, getPosition().y));
					//break;
				}
				if (/*left <= right &&*/ direction.x < 0 && isMovingX==true){
					setPosition(sf::Vector2f(j*32 + 32, getPosition().y));
					//break;
				}
				if (/*bottom >= top &&*/ direction.y > 0 && isMovingX==false){
					setPosition(sf::Vector2f(getPosition().x, i*32-textureFrameSize.y));
					onGround = true;
					setDirectionY(0.f);
					//break;
				}
				if (/*top <= bottom &&*/ direction.y < 0 && isMovingX==false){
					setPosition(sf::Vector2f(getPosition().x, i*32 + 32));
					setDirectionY(0.f);
					//break;
				}
			}
			if(map->mapArray[i][j] == 'f')
			{
				++currentLevel;
				//std::cout << "Finish!!!" << std::endl;
				if(currentLevel < 3)
				{
					if(map != NULL) delete map;
					map = new Map(currentLevel);
					sprite.setPosition(100.f,50.f);
					health = 3;
					break;
				}
			}
		}
	}
}
//=============================================================
void Player::reduceHealth()
{
	--health;
}
//=============================================================
void Player::updateHealth()
{
	switch (health)
	{
		case 3:
			healthSprite.setTextureRect(sf::IntRect(0, 0, 152, 38));
			break;
		case 2:
			healthSprite.setTextureRect(sf::IntRect(0, 43, 152, 38));
			break;
		case 1:
			healthSprite.setTextureRect(sf::IntRect(0, 86, 152, 38));
			break;
		case 0:
			healthSprite.setTextureRect(sf::IntRect(0, 129, 152, 38));
			break;
	}
}
//=============================================================
void Player::setHealth(short int hp)
{
	health = hp;
}
//=============================================================
short int Player::getHealth()const
{
	return health;
}
//=============================================================
void Player::setHealthSpritePosition(float x, float y)
{
	healthSprite.setPosition(x, y);
}
//=============================================================
//=============================================================
