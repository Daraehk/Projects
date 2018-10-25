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
    long int k = 0;
    long double mu;
    struct body *one, *two, *three, *dy, *three_new, *k1, *k2, *k3, *k4, *temp;
    one = calloc(sizeof(long double), 5);
    two = calloc(sizeof(long double), 5);
    three = calloc(sizeof(long double), 5);
    dy = calloc(sizeof(long double), 5);
    three_new = calloc(sizeof(long double), 5);
    k1 = calloc(sizeof(long double), 5);
    k2 = calloc(sizeof(long double), 5);
    k3 = calloc(sizeof(long double), 5);
    k4 = calloc(sizeof(long double), 5);
    temp = calloc(sizeof(long double), 5);



    sscanf(argv[1], "%lf", &one->mass);
    sscanf(argv[2], "%lf", &two->mass);
    sscanf(argv[3], "%d", &tmax);
    sscanf(argv[4], "%lf", &dt);

    mu = 0.012277471;//(long double)one->mass/((one->mass)+(two->mass));

    one->x = -mu;
    two->x = 1-mu;

    three->x = 0.994;
    three->vy = -2.00158510637908252240537862224;



    FILE *output = fopen("result2.dat", "w");


    while(t < tmax)
    {
        fprintf(output, "%lf %lf %lf %lf %lf\n", t, (double)three->x, (double)three->y, (double)three->vx, (double)three->vy);

        if(t+dt > tmax) dt = tmax-t;

        //************ k1
        RHS(three, dy, mu);

        k1->x = dy->x;
        k1->y = dy->y;
        k1->vx = dy->vx;
        k1->vy = dy->vy;

        temp->x = three->x + dt/2*dy->x;
        temp->y = three->y + dt/2*dy->y;
        temp->vx = three->vx + dt/2*dy->vx;
        temp->vy = three->vy + dt/2*dy->vy;

        //************ k2

        RHS(temp, dy, mu);

        k2->x = dy->x;
        k2->y = dy->y;
        k2->vx = dy->vx;
        k2->vy = dy->vy;

        temp->x = three->x + dt/2*dy->x;
        temp->y = three->y + dt/2*dy->y;
        temp->vx = three->vx + dt/2*dy->vx;
        temp->vy = three->vy + dt/2*dy->vy;

        //************ k3

        RHS(temp, dy, mu);

        k3->x = dy->x;
        k3->y = dy->y;
        k3->vx = dy->vx;
        k3->vy = dy->vy;

        temp->x = three->x + dt*dy->x;
        temp->y = three->y + dt*dy->y;
        temp->vx = three->vx + dt*dy->vx;
        temp->vy = three->vy + dt*dy->vy;

        //************ k4

        RHS(temp, dy, mu);

        k4->x = dy->x;
        k4->y = dy->y;
        k4->vx = dy->vx;
        k4->vy = dy->vy;

        //*********** y_n+1

        three_new->x = three->x + dt/6*(k1->x + 2*k2->x + 2*k3->x + k4->x );
        three_new->y = three->y + dt/6*(k1->y + 2*k2->y + 2*k3->y + k4->y );
        three_new->vx = three->vx + dt/6*(k1->vx + 2*k2->vx + 2*k3->vx + k4->vx );
        three_new->vy = three->vy + dt/6*(k1->vy + 2*k2->vy + 2*k3->vy + k4->vy );

        three->x = three_new->x;
        three->y = three_new->y;
        three->vx = three_new->vx;
        three->vy = three_new->vy;

        k++;
        if(k%5000==0) printf(".");
        if(k%100000==0) printf("\n");
        t+=dt;
    }

    fclose(output);
    free(one);
    free(two);
    free(three);
    free(three_new);
    free(temp);
    free(k1);
    free(k2);
    free(k3);
    free(k4);
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

