#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <float.h>

#define __USE_MINGW_ANSI_STDIO 1
#define g 9.87

struct body{
    double mass;
    double x;
    double y;
    double vx;
    double vy;
} body;


void RHS(struct body *y, struct body *dy, long double mu);

int main(int argc, char **argv)
{

    int tmax;
    double t = 0, dt, mu;
    struct body *one, *two, *three, *dy, *three_new;
    one = calloc(sizeof(double), 5);
    two = calloc(sizeof(double), 5);
    three = calloc(sizeof(double), 5);
    dy = calloc(sizeof(double), 5);
    three_new = calloc(sizeof(double), 5);


    sscanf(argv[1], "%lf", &one->mass);
    sscanf(argv[2], "%lf", &two->mass);
    sscanf(argv[3], "%d", &tmax);
    sscanf(argv[4], "%lf", &dt);

    mu = 0.012277471; //one->mass/((one->mass)+(two->mass));

    one->x = -mu;
    two->x = 1-mu;

    three->x = 1.2;
    three->vy = -1.049357510;



    FILE *output = fopen("resulteu.dat", "w");


    while(t < tmax)
    {
        fprintf(output, "%lf %lf %lf %lf %lf\n", t, three->x, three->y, three->vx, three->vy);

        if(t+dt > tmax) dt = tmax-t;
        RHS(three,dy,mu);
        three_new->x = three->x+dt*dy->x;
        three_new->y = three->y+dt*dy->y;
        three_new->vx = three->vx+dt*dy->vx;
        three_new->vy = three->vy+dt*dy->vy;

        three->x = three_new->x;
        three->y = three_new->y;
        three->vx = three_new->vx;
        three->vy = three_new->vy;

        t+=dt;
    }

    fclose(output);
    free(one);
    free(two);
    free(three);
    printf("GGWP\n");
    return 0;
}


void RHS(struct body *three, struct body *dy, long double mu)
{
    long double r1,r2;

    r1 = sqrtl(powl((three->x+mu),2)+powl(three->y,2));
    r2 = sqrtl(powl((three->x-(1-mu)),2)+powl(three->y,2));

    dy->x = three->vx;
    dy->y = three->vy;
    dy->vx = 2 * three->vy + three->x - (1-mu) * ((three->x+mu) / (powl(r1,3))) - mu * ((three->x - (1-mu)) / (powl(r2,3)));
    dy->vy = -2 * three->vx + three->y - three->y * ( (1-mu)/ powl(r1,3) + mu / powl(r2,3));

}


