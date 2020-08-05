#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	TileComponent() = default;
	

	TileComponent(int srcX, int srcY, int Xpos, int Ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = 32;
		srcRect.h = 32;
		dstRect.x = Xpos;
		dstRect.y = Ypos;
		dstRect.w = 64;
		dstRect.h = 64;
		
	}


	~TileComponent()
	{
		SDL_DestroyTexture(texture);

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect,SDL_FLIP_NONE);
	}
};
