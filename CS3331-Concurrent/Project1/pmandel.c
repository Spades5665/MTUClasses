#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pmandel.h"

int main(int argc, char* argv[]) {
    if (argc == 8) {

        int numChildren = atoi(argv[7]);
        double inc = 1.0 / numChildren;
        for (int i = 0; i < numChildren; i++) {
            if (fork() == 0) {
                printf("\n[Child %d] creates image from %0.2f to %0.2f\n", i, i * inc, (i + 1) * inc);
                exit(0);
            }
        }

        for (int i = 0; i < numChildren; i++) {
            wait(NULL);
        }

        char l[] = {"L"};
        printf("\n");
        
    } else {
        printf("\nProper Format: pmandel <tlr> <tli> <side-length> <max-iterations> <pixels> <image-file> <nprocs>\n\n");
    }
}