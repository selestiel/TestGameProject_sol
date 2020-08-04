#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Texture* textures =  IMG_LoadTexture(Game::renderer,texture);
	return textures;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect)
{
	SDL_RenderCopy(Game::renderer, tex, &srcRect, &dstRect);
}
