#include <stdio.h>
#include <math.h>
#define PI 3.14159265359

void *spectrumToRGB(int **pointCounts, int width, int height, int maxiterations, int *iterSpecMap, FILE *outfile) {
    int i, j, total;
    unsigned char red, green, blue;
    
    total = width * height;
    
    for (i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if (pointCounts[i][j] == maxiterations) {
                red=0;
	        green=0;
	        blue=0;
	    } else {
                red = sin( (float) iterSpecMap[pointCounts[i][j] - 1] / (float) total * PI / 2) * 255;
	        green = sin( (float) iterSpecMap[pointCounts[i][j] - 1] / (float) total * PI) * 255;	   
	        blue = cos( (float) iterSpecMap[pointCounts[i][j] - 1] / (float) total * PI / 2) * 255;
	    }
            
	    fputc(red, outfile);
	    fputc(green, outfile);
   	    fputc(blue, outfile);
	   
	}
    }
}
