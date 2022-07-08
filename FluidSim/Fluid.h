#pragma once
#define SIM_SIZE 300
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
		void advect(float d[], float d0[], float velocX[], float velocY[], float dt);
		void linearSolve(float xarr[], float prevxarr[],float a, float c);
		void swapU(float x[],float x0[]);
		void swapV(float x[], float x0[]);
		float getU(int index);
		float getV(int index);
		int Index(int i, int j);
		void addVat(int, float, float);
		void project(float velocX[], float velocY[], float* p, float* div, int iter);
	};

