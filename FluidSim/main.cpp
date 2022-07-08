
#include <iostream>
#define main SDL_main
#include <SDL2/SDL.h>
#include <tuple>
#include <string>
#include<time.h>
#include<math.h>
#include<random>
#include<thread>
#include"Fluid.h"
//#include"Fluid.h"
using std::this_thread::sleep_for;
#define SIM_SIZE 300


constexpr int TIME_TO_SLEEP = 1;
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1

		

int Index(int x, int y)
{
	return (y * SIM_SIZE + x);
}
void fluidStep(float xarr[], float yarr[])
{
	float timescale = 0.6;

}
struct Particle {
private :
	float cellx;
	float celly;
	float velocityx;
	float velocityy;
public: 
	void updateParticle(float x,float y)
	{
		if (1 < cellx + velocityx + 1 && cellx + velocityx + 1 < SIM_SIZE - 1)
		{
			cellx += velocityx;
		}
		else {
			velocityx = velocityx * -1;
		}
		if (1 < celly + velocityy + 1 && celly + velocityy + 1 < SIM_SIZE - 1)
		{
			celly += velocityy;
		}
		else {
			
			velocityy = velocityy * -1;
		}
		//velocityx *= 0.99;
		//velocityy *= 0.99;
		velocityx += 2*x;
		velocityy += 2*y;
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
float Fluid::velocityu[SIM_SIZE * SIM_SIZE] = { 0 };
float Fluid::velocityv[SIM_SIZE * SIM_SIZE] = { 0 };
float Fluid::uold[SIM_SIZE * SIM_SIZE] = { 0 };
float Fluid::vold[SIM_SIZE * SIM_SIZE] = { 0 };
int main(int argc, char* argv[])
{


	bool keep_window_open = true;
	//SDL2 (2D Renderer) Initialisation
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SIM_SIZE, SIM_SIZE, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SIM_SIZE, SIM_SIZE);
	Uint32* pixels = new Uint32[SIM_SIZE * SIM_SIZE];
	//init flowfield arrays
		Fluid f(0,0);
		//f.setFlowFields();
		
	//Randomize flow field velocities



	//Initialize visualisation particles & set initial positions.
	const int particlecount = 8000;
	Particle particles[particlecount] = {};
	for (int i = 0; i < particlecount; ++i)
	{
		Particle a;
		
		a.setX(rand() % SIM_SIZE);
		a.setY(rand() % SIM_SIZE);
		a.setU(Index(0,0));
		a.setV(Index(0,0));
		particles[i] = a;
	}
	
	memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
	while (keep_window_open)
	{
		//sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
		memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
		for (int i = 0; i < particlecount; ++i)
		{
			particles[i].updateParticle(f.getU(Index(particles[i].returnX(), particles[i].returnY())), f.getV(Index(particles[i].returnX(), particles[i].returnY())));
			pixels[Index(particles[i].returnX(), particles[i].returnY())] = SDL_MapRGB(window_surface->format, 254, 254, 254);
		}
		for (int i = 0; i < SIM_SIZE * SIM_SIZE; ++i)
		{
			pixels[i] = f.getV(i) * 255;
		}
		f.stepVelocity();
		f.addVat(50000, 1000, 1000);
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