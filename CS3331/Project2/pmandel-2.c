#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

int *iterMap(int **pointCounts,int width,int height, int maxIterations) {

    int i, j;
    int *iterationMap;

    iterationMap = malloc(maxIterations * sizeof(int));
    if (iterationMap == 0) {
        return NULL;
    }
    bzero(iterationMap, maxIterations * sizeof(int));

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            iterationMap[pointCounts[i][j] - 1] = iterationMap[pointCounts[i][j] - 1] + 1;
        }
    }

    return iterationMap;
}

int *iterSpectrumMap(int *iterationMap, int maxIterations) {
    int *iterSpecMap;
    int i, leadingEdge, width;

    iterSpecMap = malloc(maxIterations * sizeof(int));
    if (iterSpecMap == 0) {
        return(iterSpecMap);
    }

    bzero(iterSpecMap, maxIterations * sizeof(int));

    leadingEdge = 0;
    for (i = 0; i < maxIterations; i++) {
        width = iterationMap[i];

        if (iterationMap[i] != 0) {
            iterSpecMap[i] = leadingEdge + (width / 2) + 1;
        } else {
            iterSpecMap[i] = 0;
        }

        leadingEdge += iterationMap[i];
    }

    return(iterSpecMap);
}

void *spectrumToRGB(int **pointCounts, int width, int height, int maxIterations, int *iterSpecMap, FILE *outfile) {
    int i, j, total;
    unsigned char red, green, blue;

    total = width * height;

    for (i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if (pointCounts[i][j] == maxIterations) {
                red = 0;
                green = 0;
                blue = 0;
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
        if (pixels < 10) {
            printf("\nMust be at least 10 pixels!\n\n");
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
        int memID = shmget(memKey, sizeof(int *) * pixels + sizeof(int) * pixels * pixels, IPC_CREAT | 0666);

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
            double imagL = atof(argv[2]) - ( (getpid() - parentID - 1) * ratio * atof(argv[3]) ); // Imaginary left - ( (which section of the picture) * ratio * width )

            // Height of child picture
            double height = atof(argv[3]) * ratio;

            // Height of child picture in pixels
            int hPixels = atoi(argv[5]) * ratio;
            
            // Converts values to strings
            char imag[10];
            char heig[10];
            char hPix[10];
            
            sprintf(imag, "%f", imagL);
            sprintf(heig, "%f", height);
            sprintf(hPix, "%d", hPixels);

            // Array for mandel
            char *args[] = {"./mandelc", argv[1], imag, argv[3], heig, argv[4], argv[5], hPix, (char*) NULL};

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

        // Sets up access to shared memory
        for (int i = 0; i < pixels; i++){
            unsigned long long rowStart = (unsigned long long) pointCounts + (pixels * sizeof(int *)) + (i * pixels * sizeof(int));
            pointCounts[i] = (int*) rowStart;
        }
        
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
        spectrumToRGB(pointCounts, pixels, pixels, atoi(argv[4]), iterSpecMap, finalFile);

        // Frees iterSpecMap
        free(iterSpecMap);

        // Detaches from shared memory
        shmdt(pointCounts);

        // Deletes shared memory
        shmctl(memID, IPC_RMID, NULL);

        // Closes parent file
        fclose(finalFile);
        
        // Buffer line
        printf("\n");
        
    } else {

        // Correct format
        printf("\nProper Format: pmandel-2 <tlr> <tli> <side-length> <max-iterations> <pixels> <image-file> <nprocs>\n\n");

    }

}
