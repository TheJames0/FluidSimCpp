#pragma once
#define SIM_SIZE 400
class Fluid
{

private:
	int n;
	float density[SIM_SIZE * SIM_SIZE];
	float velocityx[SIM_SIZE * SIM_SIZE];
	float velocityy[SIM_SIZE * SIM_SIZE];

public:
	inline Fluid();
	void velocitystep();
	void setVelocities();
};

