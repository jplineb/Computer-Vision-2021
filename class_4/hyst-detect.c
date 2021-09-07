#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code is currently broken */

int main (int argc, char *argv[])
{
FILE        *fpt;
double      data[500];
int         total_data,i;
double      t1,t2;
int         start,end;

    if (argc != 2)
    {
        printf("Usage: hyst-detect [data.txt]\n");
        exit(0);
    }
t1 = atof(argv[2]);
t2 = atof(argv[3]);
fpt = fopen(argv[1], "r");
if (fpt == NULL)
    {
        printf("Unable to open file\n");
        exit(0);
    }
total_data = 0;
while (1)
{
    i=fscanf(fpt, "%lf", &(data[total_data]));
    if (i != 1)
        break;
    total_data++;

}
fclose(fpt);
printf("%d total data \n", total_data);
i=0;
while (i < total_data)
    {
    if (data[i] > t1)
        {
            i++;
            continue;
        }
    start=i;
    while (1)
    if (data[i] > t2)
        {
            i++;
            continue;
        }
    end=i;
    printf("%d...%d\n", start, end);

    }
}

