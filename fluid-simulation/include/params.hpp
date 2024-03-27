#ifndef PARAMS_HPP
#define PARAMS_HPP

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

#endif