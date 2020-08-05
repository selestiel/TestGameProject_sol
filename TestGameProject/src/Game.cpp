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
SDL_Rect Game::camera{ 0,0,1280,720};


bool Game::isRunning = false;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "assets/terrain_ss.png";

enum grouplabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupMobs,
	groupColliders

};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& mobs(manager.getGroup(groupMobs));


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

	Map::LoadMap("assets/map.map",25,20);

	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("assets/player_anims.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/water.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
	
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
	
	camera.x = player.getComponent<TransformComponent>().position.x - (camera.w / 2);
	camera.y = player.getComponent<TransformComponent>().position.y  - (camera.h / 2);
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > camera.w)
	{
		camera.x = camera.w;
	}
	if (camera.y > camera.h)
	{
		camera.y = camera.h;
	}

	//
	for (auto& cs : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cs);
		
	}
	//

};




void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}for (auto& p : players)
	{
		p->draw();
	}for (auto& m : mobs)
	{
		m->draw();
	}
	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}
