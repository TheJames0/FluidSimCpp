
#include <iostream>
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
int main(int argc, char* argv[])
{
	//init flowfield arrays
	FluidCell* f = new FluidCell(0, 0, 0.0000001f);
	FluidSimulator* activeSimulator = new FluidSimulator(f, 16);


	activeSimulator->addVelocity(10, 99, 100000000, 5);
	activeSimulator->addVelocity(10, 100, 100000000, 0);
	activeSimulator->addVelocity(10, 101, 100000000, -5);
	activeSimulator->addVelocity(10, 99, 100000000, 5);
	activeSimulator->addVelocity(10, 100, 100000000, 0);
	activeSimulator->addVelocity(10, 101, 100000000, -5);
	activeSimulator->addVelocity(10, 4, 0, -99999999999);

	int frame_count = 10;

	for (int i = 0; i < frame_count; i++)
	{	
		activeSimulator->addDye(50, 50, 100000);
		
		activeSimulator->step();
			
		}

		
	}
	
	return 0;
}