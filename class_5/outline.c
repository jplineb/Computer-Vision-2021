/* Coding challenge:

Write a program that outlines all occurrences of a given letter in parenthood.ppm.  The outline should be 9 (width) x 15 (height) pixels around the center point as identified in the ground truth file.  Set the outline pixels to 255 intensity.

Usage:  outline [letter]

Assume parenthood.ppm and parenthood_gt.txt are in the current directory.

*/
	
  /*
	** Outlines the given letter in parenthood.ppm.
	** Requires parenthood_gt.txt.
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])

{
FILE		*fpt;
unsigned char	*image;
char		header[80];
int		ROWS,COLS,BYTES;
int		letter_r,letter_c,r,c,i;
char		letter,gt_letter[10];

	/* tell user how to use program if incorrect arguments */
if (argc != 2)
  {
  printf("Usage:  outline [letter]\n");
  exit(0);
  }
letter=argv[1][0];

	/* open image for reading */
fpt=fopen("parenthood.ppm","rb");
if (fpt == NULL)
  {
  printf("Unable to open %s for reading\n","parenthood.ppm");
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

	/* open GT file for reading */
fpt=fopen("parenthood_gt.txt","r");
while (1)
  {
  i=fscanf(fpt,"%s %d %d",gt_letter,&letter_c,&letter_r);
  if (i != 3)
    break;
  if (gt_letter[0] != letter)
    continue;
  for (r=letter_r-7; r<=letter_r+7; r++)
    {
    image[r*COLS+letter_c-4]=255;	/* left line */
    image[r*COLS+letter_c+4]=255;	/* right line */
    }
  for (c=letter_c-4; c<=letter_c+4; c++)
    {
    image[(letter_r-7)*COLS+c]=255;	/* top line */
    image[(letter_r+7)*COLS+c]=255;	/* bottom line */
    }
  }
fclose(fpt);

	/* write out the output result */
fpt=fopen("outlined.ppm","wb");
if (fpt == NULL)
  {
  printf("Unable to open outlined.ppm for writing\n");
  exit(0);
  }
fprintf(fpt,"P5 %d %d 255\n",COLS,ROWS);
fwrite(image,1,ROWS*COLS,fpt);
fclose(fpt);
}

