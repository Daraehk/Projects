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
    struct coord *y, *dy, *ynew, *k1, *k2, *temp;
    y = calloc(sizeof(double), 2);
    dy = calloc(sizeof(double), 2);
    k1 = calloc(sizeof(double), 2);
    k2 = calloc(sizeof(double), 2);
    ynew = calloc(sizeof(double), 2);
    temp = calloc(sizeof(double), 2);
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
        k1->phi = dy->phi;
        k1->omega = dy->omega;

        temp->phi = y->phi+dt/2*dy->phi;
        temp->omega = y->omega+dt/2*dy->omega;

        RHS(t,l,temp,dy);

        k2->phi = dy->phi;
        k2->omega = dy->omega;

        ynew->phi = y->phi + dt*dy->phi;
        ynew->omega = y->omega + dt*dy->omega;

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

