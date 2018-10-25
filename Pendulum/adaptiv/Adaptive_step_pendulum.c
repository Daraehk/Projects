#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define g 9.81
#define l 1

struct coord{
    long double phi;
    long double omega;
} coord;


void RHS(struct coord *y, struct coord *dy)
{
    dy->phi = y->omega;
    dy->omega = -g/l*(sin(y->phi));
}

int main()
{

    FILE* result = fopen("pend.dat", "w");
    FILE* data = fopen("data.dat", "w");

    struct coord *y, *ynew, *yhat, *k1, *k2, *k3, *dy2, *dy3, *scale;

    y = calloc(sizeof(long double), 2);
    ynew = calloc(sizeof(long double),2);
    yhat = calloc(sizeof(long double),2);
    y->omega = 0.5;
    k1 = calloc(sizeof(long double), 2);
    k2 = calloc(sizeof(long double), 2);
    k3 = calloc(sizeof(long double), 2);
    dy2 = calloc(sizeof(long double), 2);
    dy3 = calloc(sizeof(long double), 2);
    scale = calloc(sizeof(long double), 2);

    long double t = 0.0;
    long double tmax = 1000.0;
    long double TOL = 0.00001;
    long double dt = 0.1;
    long double ERR = 0.0;
    long double opt = 0.0;
    long double sum = 0.0;


    while(t < tmax)
    {

      do
      {

        RHS(y, k1);

        dy2->phi = y->phi + dt/3.0*k1->phi;
        dy2->omega = y->omega + dt/3.0*k1->omega;


        RHS(dy2, k2);

        dy3->phi = y->phi + dt*2.0/3.0*k2->phi;
        dy3->omega = y->omega + dt*2.0/3.0*k2->omega;


        RHS(dy3, k3);

        ynew->phi = y->phi + dt*(1.0/4.0*k1->phi + 3.0/4.0*k3->phi);
        ynew->omega = y->omega + dt*(1.0/4.0*k1->omega + 3.0/4.0*k3->omega);

        yhat->phi = y->phi + dt*(5.0/6.0*k1->phi + 1.0/6.0*k2->phi);
        yhat->omega = y->omega + dt*(5.0/6.0*k1->omega + 1.0/6.0*k2->omega);

        scale->phi = fmax(fabs(ynew->phi),fabs(yhat->phi))*TOL;
        scale->omega = fmax(fabs(ynew->omega),fabs(yhat->omega))*TOL;

        sum = 0.0;


        sum += pow(((yhat->phi - ynew->phi)/scale->phi), 2);
        sum += pow(((yhat->omega - ynew->omega)/scale->omega),2);
        //printf("%lf \t %lf \n", (double)sum, (double)scale->omega);

        ERR = sqrt(sum/(2.0));

        opt = 0.8*dt*pow(ERR,-1.0/3.0);
        dt = opt;
        fprintf(data, "%lf %lf %lf %lf\n", (double)sum, (double)ERR, (double)opt, (double)t);

      }
      while(ERR > 1);

        while(y->phi > M_PI) y->phi = y->phi - 2.0*M_PI;
        while(y->phi < -1.0*M_PI) y->phi = y->phi+ 2.0*M_PI;

        y->phi = ynew->phi;
        y->omega = ynew->omega;

        fprintf(result, "%lf %lf %lf\n", (double)t, (double)y->phi, (double)y->omega);

        t = t + dt;
       if(t + dt > tmax) dt = tmax-t;

      }


    fclose(result);
    fclose(data);
    return 0;
}
