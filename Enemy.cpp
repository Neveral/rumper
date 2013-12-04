#include "Enemy.h"

const float Enemy::speed = 0.06f;
const sf::Vector2i Enemy::textureFrameSize = sf::Vector2i(48,48);
int Enemy::changeDirectionCounter = 0;

Enemy::Enemy()
{
	if(!texture.loadFromFile("Media/enemy.png"))
		throw "File enemy.png not found!";
	sprite.setTexture(texture);
	sprite.setPosition(300, 50);
	sprite.setTextureRect(sf::IntRect(0, 0, textureFrameSize.x, textureFrameSize.y));
	direction = sf::Vector2f(0,0);
	onGround = false;
	currentFrame = 0;

	/*if(!bulletTexture.loadFromFile("Media/bullet.png"))
		throw "File bullet.png not found";
	bulletSprite.setTexture(bulletTexture);*/
}
//======================================================
Enemy::Enemy(float x, float y)
{
	if(!texture.loadFromFile("Media/enemy.png"))
		throw "File enemy.png not found!";
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::IntRect(0, 0, textureFrameSize.x, textureFrameSize.y));
	rect = sf::FloatRect(x,y, textureFrameSize.x,textureFrameSize.y);
	life = true;
	direction = sf::Vector2f(0,0);
	onGround = false;
	currentFrame = 0;

	/*if(!bulletTexture.loadFromFile("Media/bullet.png"))
		throw "File bullet.png not found";
	bulletSprite.setTexture(bulletTexture);*/
	//bulletSprite.setPosition(x, y);
}
//=======================================================
void Enemy::display(sf::RenderWindow* window)
{
	window->draw(sprite);
	//window->draw(bulletSprite);
}
//=======================================================
void Enemy::update(Map* map)
{
	if(life){
	const float time = 20;
	++changeDirectionCounter;
	if(changeDirectionCounter <= 200)
		direction.x = speed*time;
	else
		direction.x = -speed*time;	

	sprite.move(direction.x, 0);

	if(changeDirectionCounter >= 400)
		changeDirectionCounter = 0;

	collision(map, true);

	sprite.move(0, direction.y*time*2);
	onGround=false;
	collision(map, false);

	if (!onGround)
		direction.y = direction.y + 0.001*time;

	currentFrame += time * 0.006;
	if(currentFrame > 5) 
		currentFrame -= 5;

	if(direction.x > 0)
		sprite.setTextureRect(sf::IntRect(textureFrameSize.x*int(currentFrame), 0, textureFrameSize.x , textureFrameSize.y));
	if(direction.x == 0)
		sprite.setTextureRect(sf::IntRect(0, 0, textureFrameSize.x, textureFrameSize.y));
	if(direction.x < 0)
		sprite.setTextureRect(sf::IntRect(textureFrameSize.x*int(currentFrame)+textureFrameSize.x, 0, -textureFrameSize.x, textureFrameSize.y));
	
	sprite.setColor(sf::Color::White);	
	rect.left = getPosition().x;
	rect.top = getPosition().y;
	direction.x=0.f;
	}
	else
		sprite.setColor(sf::Color::Blue);
	}
//=======================================================
void Enemy::collision(Map* map, bool isMovingX)
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
		}
	}
}
//=======================================================
sf::Vector2f Enemy::getPosition()const
{
	return sprite.getPosition();
}
//=======================================================
void Enemy::setPosition(sf::Vector2f &position)
{
	sprite.setPosition(position);
}
//=======================================================
void Enemy::setDirectionX(float dirX)
{
	direction = sf::Vector2f(dirX, direction.y);
}
//=============================================================
void Enemy::setDirectionY(float dirY)
{
	direction = sf::Vector2f(direction.x, dirY);
}
//=======================================================