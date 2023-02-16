#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "pmandel-2.h"

int main(int argc, char* argv[]) {

    if (argc == 8) {

        // Holds parents PID to single it out from the children
        pid_t parentID = getpid();
        
        // Gets number of children process to create
        int numChildren = atoi(argv[7]);

        // Detects number of children
        if (numChildren <= 0) {
            printf("\nNo Children!\n\n");
            exit(1);
        }

        // Gets pixel count for picture
        int pixels = atoi(argv[5]);

        // Makes sure its of proper size
        if (pixels < 48) {
            printf("\nMust be at least 48 pixels!\n\n");
            exit(1);
        }

        // Checks other inputs
        if (atof(argv[3]) <= 0) {
            printf("\nWidth must be greater than zero.\n\n");
            exit(1);
        }

        if (atoi(argv[4]) < 2) {
            printf("\nMax iterations must be at least 2.\n\n");
            exit(1);
        }
        
        // Shared Memory 
        int **pointCounts;
        
        // Shared Memory Key
        key_t memKey = ftok("./", 'u'); // "./" is this file, 'u' is the unique id

        // Makes sure key creation worked
        if (memKey < 0) {
            printf("\nFailed to create key in pmandel!\n\n");
            exit(1);
        }
        
        // Creates Shared Memory
        int memID = shmget(memKey, (sizeof(int *) * pixels) + (sizeof(int) * pixels * pixels), IPC_CREAT | 0666);

        // Makes sure memory creation worked
        if (memID < 0) {
            printf("\nFailed to create shared memory in pmandel!\n\n");
            exit(1);
        }

        // Attaches Shared Memory to pointCounts
        pointCounts = (int**) shmat(memID, NULL, 0);

        // Makes sure the memory was properly attached
        if (pointCounts < 0) {
            printf("\nFailed to attach memory in pmandel!\n\n");
            exit(1);
        }

        // Creates the children
        for (int i = 0; i < numChildren; i++) {
            if (getpid() == parentID) {
                if (fork() < 0) {
                    printf("\nFork Failed!\n\n");
                    exit(1);
                }
            }
        }
        
        // Children run this
        if (getpid() != parentID) {
            
            // Calculates ratio for height values
            double ratio = 1.0 / numChildren;
            
            // Imaginary start
            double imagL = atof(argv[2]) - ( getpid() - parentID - 1 * ratio * atof(argv[3]) ); // Imaginary left - ( (which section of the picture) * ratio * width )

            // Height of child picture
            double height = atof(argv[3]) * ratio;

            // Height of child picture in pixels
            int hpixels = atoi(argv[5]) * ratio;
            
            // Converts values to strings
            char imag[10];
            char heig[10];
            char hpix[10];
            
            sprintf(imag, "%f", imagL);
            sprintf(heig, "%f", height);
            sprintf(hpix, "%d", hpixels);

            // Array for mandel
            char *args[] = {"./mandelc", argv[1], imag, argv[3], heig, argv[4], argv[5], hpix, (char*) NULL};

            // Calls mandel
            if (execvp(args[0], args)) {
                printf("\nFailed exec call\n\n");
                exit(1);
            }
            
            // Kills Child
            exit(0);
        }

        // Parent function waits for all children to be done
        for (int i = 0; i < numChildren; i++) {
            wait(NULL);
        }

        for (int i = 0; i < pixels; i++){
            unsigned long long rowstart = (unsigned long long) pointCounts + (pixels * sizeof(int *)) + (i * pixels * sizeof(int));
            pointCounts[i] = (int *) rowstart;
        }

        printf("\n");
        for (int r = 0; r < atoi(argv[5]) * (1.0 / numChildren); r++) {
            for (int c = 0; c < pixels; c++) {
                printf("%d ", pointCounts[r][c]);
            }
            printf("\n");
        }
        printf("\n");

        // Detaches from shared memory
        shmdt(pointCounts);
        
        // Create Final image
        FILE * finalFile = fopen(argv[6], "wb");
        if (finalFile == NULL) {
            printf("\nFailed to open final file\n\n");
            exit(1);
        }

        // Header for final file
        fprintf(finalFile, "P6\n%d %d\n255\n", atoi(argv[5]), atoi(argv[5]));

        // Set parent file values
        int *iterationMap = iterMap(pointCounts, pixels, pixels, atoi(argv[4]));
        int *iterSpecMap = iterSpectrumMap(iterationMap, atoi(argv[4]));
        //spectrumToRGB(pointCounts, pixels, pixels, atoi(argv[4]), iterSpecMap, finalFile);

        // Closes parent file
        fclose(finalFile);
        
        // Buffer line
        printf("\n");
        
    } else {

        // Correct format
        printf("\nProper Format: pmandel-2 <tlr> <tli> <side-length> <max-iterations> <pixels> <image-file> <nprocs>\n\n");

    }

}
