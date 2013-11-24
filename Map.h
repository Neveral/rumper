#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

class Map{

private:
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

public:
	Map();
	std::vector<std::vector<char>> mapArray; // !!!!!!!!!!!
	void display(sf::RenderWindow &window);
	static const sf::Vector2i blockSize;
	//char operator[] (int index);
};


#endif