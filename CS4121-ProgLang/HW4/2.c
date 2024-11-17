#include <stdio.h>

struct S1 {
    int a;
    int b;
} s1, s3;

struct S2 {
    int b;
    int a;
} s2;

typedef struct S1 S;

S s4;

main() {
    s1.a = 10;
    s1.b = 20;
    s2 = s1;
    s3 = s1;
    s4 = s1;
    printf("s2.a = %d; s2.b = %d\n", s2.a, s2.b);
    printf("s3.a = %d; s3.b = %d\n", s3.a, s3.b);
    printf("s4.a = %d; s4.b = %d\n", s4.a, s4.b);
}
