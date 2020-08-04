#pragma once
#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void FillLevel(int arr[20][25]);

private:

	SDL_Rect srcRect, destRect;
	SDL_Texture* grass_tex;
	SDL_Texture* stone_tex;
	SDL_Texture* water_tex;

	int map[20][25];

};

