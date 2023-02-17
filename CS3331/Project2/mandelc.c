#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
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
    int hPixels;           //-- Pixels per imaginary side (left and right)
    int wPixels;           //-- Pixels per real side      (top and bottom)
    double increment;      //-- Length between pixels in complex plane
    double complex z;      //-- Temporary used in mandelbrot recurrence computation
    double complex c;      //-- Temporary used in mandelbrot recurrence computation
    double size;           //-- Temporary used in mandelbrot recurrence computation
    int maxIterations;     //-- Number of iterations use to identify points in the set
    int iterations;        //-- Recurrence iteration counters
    int i, w, h;                 //-- Loop index for recurrence relation5
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
    maxIterations = atoi(argv[5]);

    // Finds pixel count
    wPixels = atoi(argv[6]);

    // Finds pixel count
    hPixels = atoi(argv[7]);

    // Shared Memory
    int **pointCounts;

    // Shared Memory Key
    key_t memKey = ftok("./", 'u'); // "./" is this file, 'u' is the unique

    // Checks if creating key worked
    if (memKey < 0) {
        printf("\nFailed to create key in mandelc!\n\n");
        exit(1);
    }

    // Creates Shared Memory
    int memID = shmget(memKey, sizeof(int *) * wPixels + sizeof(int) * wPixels * wPixels, IPC_CREAT | 0666);

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

    // Finds starting point on the graph for each child
    int hStart = (getpid() - getppid() - 1) * hPixels;

    for (h = hStart; h < hStart + hPixels; h++) {
        unsigned long long rowStart = (unsigned long long) pointCounts + (wPixels * sizeof(int *)) + (h * wPixels * sizeof(int));
        pointCounts[h] = (int*) rowStart;
    }

    // Calculations Print
    snprintf(printBuf, PRINTBUFSIZE, "Top left coordinate is: %f + %fi\nLength of top/bottom side:  %f\nPixels of top/bottom side:  %d\nLength of left/right side:  %f\nPixels of left/right side:  %d\n", creal(start), cimag(start), width, wPixels, height, hPixels);
    write(1, printBuf, strlen(printBuf));

    snprintf(printBuf, PRINTBUFSIZE, "Process %d testing rectangle at %f + %f \n\twidth %f and height %f \n\tplot area width %d by height %d pixels.\n", getpid(), creal(start), cimag(start), width, height, wPixels, hPixels);
    write(1, printBuf, strlen(printBuf));

    increment = width / ( (double) wPixels - 1 );  //-- How far we move at each step

    //printf("\nChild [%d] has values: hStart = %d, Limit = %d and w = %d, Limit = %d\n\n", getpid() - getppid(), hStart, hStart + hPixels, 0, wPixels);
    for (h = hStart; h < hStart + hPixels; h++) {

        c = start - (double) h * increment * I + ((getpid() - getppid() - 1) * height * I);

        printf("c = %f + %f --- start = %f + %f, h = %d, increment = %f\n", creal(c), cimag(c), creal(start), cimag(start), h, increment);

        for (w = 0; w < wPixels; w++) {

#ifdef DEBUGCALC	
	    printf("\nc = %f + %f\n", creal(c), cimag(c));
#endif
            z = 0;

            iterations = 0;

            for (i = 1; i <= maxIterations; i++) {

                z = cpow(z, 2) + c;
               
#ifdef DEBUGCALC	  
                printf("z^2 = %f + %f\n", creal(z), cimag(z));
#endif	  

                size = cabs(z);
               
#ifdef DEBUGCALC
                printf("size of z is %f\n",size);
#endif

                if (getpid() - getppid() - 1 == 5) {
                    //printf("\nTrying to access [%d][%d]", h, w);
                    printf("HW: [%d][%d] --- c = %f + %f, z = %f + %f, size = %f\n", h, w, creal(c), cimag(c), creal(z), cimag(z), size);
                }

                if (size > 2.0) {
                    iterations = i;
                    break;
                }

            }

            if (i > maxIterations) {
                iterations = maxIterations;
            }

            if (getpid() - getppid() - 1 == 5) {
                //printf("\nTrying to access [%d][%d]", h, w);
                printf("Iterations value: %d, max = %d\n", iterations, maxIterations);
            }

            pointCounts[h][w] = iterations;
           
            c = c + increment + 0 * I;

        }

    }

    /*printf("Here is the memory [%d] added: \n", getpid() - getppid() - 1);
    for (h = hStart; h < hStart + hPixels; h++) {
        for (w = 0; w < wPixels; w++) {
            printf("%d ", pointCounts[h][w]);
        }
        printf("\n");
    }*/

    // Detaches from shared memory
    shmdt(pointCounts);

    // End Print
    snprintf(printBuf, PRINTBUFSIZE, "Process %d done.\n", getpid());
    write(1, printBuf, strlen(printBuf));

}
