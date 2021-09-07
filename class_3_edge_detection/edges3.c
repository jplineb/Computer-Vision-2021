
	/*
	** Demonstrates how to calculate a simple gradient in one direction.
	** What is wrong with this approach?
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (int argc, char *argv[])

{
FILE		    *fpt;
unsigned char   *image,*output;
double          *gradient;
char		    header[80];
int		        ROWS,COLS,BYTES;
int		        i,j,b,r,c;
int             h,v;
int             max,min;

	/* tell user how to use program if incorrect arguments */
if (argc != 3)
  {
  printf("Usage:  edges1 [filename] [amount]\n");
  exit(0);
  }
b=atoi(argv[2]);
if (b < 0  ||  b > 255)
  {
  printf("amount must be 0...255\n");
  exit(0);
  }
	/* open image for reading */
fpt=fopen(argv[1],"rb");
if (fpt == NULL)
  {
  printf("Unable to open %s for reading\n",argv[1]);
  exit(0);
  }
	/* read image header (simple 8-bit greyscale PPM only) */
i=fscanf(fpt,"%s %d %d %d ",header,&COLS,&ROWS,&BYTES);
if (i != 4  ||  strcmp(header,"P5") != 0  ||  BYTES != 255)
  {
  printf("%s is not an 8-bit PPM greyscale (P5) image\n",argv[1]);
  fclose(fpt);
  exit(0);
  }
	/* allocate dynamic memory for image */
image=(unsigned char *)calloc(ROWS*COLS,sizeof(unsigned char));
if (image == NULL)
  {
  printf("Unable to allocate %d x %d memory\n",COLS,ROWS);
  exit(0);
  }
	/* read image data from file */
fread(image,1,ROWS*COLS,fpt);
fclose(fpt);

/* My modification -> gradient two directions and normalization */
output=(unsigned char *)calloc(ROWS*COLS,sizeof(unsigned char));
gradient=(double *)calloc(ROWS*COLS,sizeof(double));
for (r=0; r<ROWS-1; r++)
    {
        for (c=0; c<COLS-1; c++)
        {
            h=abs((int)(image[r*COLS+c+1])-(int)(image[r*COLS+c]));
            v=abs((int)(image[(r+1)*COLS+c])-(int)(image[r*COLS+c]));
            output[r*COLS+c]=(unsigned char)sqrt((double)(h*h)+(double)(v*v));
        }
    }
	/* calculate min and max to normalize */
max=min=output[0];
for (i=1; i<ROWS*COLS; i++)
  {
  if (output[i] > max)
    max=output[i];
  if (output[i] < min)
    min=output[i];
  }
printf("Range is %d to %d\n",min,max);

	/* write out edges1.ppm, the output result */
fpt=fopen("edges.ppm","wb");
if (fpt == NULL)
  {
  printf("Unable to open edges1.ppm for writing\n");
  exit(0);
  }
fprintf(fpt,"P5 %d %d 255\n",COLS,ROWS);
fwrite(output,1,ROWS*COLS,fpt);
fclose(fpt);
}

