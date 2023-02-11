
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
#include"Simulator.h"
//#include"Fluid.h"
using std::this_thread::sleep_for;
#define SIM_SIZE 200


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
	Uint32 color;
public: 
	void updateParticle(float x,float y)
	{
		
		
		velocityx = x * 0.0001;
		velocityy = y * 0.0001;
	
		if (1 < cellx + velocityx + 1 && cellx + velocityx + 1 < SIM_SIZE - 1)
		{
			cellx += velocityx;
		}

		if (1 < celly + velocityy + 1 && celly + velocityy + 1 < SIM_SIZE - 1)
		{
			celly += velocityy;
		}

		
	}
	int returnX() { return cellx; }
	int returnY() { return celly; }
	float returnU() { return velocityx; }
	float returnV() { return velocityy; }
	void setX(int xval) { this->cellx = xval; }
	void setY(int yval) { this->celly = yval; }
	void setU(float uval) { this->velocityx = uval; }
	void setV(float vval) { this->velocityy = vval; }
	void setcolor(SDL_Surface* window_surface) { this->color = SDL_MapRGB(window_surface->format, rand() % 30, rand() % 30, rand() % 30); }
	Uint32 returncolor() { return this->color; }
	
};

int main(int argc, char* argv[])
{


	bool keep_window_open = true;
	//SDL2 (2D Renderer) Initialisation
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1000, 1000, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SIM_SIZE, SIM_SIZE);
	Uint32* pixels = new Uint32[SIM_SIZE * SIM_SIZE];
	//init flowfield arrays
	FluidCell* f = new FluidCell(0, 0, 0.0000001f);
	FluidSimulator* activeSimulator = new FluidSimulator(f, 16);

	SDL_Rect dest = { 0,  0,  1000,  1000 };
	

	



	//Initialize visualisation particles & set initial positions.
	const int particlecount = 50000;
	static Particle particles[particlecount] = {};
	for (int i = 0; i < particlecount; ++i)
	{
		Particle a;
		
		a.setX(rand() % SIM_SIZE);
		a.setY(rand() % SIM_SIZE);
		a.setU(Index(0,0));
		a.setV(Index(0,0));
		a.setcolor(window_surface);
		particles[i] = a;
	}

	activeSimulator->addVelocity(10, 99, 100000000, 5);
	activeSimulator->addVelocity(10, 100, 100000000, 0);
	activeSimulator->addVelocity(10, 101, 100000000, -5);
	activeSimulator->addVelocity(10, 99, 100000000, 5);
	activeSimulator->addVelocity(10, 100, 100000000, 0);
	activeSimulator->addVelocity(10, 101, 100000000, -5);
	activeSimulator->addVelocity(10, 4, 0, -99999999999);
	int count = 0;
	memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
	while (keep_window_open)
	{	
		sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
		memset(pixels, 10, SIM_SIZE * SIM_SIZE * sizeof(Uint32));
		
			
		

		
		count += 10;
		for (int i = 0; i < particlecount; ++i)
		{
			if (i < count && count - 10 < i)
			{
				particles[i].setX( rand() % SIZE);
				particles[i].setY( rand() % SIZE);

		}
			if (count == particlecount - 10)
				count = 0;

			particles[i].updateParticle(f->velocityX[Index(particles[i].returnX(),particles[i].returnY())], f->velocityY[Index(particles[i].returnX(), particles[i].returnY())]);
			float mag = std::abs(((particles[i].returnU() + particles[i].returnV())) * 500);
			pixels[Index(particles[i].returnX(), particles[i].returnY())] = particles->returncolor() + mag;
			//if(std::abs(particles[i].returnU()) > 0.01 && std::abs(particles[i].returnV()) > 0.01)
			//pixels[Index(particles[i].returnX(), particles[i].returnY())] = 250;
		}

		//activeSimulator->addDye(50, 50, 100000);
		
		activeSimulator->step();
		
		SDL_UpdateWindowSurface(window);
		//Texture Update
		SDL_UpdateTexture(texture, NULL, pixels, SIM_SIZE * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dest);
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