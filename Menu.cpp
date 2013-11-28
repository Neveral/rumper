#include "Menu.h"

const sf::Vector2i screenDimensions(800, 600);

Menu::Menu()
{
	if (!menuFont.loadFromFile("Media/Sansation.ttf"))
		throw "Error! Font is not loading! ";

	menuTextPause.setFont(menuFont);
	menuTextPause.setPosition(15, screenDimensions.y*0.01);
	menuTextPause.setColor(sf::Color::White);
	menuTextPause.setStyle(sf::Text::Regular);
	menuTextPause.setCharacterSize(48);

	menuTextPressSomething.setFont(menuFont);
	menuTextPressSomething.setPosition(15, screenDimensions.y*0.2);
	menuTextPressSomething.setColor(sf::Color::White);
	menuTextPressSomething.setStyle(sf::Text::Regular);
	menuTextPressSomething.setCharacterSize(36);

	menuTextNewGame.setFont(menuFont);
	menuTextNewGame.setPosition(15, screenDimensions.y*0.3);
	menuTextNewGame.setColor(sf::Color::White);
	menuTextNewGame.setStyle(sf::Text::Regular);
	menuTextNewGame.setCharacterSize(36);

	menuTextContinue.setFont(menuFont);
	menuTextContinue.setPosition(15, screenDimensions.y*0.4);
	menuTextContinue.setColor(sf::Color::White);
	menuTextContinue.setStyle(sf::Text::Regular);
	menuTextContinue.setCharacterSize(36);

	menuTextLoadGame.setFont(menuFont);
	menuTextLoadGame.setPosition(15, screenDimensions.y*0.5);
	menuTextLoadGame.setColor(sf::Color::White);
	menuTextLoadGame.setStyle(sf::Text::Regular);
	menuTextLoadGame.setCharacterSize(36);

	menuTextSaveGame.setFont(menuFont);
	menuTextSaveGame.setPosition(15, screenDimensions.y*0.6);
	menuTextSaveGame.setColor(sf::Color::White);
	menuTextSaveGame.setStyle(sf::Text::Regular);
	menuTextSaveGame.setCharacterSize(36);

	menuTextExit.setFont(menuFont);
	menuTextExit.setPosition(15, screenDimensions.y*0.7);
	menuTextExit.setColor(sf::Color::White);
	menuTextExit.setStyle(sf::Text::Regular);
	menuTextExit.setCharacterSize(36);

	menuTextPause.setString(".:Pause:.");
	menuTextPressSomething.setString("Press 1-5 to select a menu item:");
	menuTextNewGame.setString("1. New Game");
	menuTextContinue.setString("2. Continue");
	menuTextLoadGame.setString("3. Load Game");
	menuTextSaveGame.setString("4. Save Game");
	menuTextExit.setString("5. Exit");
}

void Menu::display(sf::RenderWindow &window)
{
	window.draw(menuTextPause);
	window.draw(menuTextPressSomething);
	window.draw(menuTextNewGame);
	window.draw(menuTextContinue);
	window.draw(menuTextLoadGame);
	window.draw(menuTextSaveGame);
	window.draw(menuTextExit);
}