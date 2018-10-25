#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <errno.h>

#include <fenv.h>
#include <string.h>

/*
Output filename: kaosz_index(nu)_index(x_1).dat

x_1 values : 2 - Ordered motion
             3 - chaotic motion


10 studied nu values: [0.5, 1.5]

10000 steps [0, 10000]


Plotting help for Gnuplot: 
	    plot for[i=1:10] for[j=2:3]'kaosz_'.i.'_'.j.'.dat'

            or

            set title 'Ordered'
            plot for[i=1:10] 'kaosz_'.i.'_2.dat'
            set title 'Chaotic'
            plot for[i=1:10] 'kaosz_'.i.'_3.dat'

*/


int main()
{

double x_1 = 0;
double x_1_cyc = 0;
double x_2 = 0;
float nu = 0;
int i, n, filenum;
double x1, x1_res, x2_res;
double pi = 3.1415;


for(x_1_cyc = 2; x_1_cyc <=3; x_1_cyc++)
{
    x_1 = x_1_cyc;
    x_2 = 0;
    filenum = 0;
    for(nu = 0.5; nu <= 1.5; nu += 0.1)
    {
        FILE* file = fopen("kaosz.dat", "w");
        if(!file)
            {
            printf("File opening failed");
            return 1;
            }

        filenum++;
        char filenum_str[2];
        itoa(filenum, filenum_str, 10);
        char x_1str[2];
        itoa(x_1_cyc, x_1str, 10);
        char ext[5] = ".dat";
        char newfilename[16] = "kaosz_";
        strcat(newfilename, filenum_str);
        strcat(newfilename, "_");
        strcat(newfilename, x_1str);
        strcat(newfilename, ext);
        remove(newfilename);

        for(i = 0; i != 10000; i++)
        {
            x1 = (x_1 + x_2);

            x_1 = x1;
            x_2 = fmod((x_2 - nu*sin(x1)), (2*pi));

            n = floor(x_1/(2*pi));
            x1_res =(x_1 - n*2*pi);
            x2_res = x_2 - pi;
            if(x1_res > pi) x1_res -= 2*pi;
            //printf("%lf, %lf \n", x1_res, x2_res);
            fprintf(file, "%lf %lf\n", x1_res, x2_res);

        }
        fclose(file);
        rename("kaosz.dat", newfilename);


    }
}

return 0;
}
