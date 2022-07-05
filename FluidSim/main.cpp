
#include <iostream>
#define main SDL_main
#include <SDL2/SDL.h>
#include <tuple>
#include <string>
#include<time.h>
#include"Fluid.h"
#define SIM_SIZE 400
struct Particle {
	int cellx;
	int celly;
	float velocityx;
	float velocityy;
};
int Index(int x, int y)
{
	return (y * SIM_SIZE + x);
}
int main(int argc, char* argv[])
{
	const int arraysize = SIM_SIZE*SIM_SIZE;
	bool keep_window_open = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SIM_SIZE, SIM_SIZE, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	// Syntax
	//std::cout << "Hello";
	
	static int simulationlength = SIM_SIZE;
	static int simulationsize = simulationlength * simulationlength * simulationlength;
	static int array1[SIM_SIZE*SIM_SIZE] = {0};
	int y = 0;
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SIM_SIZE, SIM_SIZE);
	Uint32* pixels = new Uint32[SIM_SIZE * SIM_SIZE];

	memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
	const int particlecount = 100;
	Particle particles[particlecount];
	srand(time(0));
	Fluid a();
	for (int i = 0; i < particlecount; ++i)
	{
		Particle a = { 0 };
		a.cellx = rand() % SIM_SIZE;
		a.celly = rand() % SIM_SIZE;
		a.velocityx = Index(a.cellx, a.celly);
		a.velocityy = Index(a.cellx, a.celly);
	}
	while (keep_window_open)
	{
		for (int i = 0; i < SIM_SIZE * SIM_SIZE; ++i)
		{
			
			int x = i % simulationlength;

			array1[i] = 2 * y;
			if (x == 0 && i != 0) {
				y += 1;
			}
			
			//pixels[i] = SDL_MapRGB(window_surface->format, array1[i]*i, array1[i]*i,array1[i]);
			pixels[i] = i + x + y;
			//std::cout << std::to_string(x) + " " + std::to_string(y) + "\n";

		}
		std::cout << "tick";
		
		//Texture Update
		SDL_UpdateTexture(texture, NULL, pixels, SIM_SIZE * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			

			//SDL_WaitEvent(&e);
			switch (e.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;
			}
			
			
			
		}
	}
	
	return 0;
}