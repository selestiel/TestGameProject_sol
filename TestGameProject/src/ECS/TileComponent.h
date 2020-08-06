#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"


class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;

	TileComponent() = default;
	

	TileComponent(int srcX, int srcY, int Xpos, int Ypos, int tsize, int tscale, std::string ID)
	{
		texture = Game::assets->GetTexture(ID);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = tsize;
		srcRect.h = tsize;
		
		position.x = static_cast<float>(Xpos);
		position.y = static_cast<float>(Ypos);
		
		dstRect.w = tsize * tscale;
		dstRect.h = tsize * tscale;
		
	}


	~TileComponent()
	{
		SDL_DestroyTexture(texture);

	}

	void update() override
	{
		dstRect.x = static_cast<int>(position.x - Game::camera.x);
		dstRect.y = static_cast<int>(position.y - Game::camera.y);
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect,SDL_FLIP_NONE);
	}
};
