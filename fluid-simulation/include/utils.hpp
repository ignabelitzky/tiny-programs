#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <cstdlib>
#include <omp.h>

struct Fluid
{
    int size;
    float dt;
    float diff;
    float visc;

    float *s;
    float *density;

    float *Vx;
    float *Vy;

    float *Vx0;
    float *Vy0;
};

typedef struct Fluid Fluid;

int IX(int i, int j, int N);
Fluid *create_fluid(int size, float dt, float diffusion, float viscosity);
void free_fluid(Fluid *fluid);
void add_density(Fluid *fluid, int x, int y, float amount);
void add_velocity(Fluid *fluid, int x, int y, float amountX, float amountY);
void step(Fluid *fluid, int N);

#endif