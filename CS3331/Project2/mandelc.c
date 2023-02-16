#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PRINTBUFSIZE 241

int main(int argc, char *argv[]) {

    double complex start;  //-- Top left corner
    double width;          //-- Length of the top side
    double height;         //-- Length of the left side
    int hpixels;           //-- Pixels per imaginary side (left and right)
    int wpixels;           //-- Pixels per real side      (top and bottom)
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

    // Checks for correct number of inputs
    if (argc != 8 ) {
        printf("\nmandel RealLeft ImagLeft RealWidth ImagHeight EscapeIterations WidthPixels HeightPixels\n\n");
        exit(1);
    }

    // Calculates top left corner
    start = strtod(argv[1], NULL) + strtod(argv[2], NULL) * I;
  
    // Finds length of top side
    width = strtof(argv[3], NULL);

    // Finds length of left side
    height = strtof(argv[4], NULL);
  
    // Finds iteration count
    maxiterations = atoi(argv[5]);

    // Finds pixel count
    wpixels = atoi(argv[6]);

    // Finds pixel count
    hpixels = atoi(argv[7]);

    // Shared Memory
    int **pointCounts;

    // Shared Memory Key
    key_t memKey = ftok("./", 'u'); // "./" is this file, 'u' is the unique id

    // Checks if creating key worked
    if (memKey < 0) {
        printf("\nFailed to create key in mandelc!\n\n");
        exit(1);
    }

    // Creates Shared Memory
    int memID = shmget(memKey, (sizeof(int *) * wpixels) + (sizeof(int) * wpixels * wpixels), IPC_CREAT | 0666);

    // Checks if creating memID worked
    if (memID < 0) {
        printf("\nFailed to access shared memory in mandelc!\n\n");
        exit(1);
    }

    // Attaches Shared Memory to pointCounts
    pointCounts = (int**) shmat(memID, NULL, 0);

    // Checks if attaching memory worked
    if (pointCounts < 0) {
        printf("\nFailed to attach memory in mandelc!\n\n");
        exit(1);
    }

    hpixels = 3;
    for (i = 0; i < hpixels; i++) {
        unsigned long long rowstart = (unsigned long long) pointCounts + (hpixels * sizeof(int *)) + (i * hpixels * sizeof(int));
        pointCounts[i] = (int *) rowstart;
    }

    for (int rows = 0; rows < hpixels; rows++) {
        for (int columns = 0; columns < wpixels; columns++) {
            pointCounts[rows][columns] = 1;
        }
    }

    // Detaches from shared memory
    shmdt(pointCounts);

    exit(0);

    // Calculations Print
    snprintf(printBuf, PRINTBUFSIZE, "Top left coordinate is: %f + %fi\nLength of top/bottom side:  %f\nPixels of top/bottom side:  %d\nLength of left/right side:  %f\nPixels of left/right side:  %d\n", creal(start), cimag(start), width, wpixels, height, hpixels);
    write(1, printBuf, strlen(printBuf));

    snprintf(printBuf, PRINTBUFSIZE, "Process %d testing rectangle at %.8f + %.8f \n\twidth %.8f and height %.8f \n\tplot area width %d by height %d pixels.\n", getpid(), creal(start), cimag(start), width, height, wpixels, hpixels);
    write(1, printBuf, strlen(printBuf));

  z = 0;
  size = 0;
  increment = width / ( (double) wpixels - 1 );  //-- How far we move at each step

  for (pheight = 0; pheight < hpixels; pheight++) {

      c = start - (double) pheight * increment * I;

      for (pwidth = 0; pwidth < wpixels; pwidth++) {

#ifdef DEBUGCALC	
	   printf("\nc = %f + %f\n", creal(c), cimag(c));
#endif
           z = 0;

           iterations = 0;

           for (i = 1; i <= maxiterations; i++) {

               z = cpow(z, 2) + c;
               
#ifdef DEBUGCALC	  
               printf("z^2 = %f + %f\n", creal(z), cimag(z));
#endif	  

               size = cabs(z);
               
#ifdef DEBUGCALC
               printf("size of z is %f\n",size);
#endif	  

               if (size > 2.0) {
                   iterations = i;
                   break;
               }
               
           }

           if (i > maxiterations) {
               iterations = maxiterations;
           }
           
#ifndef DEBUGCALC	
           //addPoint(colorscheme, iterations, maxiterations, fp);
#endif
           
           c = c + increment + 0 * I;

      }

  }

  // End Print
  snprintf(printBuf, PRINTBUFSIZE, "Process %d done.\n", getpid());
  write(1, printBuf, strlen(printBuf));

}
