#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/include/box2d.h>
#include <CollisionDetection.h>

class Simulation
{
public:
	Simulation();
	~Simulation();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents(b2Body* characterBody, bool onAir);
	void update(float x, float y, float rot = 0.0f, float dt = 0.0f);
	void render();
	void clean();

	bool running() { return isRunning; }

	//static SDL_Event event;

	float ppm = 64.0f;
	float movingSpeed = 75.0f/ppm;

	bool KEYS_DOWN[322];  
	bool KEYS_UP[322];
	bool APPLIED[322];

private:
	bool isRunning;
	int count = 0;
	float timeCount = 0.0f;
	int hWindow, wWindow;
	float xScale = 1.0f, yScale = 1.0f;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* SIMULATION_H */