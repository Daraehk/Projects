#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <float.h>


struct body{
    double mass;
    long double x;
    long double y;
    long double vx;
    long double vy;
} body;


void RHS(struct body *y, struct body *dy, long double mu);

int main(int argc, char **argv)
{

    int tmax;
    double t = 0, dt;
    long double mu;
    struct body *one, *two, *three, *dy, *three_new, *k1;
    one = calloc(sizeof(long double), 5);
    two = calloc(sizeof(long double), 5);
    three = calloc(sizeof(long double), 5);
    dy = calloc(sizeof(long double), 5);
    three_new = calloc(sizeof(long double), 5);
    k1 = calloc(sizeof(long double), 5);


    sscanf(argv[1], "%lf", &one->mass);
    sscanf(argv[2], "%lf", &two->mass);
    sscanf(argv[3], "%d", &tmax);
    sscanf(argv[4], "%lf", &dt);

    mu = one->mass/((one->mass)+(two->mass));

    one->x = -mu;
    two->x = 1-mu;

    three->x = 1.0;
    three->vy = -1.0;



    FILE *output = fopen("result.dat", "w");


    while(t < tmax)
    {
        fprintf(output, "%lf %lf %lf %lf %lf\n", t, (double)three->x, (double)three->y, (double)three->vx, (double)three->vy);

        if(t+dt > tmax) dt = tmax-t;

        RHS(three, dy, mu);

        k1->x = three->x + dt/2*dy->x;
        k1->y = three->y + dt/2*dy->y;
        k1->vx = three->vx + dt/2*dy->vx;
        k1->vy = three->vy + dt/2*dy->vy;


        RHS(k1, dy, mu);

        three_new->x = three->x + dt * dy->x;
        three_new->y = three->y + dt * dy->y;
        three_new->vx = three->vx + dt * dy->vx;
        three_new->vy = three->vy + dt * dy->vy;

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


