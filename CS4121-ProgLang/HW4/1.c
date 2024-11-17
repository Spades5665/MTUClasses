#include <stdio.h>

main() {
    int i1, i2;
    float f1, f2;
    
    i1 = 3;
    i2 = 2;
    f1 = i1/i2 + 1.0/2;
    i1 = f1;
    printf("%d\n", i1);
    printf("%.1f\n", f1);
    
    f1 = 3;
    i2 = 2;
    f1 = f1/i2 + 1.0/2;
    i1 = f1;
    printf("%d\n", i1);
    printf("%.1f\n", f1);
}
