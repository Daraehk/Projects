#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct body{
    long double x;
    long double y;
    long double vx;
    long double vy;
} body;


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

int main()
{

    FILE* result = fopen("result.dat", "w");
    FILE* data = fopen("data.dat", "w");

    struct body *three, *ynew, *yhat, *k1, *k2, *k3, *dy2, *dy3, *scale;

    three = calloc(sizeof(long double), 5);
    ynew = calloc(sizeof(long double), 5);
    yhat = calloc(sizeof(long double), 5);
    k1 = calloc(sizeof(long double), 5);
    k2 = calloc(sizeof(long double), 5);
    k3 = calloc(sizeof(long double), 5);
    dy2 = calloc(sizeof(long double), 5);
    dy3 = calloc(sizeof(long double), 5);
    scale = calloc(sizeof(long double), 5);


    three->x = 0.994;
    three->vy = -2.00158510637908252240537862224;

    long double mu = 0.012277471;

    long double t = 0.0;
    long double tmax = 20.0;
    long double TOL = 0.00001;
    long double dt = 0.1;
    long double ERR = 0.0;
    long double opt = 0.0;
    long double sum = 0.0;


    while(t < tmax)
    {

      do
      {

        RHS(three, k1, mu);

        dy2->x = three->x + dt/3.0*k1->x;
        dy2->y = three->y + dt/3.0*k1->y;
        dy2->vx = three->vx + dt/3.0*k1->vx;
        dy2->vy = three->vy+ dt/3.0*k1->vy;

        RHS(dy2, k2, mu);

        dy3->x = three->x + dt*2.0/3.0*k2->x;
        dy3->y = three->y + dt*2.0/3.0*k2->y;
        dy3->vx = three->vx + dt*2.0/3.0*k2->vx;
        dy3->vy = three->vy + dt*2.0/3.0*k2->vy;


        RHS(dy3, k3, mu);

        ynew->x = three->x + dt*(1.0/4.0*k1->x + 3.0/4.0*k3->x);
        ynew->y = three->y + dt*(1.0/4.0*k1->y + 3.0/4.0*k3->y);
        ynew->vx = three->vx + dt*(1.0/4.0*k1->vx + 3.0/4.0*k3->vx);
        ynew->vy = three->vy + dt*(1.0/4.0*k1->vy + 3.0/4.0*k3->vy);

        yhat->x = three->x + dt*(5.0/6.0*k1->x + 1.0/6.0*k2->x);
        yhat->y = three->y + dt*(5.0/6.0*k1->y + 1.0/6.0*k2->y);
        yhat->vx = three->vx + dt*(5.0/6.0*k1->vx + 1.0/6.0*k2->vx);
        yhat->vy = three->vy + dt*(5.0/6.0*k1->vy + 1.0/6.0*k2->vy);

        scale->x = fmax(fabs(ynew->x),fabs(yhat->x))*TOL;
        scale->y = fmax(fabs(ynew->y),fabs(yhat->y))*TOL;
        scale->vx = fmax(fabs(ynew->vx),fabs(yhat->vx))*TOL;
        scale->vy = fmax(fabs(ynew->vy),fabs(yhat->vy))*TOL;

        sum = 0.0;


        sum += pow(((yhat->x - ynew->x)/scale->x), 2);
        sum += pow(((yhat->y - ynew->y)/scale->y), 2);
        sum += pow(((yhat->vx - ynew->vx)/scale->vx), 2);
        sum += pow(((yhat->vy - ynew->vy)/scale->vy), 2);
        //printf("%lf \t %lf \n", (double)sum, (double)scale->omega);

        ERR = sqrt(sum/(2.0));

        opt = 0.8*dt*pow(ERR,-1.0/3.0);
        dt = opt;
        fprintf(data, "%lf %lf %lf %lf\n", (double)sum, (double)ERR, (double)opt, (double)t);

      }
      while(ERR > 1);

       /* while(y->phi > M_PI) y->phi = y->phi - 2.0*M_PI;
        while(y->phi < -1.0*M_PI) y->phi = y->phi+ 2.0*M_PI;*/

        three->x = ynew->x;
        three->y = ynew->y;
        three->vx = ynew->vx;
        three->vy = ynew->vy;

        fprintf(result, "%lf %lf %lf %lf %lf\n", (double)t, (double)three->x, (double)three->y, (double)three->vx, (double)three->vy);

        t = t + dt;
       if(t + dt > tmax) dt = tmax-t;

      }


    fclose(result);
    fclose(data);
    return 0;
}
