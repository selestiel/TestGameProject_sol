#pragma once
#include "SDL.h"
#include "SDL_image.h"




class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	bool running()
	{
		return isRunning;
	}
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;


	
	bool isRunning;

private:
	int count{ 0 };
	SDL_Window* window;
};

