#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "SpriteComponent.h"

class TileComponent : public Component
{
public:
	TransformComponent* transforms;
	SpriteComponent* sprites;

	SDL_Rect tileRect;
	
	int tileID;
	const char* path;


	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "assets/grass.png";
			break;
		case 1:
			path = "assets/stone.png";
			break;
		case 2:
			path = "assets/water.png";
		default:
			break;
		}
	}
	void init() override
	{
		entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x),static_cast<float>(tileRect.y),tileRect.w, tileRect.h,1);
		transforms = &entity->getComponent<TransformComponent>();
		entity->addComponent<SpriteComponent>(path);
		sprites = &entity->getComponent<SpriteComponent>();

	}


};
