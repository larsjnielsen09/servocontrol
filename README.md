<h1>Hello, fellow robotics learners</h1>
For those of us who are on a budget, have brain-sized balls (or ball-sized brains, depending on POV),
and/or plan to control the robot from an embedded system (or any combination thereof), I've been trying to implement some of the MATLAB functionality in C.<br>
I'ts work in progress, dudes. Forward and reverse kinematics will be coming any day now.<br>
Feel free to contribute, but don't improve matrix_mul() unless you really, really, really, really know what you're doing - I pulled my hair out to make that beast work.

To compile, type make at the $ prompt<br>
$ make

<h2>matrix</h2>
matrix.c contains enough maxtrix operations to get through the course, 
then adding whatever is necessary to get a Chinese 6DOF robot arm working with TowerPro MG996R servos.<br>
The low-level stuff will be in servoctl.c.<br>

To use the matrix operations, include matrix.h.<br>

<code>

/* Let's multiply two matrices, m x m2 and store the product in m3 */
#include "matrix.h"


/* 1. Declare the three matrices you'll be using. */

	matrix_t* m = matrix_new(3,3); /* Create a 3x3 matrix */
	matrix_t* m2 = matrix_new(1,3);/* Create a 1x3 matrix */
	matrix_t* m3;

/* 2. Put some values in m and m2 */

	matrix_set_col(m,0, 1.0, 2.0, 3.0);
	matrix_set_col(m,1, 4.0, 5.0, 6.0);
	matrix_set_col(m,2, 7.0, 8.0, 9.0);

	matrix_set_col(m2,0, 1.0, 2.0, 3.0);

	/* Print it */
	matrix_printf("%2.0f ", m);
	printf("*\n");
	matrix_printf("%2.0f ", m2);
	printf("=\n");
	
/* 3. Multiply them and print the result */

	m3 = matrix_mul(m, m2);
	matrix_printf("%2.0f ", m3);
	

/* 4. Clean up, and you're done. */
	matrix_del(m2);
	matrix_del(m3);
	
	matrix_del(m);
</code>


<h2>Servoctl</h2>
Contains low-level routines for dealing with servos and the Adafruit servo controller.
