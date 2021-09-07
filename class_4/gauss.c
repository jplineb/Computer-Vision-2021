#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Write a program that calculates 1D Gaussian kernel values given a window size and sigma. */

int main (int argc, char *argv[])
{
    int         i,w;
    double      sigma,g;

w = atoi(argv[1]);
sigma = atof(argv[2]);

for (i=-w/2; i<=w/2; i++)
    {
        g=pow(M_E,(0.0-(i*i))/(2.0*sigma*sigma));
        printf("%lf", g);
    }
printf("\n");
}