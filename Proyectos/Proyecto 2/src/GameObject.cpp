#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren)
{
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);
}

void GameObject::update(int x, int y, int w, int h)
{
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

void GameObject::render(bool background)
{
	if (background)
	{
		SDL_RenderCopy(renderer, objTexture, NULL, NULL);
	}
	else
	{
		SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
	}
}
