#ifndef STATISTICS_H
#define STATISTICS_H

#include "SFML\Graphics.hpp"

class Statistics
{
private:
	sf::Font font;
	
	int numFrames;
	sf::Time updateTime;
public:
	Statistics();
	sf::Text text;
	void updateStatistics(sf::Time elapsedTime);
	void display (sf::RenderWindow* window);
};

#endif