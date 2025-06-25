
//-----------------------------------------------------------------
// Computes members of mandelbrot for specified square region
// of the real/imaginary plane. Creates PPM image file
// according to one of several color schemes.
//-----------------------------------------------------------------
//
// Compilation: gcc -o mandel mandel.c -lm
//
//-----------------------------------------------------------------
//
// Invocation: mandel RealCoord ImagCoord SideLength EscapeIterations PixelsPerSide ImageFile
//
// See the project handout for a detailed description of the parameters and
// operation of the program.
//------------------------------------------------------------------
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "mandel.h"

#define PRINTBUFSIZE 241

int main(int argc, char *argv[]){
  
  double complex start;  //-- Top left corner
  double range;          //-- Length of a side in complex plane
  int pixels;            //-- Pixels per side
  double increment;      //-- Length between pixels in complex plane
  double complex z;      //-- Temporary used in mandelbrot recurrence computation
  double complex c;      //-- Temporary used in mandelbrot recurrence computation
  double size;           //-- Temporary used in mandelbrot recurrence computation
  int maxiterations;     //-- Number of iterations use to identify points in the set
  int iterations;        //-- Recurrence iteration counters
  int pheight;           //-- Counter for loop over pixels down imaginary axis
  int pwidth;            //-- Counter for loop over pixels across real axis
  int i;                 //-- Loop index for recurrence relation
  FILE *fp;              //-- Descriptor for file to hold image
  char printBuf[PRINTBUFSIZE];    //-- Output buffer
  int *iterationMap;     //-- Maps # of iterations to # of points that escaped at that iteration count
  int **pointCounts;     //-- Escape iterations for each point
  int *iterSpecMap;      //-- Maps iteration count to a location in the spectrum
  int total;             //-- Total number of points

  //
  // -- Process the input arguments
  //
  if (argc!=7){
    printf("mandel RealCoord ImagCoord SideLength EscapeIterations PixelsPerSide ImageFile\n");
    exit(1);
  } 
  start=strtod(argv[1],NULL)+strtod(argv[2],NULL)*I;
  printf("Top left coordinate is: %f + %fi\n", creal(start), cimag(start));  
  range=strtod(argv[3],NULL);
  if (range<=0){printf("Range must be greater than zero.\n");exit(1);}
  printf("Length of a side:  %f\n",range);
  maxiterations=atoi(argv[4]);
  if (maxiterations<2){printf("Max iterations must be at least 2.\n");exit(1);}
  pixels=atoi(argv[5]);
  printf("Pixels per side:  %d\n",pixels);
  if (pixels<48){printf("Pixels must be at least 48.\n");exit(1);}

  fp=fopen(argv[6], "wb"); /* b - binary mode */
  if (fp==NULL){printf("%s cannot be opened for write\n",argv[6]);}
  (void) fprintf(fp, "P6\n%d %d\n255\n", pixels, pixels);  

   //-- NEW allocating space for the point counts
   //   Access is regular indexing: pointCounts[x][y]
   //
    pointCounts=(int **)malloc(pixels*sizeof(int *));
    if (pointCounts==NULL)
      {
	printf("Can malloc space for point counts\n");
	exit(1);
      }
    
    for (i=0;i<pixels;i++) {
      pointCounts[i]=(int *)malloc(pixels*sizeof(int));
      if (pointCounts[i]==NULL)
	{
	  printf("Can't malloc space for point counts\n");
	  exit(2);
	}
    }
    //-- End pointCounts allocation 
    
    snprintf(printBuf,PRINTBUFSIZE,"Process %d testing rectangle at %.8f + %.8f \n\twidth %.8f and height %.8f \n\tplot area width %d by height %d pixels.\n",getpid(),creal(start),cimag(start),range,range,pixels,pixels);
    write(1,printBuf,strlen(printBuf));
  //
  // -- Start the mandelbrot set identification calculation 
  //    One to one correspondance between pixels ad points
  //    in the plane to be evaluated.  Divde the range by
  //    the number of pixels on a side to identify points. 
  //    Start at te left corner and work down the imaginary
  //    axis by rwo. Only square spaces in the real-imaginary
  //    plane.
  //
  z=0;
  size=0;
  increment=range/((double)pixels-1);  //-- How far we move at each step
  for (pheight=0;pheight<pixels;pheight++){
      c=start-(double)pheight*increment*I;
      for (pwidth=0;pwidth<pixels;pwidth++){
           z=0;
	       iterations=0;
           for (i=1;i<=maxiterations;i++){
                z=cpow(z,2)+c;
	            size=cabs(z);
	            if (size>2.0){
	                 iterations=i;
	                 break;
	            }
           }
	   

	      if (i>maxiterations)iterations=maxiterations;
	      //-- NEW
	      pointCounts[pheight][pwidth]=iterations; //-- Filling in pointCounts
	                                                //-- In the previous project just computed color
	                                                //-- for the point and addded point to PPM file
               c=c+increment+0*I;
      }      
  }

  //
  //--- Parent performs these calculations once the children have filled in pointCounts
  //
  total=pwidth*pheight;
  iterationMap=iterMap(pointCounts,pwidth,pheight,maxiterations);
  iterSpecMap=iterSpectrumMap(iterationMap,maxiterations);  
  spectrumToRGB(pointCounts,pwidth,pheight,maxiterations,iterSpecMap,fp);  
       
}





  
