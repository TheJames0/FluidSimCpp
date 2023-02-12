
#include <iostream>
#include <tuple>
#include <string>
#include<time.h>
#include<math.h>
#include<random>
#include<thread>
#include"Fluid.h"
#include"Simulator.h"
#include<fstream>
#include<cmath>
#include<cstdint>
//#include"Fluid.h"
using std::this_thread::sleep_for;
#define SIM_SIZE 200


constexpr int TIME_TO_SLEEP = 1;
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1

		
void save_image(const ::std::string& name, float img_vals[SIM_SIZE*SIM_SIZE])
{
	using ::std::string;
	using ::std::ios;
	using ::std::ofstream;
	typedef unsigned char pixval_t;
	auto float_to_pixval = [](float img_val) -> pixval_t {
		int tmpval = static_cast<int>(::std::floor(123 * img_val));
		if (tmpval < 0) {
			return 0u;
		}
		else if (tmpval > 255) {
			return 255u;
		}
		else {
			return tmpval & 0xffu;
		}
	};
	auto as_pgm = [](const string& name) -> string {
		if (!((name.length() >= 4)
			&& (name.substr(name.length() - 4, 4) == ".pgm")))
		{
			return name + ".pgm";
		}
		else {
			return name;
		}
	};

	ofstream out(as_pgm(name), ios::binary | ios::out | ios::trunc);

	out << "P5\n200 200\n255\n";
	for (int x = 0; x < SIM_SIZE*SIM_SIZE; ++x) {
		
			const pixval_t pixval = float_to_pixval(img_vals[x]);
			const char outpv = static_cast<const char>(pixval);
			out.write(&outpv, 1);
		
	}
}
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
	FluidCell* f = new FluidCell(0.00001, 0, 0.00001f);
	FluidSimulator* activeSimulator = new FluidSimulator(f, 16);



	activeSimulator->addDye(21, 21, 10000);
	int frame_count = 60;

	for (int i = 0; i < frame_count; i++)
	{	
		activeSimulator->addVelocity(20, 20, 1000, 1000);
		
		activeSimulator->step();
		std::string name = std::to_string(i);
		save_image(name, f->density);
	}

	return 0;
	}