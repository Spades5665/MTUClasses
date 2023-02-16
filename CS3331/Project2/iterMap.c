#include <strings.h>
#include <stdlib.h>
int *iterMap(int **pointCounts,int width,int height, int maxiterations) {

    int i, j;
    int *iterationMap;

    iterationMap = malloc(maxiterations * sizeof(int));
    if (iterationMap == 0) {
        return NULL;
    }
    bzero(iterationMap, maxiterations * sizeof(int));

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            iterationMap[pointCounts[i][j] - 1] = iterationMap[pointCounts[i][j] - 1] + 1;
        }
    }
    
    return iterationMap;
}





  
