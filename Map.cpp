#include "Map.h"

const sf::Vector2i Map::blockSize=sf::Vector2i(32, 32);

Map::Map()
{

}
//============================================================
Map::Map(const char n)
{
	std::string mapFileName("Media/map");
	mapFileName.push_back(n);
	mapFileName += ".txt";

	std::vector<char> tempMapArray;
	std::ifstream mapFile(mapFileName.c_str());
	if (!mapFile.is_open())
		throw "Error: Can't load map file";
		
	std::string mapTextureFileName;
	mapFile >> mapTextureFileName;
	mapFile.get(); // skip new line symbol

	if (!mapTexture.loadFromFile("Media/tilemap.png"))
		throw ("Error: Can't load mapTexture from " + mapTextureFileName);

	mapSprite.setTexture(mapTexture);

	while(!mapFile.eof())
	{
		char ch;
		ch = mapFile.get();

		tempMapArray.push_back(ch);

		if (mapFile.peek() == '\n' || mapFile.peek() == EOF)
		{
			mapArray.push_back(tempMapArray);
			tempMapArray.clear();
			mapFile.get(); // skip new line symbol
		}
	}
}
//================================================================
void Map::display(sf::RenderWindow* window)
{
	for (int i=0; i<mapArray.size(); ++i)
	{
		for (int j=0; j<mapArray[0].size(); ++j)
		{
			mapSprite.setPosition(j*blockSize.x, i*blockSize.y);

			if (mapArray[i][j] == 'b')
				mapSprite.setTextureRect(sf::IntRect(0, 0, blockSize.x, blockSize.y));
			if (mapArray[i][j] == 'p')
				mapSprite.setTextureRect(sf::IntRect(32, 0, blockSize.x, blockSize.y));
			if (mapArray[i][j] == 'w')
				mapSprite.setTextureRect(sf::IntRect(64, 0, blockSize.x, blockSize.y));
			if (mapArray[i][j] == 'd')
				mapSprite.setTextureRect(sf::IntRect(0, 32, blockSize.x*2, blockSize.y*2));

			if (mapArray[i][j] == '0' || mapArray[i][j] == ' ' || mapArray[i][j] == 'f')
				continue;

			window->draw(mapSprite);
		}
	}
}

