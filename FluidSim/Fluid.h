#pragma once
#define SIM_SIZE 1000
class Fluid
{
	private:
		//Diffusion variables
		int dt; //timestep
		float diffusion;
		float viscosity; //liquidthickness

		//Velocity horizontal
		static float velocityu[SIM_SIZE * SIM_SIZE];
		//Velocity vertical
		static float velocityv[SIM_SIZE * SIM_SIZE];

		//Previous velocity horizontal
		static float uold[SIM_SIZE * SIM_SIZE];
		//Velocity velocity vertical
		static float vold[SIM_SIZE * SIM_SIZE];
		




	public:
		Fluid(float viscosity,float diffusion);
		void setFlowFields();
		void stepVelocity();
		void diffuse(float [], float [],float );
		void advect();
		void linearSolve(float xarr[], float prevxarr[],float a, float c);
		void swapU(float x[],float x0[]);
		void swapV(float x[], float x0[]);
		float getU(int index);
		float getV(int index);
	};

