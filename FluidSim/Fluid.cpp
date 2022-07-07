#include "Fluid.h"
#include <iostream>
#define SIM_SIZE 1000
Fluid::Fluid(float visc,float diff)
{
	int dt = 0.1;
	float viscosity = visc;
	float diffusion = diff;

	
}
void Fluid::setFlowFields()
{
	for (int i = 0; i < SIM_SIZE * SIM_SIZE; ++i)
	{

		velocityu[i] = (float)(rand() % 13 + (-6)) / 6;
		velocityv[i] = (float)(rand() % 13 + (-6)) / 6;
	};
}
void Fluid::linearSolve(float x[],float x0[],float a,float c)
{
	float inverseC = 1.0 / c;
}
void Fluid::diffuse(static float x[], static float x0[], float diffusion)
{
	float a = dt * diffusion * SIM_SIZE - 2 * SIM_SIZE - 2;

	//x is new iteration x0 is previous iteration
	linearSolve(x, x0, a, 1 + 4 * a);
}
void Fluid::advect()
{

}
void Fluid::swapU(static float *x, float *x0)
{
	static float tmp[SIM_SIZE * SIM_SIZE];
	//memcpy(x, tmp, sizeof(x));
	
}
void Fluid::swapV(float x[], float x0[])
{
	static float tmp[SIM_SIZE * SIM_SIZE];
}
void Fluid::stepVelocity()
{
	
	diffuse(Fluid::velocityu, Fluid::uold, viscosity);
	
}
float Fluid::getU(int index)
{
	std::cout << velocityu[index];
	return velocityu[index];
}
float Fluid::getV(int index)
{
	return velocityv[index];
}