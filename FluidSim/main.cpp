
#include <iostream>
#define main SDL_main
#include <SDL2/SDL.h>
#include <tuple>
#include <string>
#include<time.h>
#include<math.h>
#include<random>
//#include"Fluid.h"
#define SIM_SIZE 200
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1
int Index(int x, int y)
{
	return (y * SIM_SIZE + x);
}

struct Particle {
private :
	int cellx;
	int celly;
	float velocityx;
	float velocityy;
public: 
	void updateParticle(int xarr[],int yarr[])
	{
		if (0 < cellx + velocityx + 0.5 && cellx + velocityx + 0.5 < 255)
		{
			cellx += (int)velocityx + 0.5;
		}
		if (0 < celly + velocityy + 0.5 && celly + velocityy + 0.5 < 255)
		{
			celly += (int)velocityy + 0.5;
		}
		
		velocityx = xarr[Index(cellx, celly)];
		velocityy = yarr[Index(cellx, celly)];
	}
	int returnX() { return cellx; }
	int returnY() { return celly; }
	float returnU() { return velocityx; }
	float returnV() { return velocityy; }
	void setX(int xval) { this->cellx = xval; }
	void setY(int yval) { this->celly = yval; }
	void setU(float uval) { this->velocityx = uval; }
	void setV(float vval) { this->velocityy = vval; }
};

int main(int argc, char* argv[])
{
	int velocityx[SIM_SIZE * SIM_SIZE] = { 10 };
	int velocityy[SIM_SIZE * SIM_SIZE] = { -10 };

	bool keep_window_open = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SIM_SIZE, SIM_SIZE, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	// Syntax
	//std::cout << "Hello";
	
	static int array1[SIM_SIZE*SIM_SIZE] = {0};
	int y = 0;
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SIM_SIZE, SIM_SIZE);
	Uint32* pixels = new Uint32[SIM_SIZE * SIM_SIZE];

	
	
	

	const int particlecount = 3;
	Particle particles[particlecount] = {};
	for (int i = 0; i < SIM_SIZE * SIM_SIZE; ++i)
	{
		
		velocityx[i] = rand() % 19 + (-9);
		velocityy[i] = rand() % 19 + (-9);
	}
	for (int i = 0; i < particlecount; ++i)
	{
		Particle a;
		
		a.setX(rand() % SIM_SIZE);
		a.setY(rand() % SIM_SIZE);
		a.setU(Index(a.returnX(), a.returnY()));
		a.setV(Index(a.returnX(), a.returnY()));
		particles[i] = a;
		std::cout << a.returnX();
	}
	
	memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
	while (keep_window_open)
	{
		/*
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
		*/
		for (int i = 0; i < particlecount; ++i)
		{
			particles[i].updateParticle(velocityx, velocityy);
			std::cout << particles[i].returnU();
			pixels[Index(particles[i].returnX(), particles[i].returnY())] = SDL_MapRGB(window_surface->format, 255, 255,255);;
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