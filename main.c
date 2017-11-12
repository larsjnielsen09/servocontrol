#include "servoctl.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    int i, steps;
    double p0, p1;
    if(argc < 4) {
	fprintf(stderr, "Usage: %s p0 p1 steps", argv[0]);
	exit(1);
    }
    p0 = atof(argv[1]);
    p1 = atof(argv[2]);
    steps = atoi(argv[3]);
    printf("servo positions\n");
    double* ar = interpolate(p0, p1, steps);
    for(i = 0; i < steps; i++) {
	printf("%2.1f ", ar[i]);
    }
    free(ar);
    printf("\n");
    return 0;
}
