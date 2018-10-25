#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>

#define g 9.87

struct coord{
    double phi;
    double omega;
} coord;

void RHS(double t, double l, struct coord *y, struct coord *dy);

int main(int argc, char **argv)
{

    int tmax;
    double t = 0, dt, l;
    struct coord *y, *dy, *ynew;
    y = calloc(sizeof(double), 2);
    dy = calloc(sizeof(double), 2);
    ynew = calloc(sizeof(double),2);
    y->omega = 0.5;
    y->phi = 0;
    dy->omega = 0;
    dy->phi = 0;

    sscanf(argv[1], "%d", &tmax);
    sscanf(argv[2], "%lf", &dt);
    sscanf(argv[3], "%lf", &l);

    FILE *output = fopen("pend.dat", "w");


    while(t < tmax)
    {
        fprintf(output, " %lf %lf %lf\n", t, y->phi, y->omega);

        if(t+dt > tmax) dt = tmax-t;
        RHS(t,l,y,dy);
        ynew->phi = y->phi+dt*dy->phi;
        ynew->omega = y->omega+dt*dy->omega;

        y->phi = ynew->phi;
        y->omega = ynew->omega;

        t+=dt;
    }

    fclose(output);
    free(ynew);
    free(y);
    free(dy);
    printf("GGWP\n");
    return 0;
}


void RHS(double t, double l, struct coord *y, struct coord *dy)
{
    dy->phi = y->omega;
    dy->omega = -g/l*(sin(y->phi));
}

