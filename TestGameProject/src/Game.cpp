#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"



Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen == true) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) 
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}

	map = new Map();
	
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();


	wall.addComponent<TransformComponent>(300.0, 300.0, 300, 20,1);
	wall.addComponent<SpriteComponent>("assets/water");
	SDL_Color white = { 255,255,255,255 };
}
void Game::handleEvents() 
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
};
void Game::update()
{

	manager.refresh();
	manager.update();
	manager.draw();

};
void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	player.draw();

	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}