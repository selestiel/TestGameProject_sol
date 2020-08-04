#include "Map.h"
#include "TextureManager.h"
#include <cstdlib>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"


int lvl1[20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int lvl2[20][25];

Map::Map()
{
	grass_tex = TextureManager::LoadTexture("assets/grass.png");
	stone_tex = TextureManager::LoadTexture("assets/stone.png");
	water_tex = TextureManager::LoadTexture("assets/water.png");
	FillLevel(lvl2);
	LoadMap(lvl2);
	srcRect.x =  0 ;
	srcRect.y =  0 ;
	destRect.x = 0 ;
	destRect.y = 0 ;
	srcRect.w = 32;
	srcRect.h = 32;
	destRect.w = 32;
	destRect.h = 32;
}

Map::~Map()
{
	SDL_DestroyTexture(grass_tex);
	SDL_DestroyTexture(water_tex);
	SDL_DestroyTexture(stone_tex);
}

void Map::LoadMap(int arr[20][25])
{
	for (int row{ 0 }; row < 20; row++)
	{
		for (int col{ 0 }; col < 25; col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}
void Map::FillLevel(int arr[20][25]) 
{
	for (int i = 0; i < 20; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			arr[i][j] = rand() % 3;
		}
	}
}

void Map::DrawMap()
{
	int type{ 0 };

	for (int row{ 0 }; row < 20; row++)
	{
		for (int col{ 0 }; col < 25; col++)
		{
			type = map[row][col];
			destRect.x = col * 32;
			destRect.y = row * 32;
			switch (type) 
			{
			case 0:
				TextureManager::Draw(grass_tex, srcRect, destRect);
				break;
			case 1:
				TextureManager::Draw(stone_tex, srcRect, destRect);
				break;
			case 2:
				TextureManager::Draw(water_tex, srcRect, destRect);
				break;
			default:
				break;
			}
		}
	}
}
