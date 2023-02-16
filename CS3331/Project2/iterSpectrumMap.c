#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int *iterSpectrumMap(int *iterationMap, int maxiterations) {
    int *iterSpecMap;
    int i, leadingEdge, width;
  
    iterSpecMap = malloc(maxiterations * sizeof(int));
    if (iterSpecMap == 0) {
        return(iterSpecMap);
    }
  
    bzero(iterSpecMap, maxiterations * sizeof(int));
  
    leadingEdge = 0;
    for (i = 0; i < maxiterations; i++) {
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
