#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"



Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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

	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(150, 150, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("stone");
	tile2.addComponent<TileComponent>(250, 250, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("water");

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/water.png");
	wall.addComponent<ColliderComponent>("wall");
	
	
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
	for (auto& cs : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cs);
		
	}

};
void Game::render()
{
	SDL_RenderClear(renderer);
	
	map->DrawMap();
	player.draw();
	wall.draw();
	tile0.draw();
	tile1.draw();
	tile2.draw();

	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}