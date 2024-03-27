#include "../include/utils.hpp"

int IX(int i, int j, int N)
{
    return i + j * N;
}

Fluid *create_fluid(int size, float diffusion, float viscosity, float dt)
{
    Fluid *fluid = (Fluid *)malloc(sizeof(Fluid));
    fluid->size = size;
    fluid->dt = dt;
    fluid->diff = diffusion;
    fluid->visc = viscosity;

    fluid->s = (float *)calloc(size * size, sizeof(float));
    fluid->density = (float *)calloc(size * size, sizeof(float));

    fluid->Vx = (float *)calloc(size * size, sizeof(float));
    fluid->Vy = (float *)calloc(size * size, sizeof(float));

    fluid->Vx0 = (float *)calloc(size * size, sizeof(float));
    fluid->Vy0 = (float *)calloc(size * size, sizeof(float));

    return fluid;
}

void free_fluid(Fluid *fluid)
{
    free(fluid->s);
    free(fluid->density);
    free(fluid->Vx);
    free(fluid->Vy);
    free(fluid->Vx0);
    free(fluid->Vy0);
    free(fluid);
}

void add_density(Fluid *fluid, int x, int y, float amount)
{
    int index = IX(x, y, fluid->size);
    fluid->density[index] += amount;
}

void add_velocity(Fluid *fluid, int x, int y, float amountX, float amountY)
{
    int index = IX(x, y, fluid->size);
    fluid->Vx[index] += amountX;
    fluid->Vy[index] += amountY;
}

static void set_bnd(int b, float *x, int N)
{
    for (int i = 1; i < N - 1; i++)
    {
        x[IX(i, 0, N)] = b == 2 ? -x[IX(i, 1, N)] : x[IX(i, 1, N)];
        x[IX(i, N - 1, N)] = b == 2 ? -x[IX(i, N - 2, N)] : x[IX(i, N - 2, N)];
    }
    for (int j = 1; j < N - 1; j++)
    {
        x[IX(0, j, N)] = b == 1 ? -x[IX(1, j, N)] : x[IX(1, j, N)];
        x[IX(N - 1, j, N)] = b == 1 ? -x[IX(N - 2, j, N)] : x[IX(N - 2, j, N)];
    }

    x[IX(0, 0, N)] = 0.5 * (x[IX(1, 0, N)] + x[IX(0, 1, N)]);
    x[IX(0, N - 1, N)] = 0.5 * (x[IX(1, N - 1, N)] + x[IX(0, N - 2, N)]);
    x[IX(N - 1, 0, N)] = 0.5 * (x[IX(N - 2, 0, N)] + x[IX(N - 1, 1, N)]);
    x[IX(N - 1, N - 1, N)] = 0.5 * (x[IX(N - 2, N - 1, N)] + x[IX(N - 1, N - 2, N)]);
}

static void lin_solve(int b, float *x, float *x0, float a, float c, int iter, int N)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            for (int i = 1; i < N - 1; i++)
            {
                x[IX(i, j, N)] = (x0[IX(i, j, N)] + a * (x[IX(i + 1, j, N)] + x[IX(i - 1, j, N)] + x[IX(i, j + 1, N)] +
                                                         x[IX(i, j - 1, N)])) *
                                 cRecip;
            }
        }
        set_bnd(b, x, N);
    }
}

static void diffuse(int b, float *x, float *x0, float diff, float dt, int iter, int N)
{
    float a = dt * diff * (N - 2) * (N - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a, iter, N);
}

static void project(float *velocX, float *velocY, float *p, float *div, int iter, int N)
{
    for (int j = 1; j < N - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            div[IX(i, j, N)] = -0.5f *
                               (velocX[IX(i + 1, j, N)] - velocX[IX(i - 1, j, N)] + velocY[IX(i, j + 1, N)] -
                                velocY[IX(i, j - 1, N)]) /
                               N;
            p[IX(i, j, N)] = 0;
        }
    }
    set_bnd(0, div, N);
    set_bnd(0, p, N);
    lin_solve(0, p, div, 1, 6, iter, N);

    for (int j = 1; j < N - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            velocX[IX(i, j, N)] -= 0.5f * (p[IX(i + 1, j, N)] - p[IX(i - 1, j, N)]) * N;
            velocY[IX(i, j, N)] -= 0.5f * (p[IX(i, j + 1, N)] - p[IX(i, j - 1, N)]) * N;
        }
    }
    set_bnd(1, velocX, N);
    set_bnd(2, velocY, N);
}

static void advect(int b, float *d, float *d0, float *velocX, float *velocY, float dt, int N)
{
    float i0, i1, j0, j1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float Nfloat = N;
    float ifloat, jfloat;
    int i, j;

    for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++)
    {
        for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++)
        {
            tmp1 = dtx * velocX[IX(i, j, N)];
            tmp2 = dty * velocY[IX(i, j, N)];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if (x < 0.5f)
                x = 0.5f;
            if (x > Nfloat + 0.5f)
                x = Nfloat + 0.5f;
            i0 = floor(x);
            i1 = i0 + 1.0f;
            if (y < 0.5f)
                y = 0.5f;
            if (y > Nfloat + 0.5f)
                y = Nfloat + 0.5f;
            j0 = floor(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;

            d[IX(i, j, N)] = s0 * (t0 * d0[IX(i0i, j0i, N)] + t1 * d0[IX(i0i, j1i, N)]) +
                             s1 * (t0 * d0[IX(i1i, j0i, N)] + t1 * d0[IX(i1i, j1i, N)]);
        }
    }
    set_bnd(b, d, N);
}

void step(Fluid *fluid, int N)
{
    float visc = fluid->visc;
    float diff = fluid->diff;
    float dt = fluid->dt;
    float *Vx = fluid->Vx;
    float *Vy = fluid->Vy;
    float *Vx0 = fluid->Vx0;
    float *Vy0 = fluid->Vy0;
    float *s = fluid->s;
    float *density = fluid->density;

    diffuse(1, Vx0, Vx, visc, dt, 4, N);
    diffuse(2, Vy0, Vy, visc, dt, 4, N);

    project(Vx0, Vy0, Vx, Vy, 4, N);

    advect(1, Vx, Vx0, Vx0, Vy0, dt, N);
    advect(2, Vy, Vy0, Vx0, Vy0, dt, N);

    project(Vx, Vy, Vx0, Vy0, 4, N);

    diffuse(0, s, density, diff, dt, 4, N);
    advect(0, density, s, Vx, Vy, dt, N);
}
