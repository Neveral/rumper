#include "Statistics.h"

//=================================================================
Statistics::Statistics(): font(), text(), updateTime(), numFrames(0)
{
	if (!font.loadFromFile("Media/Sansation.ttf"))
		throw "Error! Font is not loading! ";
	text.setFont(font);
	text.setPosition(5.f, 5.f);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Regular);
	text.setCharacterSize(10);
}
//=================================================================
void Statistics::updateStatistics(sf::Time elapsedTime)
{
	updateTime += elapsedTime;
	numFrames += 1;

	if (updateTime >= sf::seconds(1.0f))
	{
		text.setString("Frames / Seconds = " + 
			std::to_string(numFrames) + "\n" +
			"Time / Update = " + 
			std::to_string( updateTime.asSeconds() / numFrames));

	updateTime -= sf::seconds(1.0f);
	numFrames = 0;
	}

}
//=================================================================
void Statistics::display(sf::RenderWindow &window)
{
	window.draw(text);
}
//=================================================================
//=================================================================