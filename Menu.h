#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>

class Menu
{
private:
	sf::Text menuTextPressSomething;
	sf::Text menuTextNewGame;
	sf::Text menuTextLoadGame;
	sf::Text menuTextSaveGame;
	sf::Text menuTextContinue;
	sf::Text menuTextExit;

	sf::Font menuFont;

public:
	Menu();
	void display(sf::RenderWindow &window);
	sf::Text menuTextPause;
};


#endif MENU_H