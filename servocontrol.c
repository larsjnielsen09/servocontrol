/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
//shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
//chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
/*
 * main.c
 * Copyright (C) 2017 
	 * 
 * servocontrol is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * servocontrol is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include "servoctl.h"

int main(int argc, char** argv)
{
	int i, steps;
	char* format = "%2.1f "; 
	double p0, p1;
	if(argc < 4) {
		fprintf(stderr, "Usage: %s p0 p1 steps", argv[0]);
		exit(1);
	}
	p0 = atof(argv[1]);
	p1 = atof(argv[2]);
	steps = atoi(argv[3]);
	if (argc >= 4){
		format = argv[4];
	}
	printf("servo positions\n");
	double* ar = interpolate(p0, p1, steps);
	for(i = 0; i < steps; i++) {
		printf(format, ar[i]);
	}
	free(ar);
	printf("\n");
	return 0;
}
