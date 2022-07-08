#include "Fluid.h"
#include <iostream>
#define SIM_SIZE 300
Fluid::Fluid(float visc,float diff)
{
	int dt = 1;
	float viscosity = visc;
	float diffusion = diff;

	
}
void Fluid::setFlowFields()
{
	for (int i = 0; i < SIM_SIZE * SIM_SIZE; ++i)
	{

		uold[i] = velocityu[i] = (float)(rand() % 21 + (-10)/40);
		vold[i] = velocityv[i] = (float)(rand() % 21 + (-10)/40);
	};
}
int Fluid::Index(int x, int y)
{
	return y * SIM_SIZE + x;
}
void Fluid::linearSolve(float x[],float x0[],float a,float c)
{	
	float inverseC = 1.0 / c;
	for (int k = 0; k < 2; k++) {
		for (int i = 1; i < SIM_SIZE - 1; i++) {
			for (int j = 1; j < SIM_SIZE - 1; j++) {
					x[Index(i, j)] =
						(x0[Index(i, j)]
							+ a * (x[Index(i + 1, j)]
								+ x[Index(i - 1, j)]
								+ x[Index(i, j + 1)]
								+ x[Index(i, j - 1)]
								)) * inverseC;
					
				}
			}
		}
}
void Fluid::diffuse(static float x[], static float x0[], float diffusion)
{
	float a = dt * diffusion * SIM_SIZE - 2 * SIM_SIZE - 2;

	//x is new iteration x0 is previous iteration
	linearSolve(x, x0, a, 1 + 4 * a);
}
void Fluid::project(float velocX[], float velocY[],  float* p, float* div, int iter)
{
    int N = SIM_SIZE;
    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                div[Index(i, j)] = -0.5f * (
                    velocX[Index(i + 1, j)]
                    - velocX[Index(i - 1, j)]
                    + velocY[Index(i, j + 1)]
                    - velocY[Index(i, j - 1)]
                    ) / N;
                p[Index(i, j)] = 0;
            }
        }
    }
    linearSolve(p,div, 1, 6);


        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                velocX[Index(i, j)] -= 0.5f * (p[Index(i + 1, j)]
                    - p[Index(i - 1, j)]) * N;
                velocY[Index(i, j)] -= 0.5f * (p[Index(i, j + 1)]
                    - p[Index(i, j - 1)]) * N;
            }
        }
    
}
void Fluid::advect(float d[], float d0[], float velocX[], float velocY[], float dt)
{
	int N = SIM_SIZE;
    float i0, i1, j0, j1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);
    float dtz = dt * (N - 2);

    float s0, s1, t0, t1, u0, u1;
    float tmp1, tmp2, tmp3, x, y;

    float Nfloat = N;
    float ifloat, jfloat;
    int i, j;

        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                tmp1 = dtx * velocX[Index(i, j)];
                tmp2 = dty * velocY[Index(i, j)];
                x = ifloat - tmp1;
                y = jfloat - tmp2;

                if (x < 0.5f) x = 0.5f;
                if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
                i0 = floorf(x);
                i1 = i0 + 1.0f;
                if (y < 0.5f) y = 0.5f;
                if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
                j0 = floorf(y);
                j1 = j0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;



                int i0i = i0;
                int i1i = i1;
                int j0i = j0;
                int j1i = j1;

                d[Index(i, j)] =

                    s0 * (t0 * ( d0[Index(i0i, j0i)]
                        +   d0[Index(i0i, j0i)])
                        + (t1 * ( d0[Index(i0i, j1i)]
                            +   d0[Index(i0i, j1i)])))
                    + s1 * (t0 * ( d0[Index(i1i, j0i)]
                        +   d0[Index(i1i, j0i)])
                        + (t1 * ( d0[Index(i1i, j1i)]
                            +   d0[Index(i1i, j1i)])));
            }
        }
    
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
	diffuse(Fluid::velocityv, Fluid::vold, viscosity);

    project(Fluid::uold, vold, velocityu, velocityv, 4);
    advect( Fluid::velocityu, Fluid::uold, Fluid::uold, Fluid::vold, dt);
    advect( Fluid::velocityv, Fluid::vold, Fluid::uold, Fluid::vold, dt);
    project(Fluid::velocityu, velocityv, uold, vold, 4);
    std::cout << "a";
}
float Fluid::getU(int index)
{
	return velocityu[index];
}
float Fluid::getV(int index)
{
	return velocityv[index];
}
void Fluid::addVat(int index, float u, float v)
{
    Fluid::velocityu[index] = u;
    Fluid::velocityv[index] = v;
}