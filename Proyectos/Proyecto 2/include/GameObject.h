#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Simulation.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren);
	~GameObject();

	void update(int x, int y, int w, int h);
	void render(bool background = false);

private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

#endif /* GAMEOBJECT_H */
