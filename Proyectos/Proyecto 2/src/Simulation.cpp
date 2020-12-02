#include "Simulation.h"
#include "TextureManager.h"
#include "GameObject.h"

//Se Declaran los objetos que contienen la informacion del objeto como el sprite y la posicion en pantalla.
GameObject* background;
GameObject* ghost;
GameObject* ghost2;
GameObject* ghost3;
GameObject* ghost4;
GameObject* orb;
GameObject* orb2;
GameObject* orb3;
GameObject* bat;
GameObject* spider;
GameObject* pin;


Simulation::Simulation()
{}

Simulation::~Simulation()
{}

void Simulation::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialized!" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		std::cout << "Couldn't initiate SDL..." << std::endl;
		isRunning = false;
	}

	//Se le asigna a traves del constructor el sprite de cada objeto que se encuentra en la carpeta de Assets.
	background = new GameObject("assets/cemetery.png", renderer);
	ghost = new GameObject("assets/ghost-sprite.png", renderer);
	ghost2 = new GameObject("assets/ghost-sprite.png", renderer);
	ghost3 = new GameObject("assets/ghost-sprite.png", renderer);
	ghost4 = new GameObject("assets/ghost-sprite.png", renderer);
	orb = new GameObject("assets/orb.png", renderer);
	orb2 = new GameObject("assets/orb2.png", renderer);
	orb3 = new GameObject("assets/orb3.png", renderer);
	bat = new GameObject("assets/bat.gif", renderer);
	spider = new GameObject("assets/spider.png", renderer);
	pin = new GameObject("assets/spiderweb.png", renderer);
}

void Simulation::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Simulation::update(float dt)
{
	timeCount += dt;

	//Movimiento Armonico Simple
	ghost->update(400-64, 320 + 20 * (sin(2* timeCount)) -64, 128, 128);
	ghost2->update(100 + 60 * (sin(3 * timeCount)) - 32, 400 - 32, 64, 64);
	ghost3->update(100 + 60 * (sin(2 * timeCount)) - 32, 450 - 32, 64, 64);
	ghost4->update(100 + 60 * (sin(1 * timeCount)) - 32, 500 - 32, 64, 64);

	//Movimiento de Rotacion
	orb->update(400 + 100 *(cos(3 * timeCount))- 16, 320 + 100 * (sin(3 * timeCount)) - 16, 32, 32);
	orb2->update(400 + 150 * (cos(1 * timeCount)) - 16, 320 + 150 * (sin(1 * timeCount)) - 16, 32, 32);
	orb3->update(400 + 200 * (cos(5 * timeCount)) - 16, 320 + 200 * (sin(5 * timeCount)) - 16, 32, 32);

	//Movimiento Rayo de Ondas.
	float batx = (50 * timeCount) + 10 - 40 + bat_offset;
	std::cout << bat_offset << std::endl;
	bat->update(batx, 100 + 50 * (sin(2 * timeCount)) - 40, 80, 80);

	//Si el murcielago sale de la pantalla, se le resta al offset 1000 pixeles para que aparezca en el inicio.
	if (batx >= 880)
	{
		bat_offset -= 1000;
	}


	//Movimiento Pendulo
	float w = 0.26 * cos(0.7746 * timeCount);
	x = 700 + 250 * (sin(w)) - 40;
	y = 350 + 250 * (cos(w)) - 40;

	pin->update(700 - 32, 350 - 32, 64, 64);
	spider->update(x, y, 80, 80);



}

void Simulation::render()
{
	SDL_RenderClear(renderer);

	background->render(true);

	//Render de una linea para el pendulo.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 700, 350, x + 40, y + 40);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	//Render de los sprites en la escena.
	ghost->render();
	ghost2->render();
	ghost3->render();
	ghost4->render();
	orb->render();
	orb2->render();
	orb3->render();
	bat->render();
	pin->render();
	spider->render();

	SDL_RenderPresent(renderer);
}

void Simulation::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Simulation cleaned..." << std::endl;
}