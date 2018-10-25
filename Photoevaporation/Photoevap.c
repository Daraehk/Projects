
#include "fargo.h"


void Parabola(int i1,int i2,int i3,double *a,double *b,double *c, double rmin, double dr, double *u);
double Func_nu(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR);
double Func_A(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR);
double Func_B(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR);
double Norm (int imax, double rmin, double dr, double M_STAR, double L_X, double a_1, double b_1, double c_1, double d_1, double e_1, double f_1, double g_1);
double Func_C( double r, double norm, double M_STAR, double a_1, double b_1, double c_1, double d_1, double e_1, double f_1, double g_1);
void Perem(double rmin, double dr, int imax, double *u);
void Kezdeti(double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR, double M_DISK, double R_S, int imax, double rmin, double dr , double *u);
double Disk_mass(PolarGrid *Rho);


void Foto_evap(PolarGrid *Rho, real dt, real Asp_Ratio, real ALPHA ){

double k_gauss = 0.01720209895;
double SDCONV = 1.12521e-7;	//M_solar/AU^2 -> g/cm^2
double AU2CM = 1.496e13;	 //AU -> cm
double SDEXP = -1.0;
double dr = (RMAX-RMIN)/(Rho->Nrad-1);
double rmin = RMIN;
double R_S = RMAX;
int imax = Rho->Nrad;

double *u, *u_old;//[imax+2];
u = (double*) malloc((imax+2)*sizeof(double));
u_old = (double*) malloc((imax+2)*sizeof(double));

double M_DISK = Disk_mass(Rho);
double M_STAR = 1.0;


const double a_1 = 0.15138;
const double a_2 = -0.438226;
const double b_1 = -1.2182;
const double b_2 = -0.10658387;
const double c_1 = 3.4046;
const double c_2 = 0.5699464;
const double d_1 = -3.5717;
const double d_2 = 0.010732277;
const double e_1 = -0.32762;
const double e_2 = -0.131809597;
const double f_1 = 3.6064;
const double f_2 = -1.32285709;
const double g_1 = -2.4918;

double t = 0.0;
  Kezdeti(ALPHA, Asp_Ratio, k_gauss, M_STAR, M_DISK, R_S, imax, rmin ,dr ,u);

    double n;
    n = Norm(imax, rmin, dr, M_STAR, 1, a_1,  b_1,  c_1,  d_1,  e_1,  f_1, g_1);
    int i;
    for (i = 0; i <= imax+1 ; i++) u_old[i] = u[i];

    double r;
	for(i = 1 ; i <= imax ; i++)
	{
		r = rmin + (i-1)*dr;

		u[i] = u_old[i] + dt*(Func_A(r, ALPHA, Asp_Ratio, k_gauss, M_STAR)*(u_old[i+1]-2*u_old[i]+u_old[i-1])/(dr*dr) + Func_B(r, ALPHA, Asp_Ratio, k_gauss, M_STAR)*(u_old[i+1]-u_old[i-1])/(2.0*dr)) - Func_nu(r, ALPHA, Asp_Ratio, k_gauss, M_STAR)*Func_C(r, n, M_STAR, a_1,  b_1,  c_1,  d_1,  e_1,  f_1, g_1);
	}


}

double Disk_mass(PolarGrid *Rho ){

double M_DISK = 0;

int nr = Rho->Nrad;
int ns = Rho->Nsec;
real *Field = Rho->Field;

int i = 0;
for(;i < nr*ns; i++) M_DISK += Field[i];

return M_DISK;
}

void Parabola(int i1,int i2,int i3,double *a,double *b,double *c, double rmin, double dr, double *u)
{
 double x1,x2,x3,y1,y2,y3;
 double av,bv,cv;

 x1 = rmin + (i1-1)*dr;
 x2 = rmin + (i2-1)*dr;
 x3 = rmin + (i3-1)*dr;

 y1 = u[i1];
 y2 = u[i2];
 y3 = u[i3];

 av = ((y1-y3)/(x1-x3) - (y1-y2)/(x1-x2)) / (x3-x2);
 bv = (y1-y2) / (x1-x2) - av*(x1+x2);
 cv = y1-av*x1*x1-bv*x1;

 *a = av;
 *b = bv;
 *c = cv;
}

/* Kinematical viscosity */
double Func_nu(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR)
{

   double nu_r = ALPHA * Asp_Ratio * Asp_Ratio * k_gauss * sqrt( r ) * sqrt(M_STAR);
   //printf("nu_r: %lf\n", nu_r);
   return nu_r;
}

double Func_A(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR)
{
 return(3.0*Func_nu(r, ALPHA, Asp_Ratio, k_gauss, M_STAR));
}


double Func_B(double r, double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR)
{
 return(9.0*Func_nu(r, ALPHA, Asp_Ratio, k_gauss, M_STAR)/(2.0*r));
}

double Norm (int imax, double rmin, double dr, double M_STAR, double L_X, double a_1, double b_1, double c_1, double d_1, double e_1, double f_1, double g_1)
{
  double c = 0.0;
  int i = 0;
  double sum = 0.0;
  double norm = 0.0;

  for(i = 0; i <= imax; i++ )
  {
      double x = 0.85*(rmin + (i-1)*dr)/M_STAR;

       if(x > 0.7)
        {
        c = pow(10, a_1 * pow(log10(x), 6) + b_1 * pow(log10(x), 5) + c_1 * pow(log10(x), 4))

            * pow(10 , d_1 * pow(log10(x), 3) + e_1 * pow(log10(x), 2)+ f_1 * log10(x)) * pow (10, g_1)

            * ( 6*a_1*pow(log(x),5)/(x*x*pow(log(10),7))  + 5*b_1*pow(log(x),4)/(x*x*pow(log(10),6)) + 4*c_1*pow(log(x),3)/(x*x*pow(log(10),5))

            + 3*d_1*pow(log(x),2)/(x*x*pow(log(10),4)) + 2*e_1*log(x)/(x*x*pow(log(10),3)) +  f_1/(x*x*pow(log(10),2)))

            * exp((-1)*pow(x/100,10)) ;
        }
        else
        {
            c = 0.0;
        }

      sum += 2*3.14159265359*(rmin + (i-1)*dr)*c*dr;
  }

    norm = sum/(6.25*pow(10,-9)*pow(M_STAR,-0.068)*pow(L_X, 1.14));

    return norm;
}

double Func_C( double r, double norm, double M_STAR, double a_1, double b_1, double c_1, double d_1, double e_1, double f_1, double g_1)
{
  double c = 0.0;

  double x = 0.85*r/M_STAR;


 if(x > 0.7)
 {
    c = pow(10, a_1 * pow(log10(x), 6) + b_1 * pow(log10(x), 5) + c_1 * pow(log10(x), 4))

    * pow(10 , d_1 * pow(log10(x), 3) + e_1 * pow(log10(x), 2)+ f_1 * log10(x)) * pow (10, g_1)

    * ( 6*a_1*pow(log(x),5)/(x*x*pow(log(10),7))  + 5*b_1*pow(log(x),4)/(x*x*pow(log(10),6)) + 4*c_1*pow(log(x),3)/(x*x*pow(log(10),5))

       + 3*d_1*pow(log(x),2)/(x*x*pow(log(10),4)) + 2*e_1*log(x)/(x*x*pow(log(10),3)) +  f_1/(x*x*pow(log(10),2)))

       * exp((-1)*pow(x/100,10)) ;
 }
 else
 {
     c = 0.0;
 }

 return(c/norm);
}

/* * * * * * * * * * * * * * * * * * * * * */

/* Boundary condition */
void Perem(double rmin, double dr, int imax, double *u)
{
 double a,b,c;

 Parabola(1,2,3,&a,&b,&c, rmin, dr, u);
 u[0] = a *(rmin-dr)*(rmin-dr) + b*(rmin-dr) + c;


 u[imax+1] = 0.0;

}

/* * * * * * * * * * * * * * * * * * * * * */

/* Initial Condition */
void Kezdeti(double ALPHA, double Asp_Ratio, double k_gauss, double M_STAR, double M_DISK, double R_S,
             int imax, double rmin, double dr, double *u )
{
 int i;
 double r;


 for(i = 1 ; i <= imax ; i++)
 {
  r = rmin + (i-1)*dr;

  u[i] = Func_nu(r, ALPHA, Asp_Ratio, k_gauss, M_STAR)*M_DISK*exp(-r/R_S)/(2.0*PI*R_S*r);

 }

 Perem(rmin, dr, imax, u);		/* Calculates ghost cell values */

}
