#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])

{
    FILE            *fpt;
    int             ROWS,COLS,MAX, i;
    unsigned char   *image;
    char            header[80];

    if (argc != 2)
        {
            printf("Usage: Brighten [filename.ppm]\n");
            exit(0);
        }


fpt = fopen(argv[1], "rb");
if (fpt == NULL)
    {
        printf("Unable to open %s for reading\n", argv[1]);
        exit(0);
    }

fscanf(fpt, "%s %d %d %d ", header, &COLS, &ROWS, &MAX);
image=(unsigned char *)calloc(ROWS*COLS, sizeof(unsigned char));
fread(image, ROWS*COLS,1,fpt);
fclose(fpt);
/* printf("First pixel value is %d\n", image[0]); */

for (i=0; i<ROWS*COLS; i++)
    {
        if (image[i] < 205)
        image[i]+=50;
    }
fpt = fopen("brighter.ppm", "wb");
fprintf(fpt,"P5 %d %d 255\n", COLS, ROWS);
fwrite(image, 512*512,1,fpt);
fclose(fpt);
}