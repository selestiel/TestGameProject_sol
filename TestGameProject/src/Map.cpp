#include "Map.h"
#include "Game.h"
#include <fstream>



Map::Map()
{
	
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char ctile;
	std::fstream mapFile;
	mapFile.open(path);
	int  srcX, srcY;


	for (int y{ 0 }; y < sizeY; y++)
	{
		for (int x{ 0 }; x < sizeX; x++)
		{
			mapFile.get(ctile);
			srcY = atoi(&ctile) * 32;
			mapFile.get(ctile);
			srcX = atoi(&ctile) * 32;

			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();

		}
	}
	mapFile.close();
}
