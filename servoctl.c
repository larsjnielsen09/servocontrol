#include <stdio.h>
#include <stdlib.h>

/*
 Copyright 2017 Jan Atle Ramsli, GPL.
 Posted in the hope that it will be useful, blah, blah, blah - iow.
 If you fry your servos, don't call me.
 * 
 */

double* interpolate(double p0, double p1, int numsteps)
{
	double gap = (p1 - p0) / 2;
	int halfWay = numsteps / 2;
	int i, j;

	double* retVal = calloc(sizeof(double), numsteps + 1);
	if(!retVal) {
		perror("interpolate():- calloc failed");
		exit(-1);
	}
	retVal[halfWay] = retVal[halfWay + 1] = (p0 + p1) / 2;
	i = j = halfWay;
	while(i > 0) {
		i--;
		j++;
		gap = gap / 2;
		retVal[i] = retVal[i + 1] - gap;
		retVal[j] = retVal[j - 1] + gap;
	}
	/*
	 i-man is done, but j-man is not quite finished.
	 Let's kludge it into place with a sledgehammer.
	 */
	if(j < numsteps) {
		j++;
		retVal[j] = retVal[j - 1] + gap;
	}
	return retVal;
}
