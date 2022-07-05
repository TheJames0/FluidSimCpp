#include "Fluid.h"

Fluid::Fluid()
{
	velocityx[SIM_SIZE * SIM_SIZE] = { 0 };
	velocityy[SIM_SIZE * SIM_SIZE] = { 0 };
}