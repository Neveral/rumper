#include <SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	try{
		Game game;
		game.run();
		system("pause");
	}
	catch(char* msg){
		std::cout << msg << std::endl;
		system("pause");
	}
	
}