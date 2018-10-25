#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

typedef struct matrix{
    int rows;
    int cols;
    double* matrix;
} mat;

/* fgtl: independent variable, fg: dependent variable, hiba: error
Arguments:
big.dat 5 666694 1
*/

int conv(int i, int j, int cols)
{
    return cols*i + j;
}

void read(mat fgtl, mat fg, mat hiba, char* f){
	int i,k;
	k = 0;
	FILE *fp = fopen(f, "r");
	for (i = 0; i < fgtl.rows*fgtl.cols; ++i)
            {
            fscanf(fp, "%lf", &fgtl.matrix[i]);
            if (i == ((k + 1)*fgtl.cols - 1)){
                fscanf(fp, "%lf", &fg.matrix[k]);
                fscanf(fp, "%lf", &hiba.matrix[k]);
                k++;
                }
            }
	fclose(fp);
}

void Diag(mat m)
{
    int i;
    for(i = 0; i < m.rows*m.cols; ++i)
        m.matrix[i] = 0;

    for(i = 0; i < m.rows; ++i)
        m.matrix[conv(i,i,m.cols)] = 1;
}

void Print(mat m)
{
    int i;
    int k = 1;
    for(i = 0; i < m.rows*m.cols; ++i)
    {
        if(k < m.cols)
            {
                printf("%lf ", m.matrix[i]);
                ++k;
            }
        else
            {
            k = 1;
            printf("%lf ", m.matrix[i]);
            printf("\n");
            }
    }
}

double* RMax(mat m)
{
    double* max = (double*)malloc(m.rows * sizeof(double));
    int i,j;

    for(i = 0; i < m.rows; ++i)
	{
	      max[i] = 0;
   	}
    for(i = 0; i < m.rows; ++i)
	{
        for(j = 0; j < m.cols; ++j)
        {
            if(fabs(m.matrix[conv(i,j,m.cols)]) > fabs(max[i]))
            {
                max[i] = m.matrix[conv(i,j,m.cols)];
            }
        }
        if(fabs(max[i]) < 0.0000001)
        {
            printf("Singular");
            exit(0);
        }

    }
    return max;
}

void RSwap(mat m, int a, int b)
{

    int i;
    double buff;

    for(i = 0; i < m.cols; ++i)
    {
        buff = m.matrix[conv(a, i, m.cols)];
        m.matrix[conv(a, i, m.cols)] = m.matrix[conv(b, i, m.cols)];
        m.matrix[conv(b, i, m.cols)] = buff;
    }

}

void RSwapFull(mat m, mat inv)
{
   int i,coln;


   for(coln = 0; coln < m.cols; ++coln)
   {
       for(i = coln; i < m.cols; ++i)
       {
            if(fabs(m.matrix[i*m.cols+coln]) > fabs(m.matrix[coln*(m.cols+1)]))
            {
                RSwap(m, coln, i);
                RSwap(inv, coln, i);


            }
       }
        if(fabs(m.matrix[coln*(m.cols+1)]) < 0.00000001)
        {
            printf("Singularity.");
            exit(0);
        }
   }

}

void Norm(mat m, double* max)
{
    int i,j;
    for(i = 0; i < m.rows; i++)
    {
    for(j = 0; j < m.cols; j++)
        {
        m.matrix[conv(i,j,m.cols)] /= max[i];
        }
    }
}

void SRows(mat m, int a, int b, double c)
{
    int i;

    for(i = 0; i < m.rows; ++i)
        m.matrix[conv(a, i, m.cols)] -= c*m.matrix[conv(b, i, m.cols)];
}

double* Vecmult(mat v, mat m)
{

   	int i, j;
  	double* res = (double*)calloc(m.cols, sizeof(double));

 	for(i = 0; i < m.rows; ++i)
 	{
        for(j = 0; j < m.cols; ++j)
      		{
       		res[i] += m.matrix[conv(i,j,m.cols)] * v.matrix[j];
      		}
 	}
    return res;
}


void Gauss(mat m, mat inv)
{
    int i,j;
    for(i = 0; i < m.rows; ++i)
    {
        for(j = 0; j < m.rows; ++j)
        {
            if(i != j)
            {
            SRows(inv, j, i, (m.matrix[conv(j,i,m.cols)]/m.matrix[conv(i,i,m.cols)]));
            SRows(m, j, i, (m.matrix[conv(j,i,m.cols)]/m.matrix[conv(i,i,m.cols)]));
            }
        }
    }
    double* max = (double*)malloc(m.rows * sizeof(double));
    max = RMax(m);
    Norm(m, max);
    Norm(inv, max);

}

mat Trans(mat m)
{
    int i, j;
    mat trans;
    trans.matrix = (double*)malloc(m.rows * m.cols * sizeof(double));
    trans.rows = m.cols;
    trans.cols = m.rows;

    for(i = 0; i < m.rows*m.cols; ++i)
        trans.matrix[i] = 0;

    for(i = 0; i < m.rows; ++i)
    {
        for(j = 0; j < m.cols; ++j)
        {
         trans.matrix[conv(j,i,m.rows)] = m.matrix[conv(i,j,m.cols)];
        }
    }
    return trans;
}

mat Mult(mat m1, mat m2)
{
    int i,j,k;
    mat res;
    res.matrix = (double*)calloc(m1.rows * m2.cols , sizeof(double));
    res.rows = m1.rows;
    res.cols = m2.cols;

    for(i = 0; i < res.rows; ++i)
    {
        for(j = 0; j < res.rows; ++j)
        {
            for(k = 0; k < m1.cols; ++k)
            {
                res.matrix[conv(i,j,res.cols)] += m1.matrix[conv(i,k,m1.cols)] * m2.matrix[conv(k,j,m2.cols)];
            }
        }
    }
    return res;
}

void Errmult(mat m, int i, double hiba)
{
    int j;
    for(j = 0; j<m.cols; ++j)
    m.matrix[conv(i,j,m.cols)] /= hiba;
}

void Err(mat m, mat hiba, int rec)
{
    int i;
    if(rec == 0)
    for(i = 0; i < m.rows; ++i)
        Errmult(m, i, hiba.matrix[i]);
    else

    for(i = 0; i < m.rows; ++i)
        Errmult(m, i, (1/hiba.matrix[i]));
}


mat polymat(int rows, int cols, mat m, int degree)
{
    int i,j,k;
    mat second;
    second.matrix = (double*)calloc(degree*rows*cols, sizeof(double));
    second.rows = rows;
    second.cols = cols;
    for(i=0; i<rows; ++i)
    {
        for(j=0; j<cols; ++j)
        {
            if(j==0)
            {
                second.matrix[conv(i,j,cols)] = 1;
            }
            for(k=1; k<degree+1; ++k)
            {
                second.matrix[conv(i,degree*j+k,cols)] = pow(m.matrix[conv(i,j,m.cols)],k);
            }
        }
    }
    return second;
}

void estimate (mat m, mat v, mat fgT, FILE* fp, int degree)
{
    mat est;
    est.rows = m.rows;
    est.cols = m.cols;
    est.matrix = (double*)calloc(m.rows, sizeof(double));
    int i,j,k;
    for(i=0; i<m.rows; ++i)
    {
        for(j=0; j<m.cols; ++j)
        {
            if(j==0)
            {
                est.matrix[i] = fgT.matrix[j];
            }
            else
            {
                for(k=1; k<degree+1; ++k)
                {
                    est.matrix[i] += m.matrix[conv(i,j-1,m.cols)]*fgT.matrix[j-1+k];
                }
            }
        }
        fprintf(fp, "%lf\t", est.matrix[i]);
        fprintf(fp, "%lf\n", v.matrix[i]);
    }
}


int main(int argc, char** argv)
{

    printf("Polynomical fitting.\n");

    int degree = atoi(argv[4]);

    mat fgtl;
    fgtl.cols = atoi(argv[2]);
    fgtl.rows = atoi(argv[3]);
    fgtl.matrix=(double*)malloc(fgtl.rows * fgtl.cols * sizeof(double));

    mat fg;
    fg.matrix=(double*)malloc(fgtl.rows * sizeof(double));
    fg.cols = 1;
    fg.rows = fgtl.rows;

    mat hiba;
    hiba.matrix=(double*)malloc(fgtl.rows * sizeof(double));
    hiba.cols = 1;
    hiba.rows = fgtl.rows;

    read(fgtl,fg,hiba,argv[1]);


    mat masod;
    masod.rows = fgtl.rows;
    masod.cols = degree*fgtl.cols+1;
    masod.matrix = (double*)malloc(masod.rows * masod.cols * sizeof(double));

    masod = polymat(masod.rows,masod.cols,fgtl,degree);

    mat temp;

    temp = Trans(masod);

    mat res = Mult(temp, masod);

    mat inv;
    inv.rows = res.cols;
    inv.cols = res.cols;
    inv.matrix = (double*)malloc(inv.cols * inv.cols * sizeof(double));

    Diag(inv);
    //Err(res, hiba,0);
    //Err(fg, hiba,0);

    //RSwapFull(res, inv);

    printf("\nres:\n");
    Print(res);

    mat resv;
    resv.matrix=(double*)calloc(degree*fgtl.cols+1, sizeof(double));
    resv.cols = 1;
    resv.rows = degree*fgtl.cols+1;

    resv.matrix = Vecmult(fg,temp);

    Gauss(res, inv);


    printf("\n");
    Print(resv);
    printf("\n");

    resv.matrix = Vecmult(resv,inv);

    printf("\nMatrix:\n");
    Print(res);

    printf("\nInverted matrix:\n");
    Print(inv);

    printf("\nMatrix2:\n");
    Print(resv);

    int i;
    FILE* fp = fopen("res.dat", "w");
    for(i = 0; i < fg.rows; ++i)
        fprintf(fp, "%lf\n", fg.matrix[i]);
    fclose(fp);




    /*fgtl.cols = atoi(argv[2]);
    fgtl.rows = atoi(argv[3]);
    fgtl.matrix=(double*)malloc(fgtl.rows * fgtl.cols * sizeof(double));

    fg.matrix=(double*)malloc(fgtl.rows * sizeof(double));
    fg.cols = 1;
    fg.rows = degree*fgtl.cols+1;

    hiba.matrix=(double*)malloc(fgtl.rows * sizeof(double));
    hiba.cols = 1;
    hiba.rows = fgtl.rows;*/

    mat fgT;
    fgT.matrix=(double*)calloc(masod.rows, sizeof(double));
    fgT.rows = 1;
    fgT.cols = masod.rows;


    int j;
    for(i = 0; i < masod.rows; ++i)
    {
        for(j = 0; j < masod.cols; ++j)
        {
         fgT.matrix[i] += (masod.matrix[conv(i,j,masod.cols)] * resv.matrix[j]);
        }
    }

    FILE* f = fopen("est.dat", "w");
    for(i = 0; i < fgtl.rows; ++i)
    {
        fprintf(f, "%lf\t", fg.matrix[i]);
        fprintf(f, "%lf\n", fgT.matrix[i]);
    }
    fclose(f);

    free(fg.matrix);
    free(fgT.matrix);
    free(hiba.matrix);

    return 0;
}
