/*
 * matrix.c
 *
 * Copyright (C) 2017 - Jan Atle Ramsli
	 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
	 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"


/**
Create a new matrix.
\arg columns - The number of columns in the matrix
\arg rows - The number of rows in the matrix.
\returns A new matric that must be deleted with matrix_del().
\warning Don't free() instances of #matrix_t. You'll be leaving dangling pointers inside.
**/
matrix_t* matrix_new(int columns, int rows)
{
	matrix_t* rv = malloc(sizeof(matrix_t));
	if (! rv){
		perror("matrix_new:- malloc() failed");
		exit(-1);
	}
	rv->ncols = columns;
	rv->nrows = rows;
	rv->v = calloc(sizeof(double), columns * rows);
	if (! rv){
		perror("matrix_new:- calloc() failed");
		exit(-1);
	}
	return rv;						 
}

/**
Delete a matrix.
\arg m - The matrix to be deleted 
- Matrices can be created with other functions than matrix_new().
- In general, if the called function returns a pointer to a #matrix_t, that matrix must be deleted with this destructor function.
**/
void matrix_del(matrix_t* m)
{
	assert(m);
	assert(m->v);
	free(m->v);
	free(m);
}

/**
	Extract a column vector from a matrix.
	\arg m - The matrix from which to extract the column
	\arg col_no - The column number to extract. Starts with 0.
	\returns A new vector of type #matrix_t that must be deleted with matrix_del().
	
**/
matrix_t* matrix_get_col_vector(matrix_t* m, int col_no){
	int i;
	
	assert(m->ncols<col_no);
	
	matrix_t* rv = matrix_new(1, m->nrows);
	for (i = 0; i < m->nrows; i += m->ncols){
		*rv->v++=m->v[i];
	}
	return rv;
}

/**
Set the column col_no in m.
\arg m - The matrix to maniplulate.
\arg col_no - The column that we wish to set
\arg ... - The values
- The argument list must contain one entry for each rown in m.
- There is no way to check this without cluttering up the code.
*/
void matrix_set_col(matrix_t* m, int col_no, ...)
{
    va_list ap;
    int row;
    
    assert(col_no < m->ncols);
    
    va_start(ap, col_no); //Requires the last fixed parameter (to get the address)
    for(row=0; row<m->nrows; row++){
    	m->v[(row*m->ncols) + col_no]=va_arg(ap, double);
    }
    va_end(ap);
}

/**
Set the element at column col and row row in m to d.
-Same as ELM the macro hack, but a lot safer.
*/
void matrix_set(matrix_t* m, int col, int row, double d){
	assert(col<m->ncols);
	assert(row<m->nrows);
	m->v[(m->ncols*row) + col] = d;
}

/**
Return a pointer to the element at col, row in m.
- The array containing this element is maintained by matrix_t, so don't try to delete this.
**/
double* matrix_get(matrix_t* m, int col, int row){
	assert(col<m->ncols);
	assert(row<m->nrows);
	return m->v + (m->ncols*row) + col;
}


/**
Print the contents of matrix m using format.
\arg format - Passed on to printf().
\arg m - The matrix to print.
- Typically, you'd use "%2.1f " (note the space).
**/
void matrix_printf(char* format, matrix_t* m){
	int i,j;
	
	for(i = 0; i < m->nrows; i++){
		printf("[");
		for(j = 0; j < m->ncols; j++){
			printf(format, m->v[(i * m->ncols) + j]);
		}
		printf("]\n");
	}
}

/**
Rotate a matrix around x-axis
\bug Create x,y,z static rotation matrices to avoid alloc/free 
- The result must be deleted with matrix_del()
**/
matrix_t* matrix_rot_x(matrix_t* m, double theta){
	matrix_t* rv;
	matrix_t* rm; // Return value, rotation matrix
	rm = matrix_new(3,3);
	matrix_set_col(rm, 0, 1.0, 0.0, 0.0);
	matrix_set_col(rm, 1, 0.0, cos(theta), sin(theta));
	matrix_set_col(rm, 2, 0.0, -sin(theta), cos(theta));
	rv = matrix_mul(rm, m);
	matrix_del(rm);
	return rv;
}


/**
Rotate a matrix around y-axis
- The result must be deleted with matrix_del():
**/
matrix_t* matrix_rot_y(matrix_t* m, double theta){
	matrix_t* rv;
	matrix_t* rm; // Return value, rotation matrix
	rm = matrix_new(3,3);
	matrix_set_col(rm, 0, cos(theta), 0.0, -sin(theta));
	matrix_set_col(rm, 1, 0.0, 1.0, 0.0);
	matrix_set_col(rm, 2, sin(theta), 0.0, cos(theta));
	rv = matrix_mul(rm, m);
	matrix_del(rm);
	return rv;
}

/**
Rotate a matrix around z-axis
- The result must be deleted with matrix_del():
**/
matrix_t* matrix_rot_z(matrix_t* m, double theta){
	matrix_t* rv;
	matrix_t* rm; // Return value, rotation matrix
	rm = matrix_new(3,3);
	matrix_set_col(rm, 0, cos(theta), sin(theta), 0.0);
	matrix_set_col(rm, 1, -sin(theta), cos(theta), 0.0);
	matrix_set_col(rm, 2, 0.0, 0.0, 1.0);
	rv = matrix_mul(rm, m);
	matrix_del(rm);
	return rv;
}


/**
multiply m1 x m2
- This function is used as a 'workhorse' for kinematic functions.
- The result must be deleted with matrix_del().
\returns A new matrix that must be deleted with matrix_del().
**/
matrix_t* matrix_mul(matrix_t* m1, matrix_t* m2)
{
	int row, col;
	matrix_t* rv;
	int col2;

	assert(m1->ncols==m2->nrows);

	rv = matrix_new(m2->ncols, m1->nrows);
	col2 = 0;
	// First row1, first col2 -> first row3, first col3
	// First row1, second col2 ->first row3, second col3
	// First row1, third col2 ->first row3, third col3
	// Second row1, first col2->second row3, first col3
	// Second row1, second col2->second row3, second col3
	// Second row1, third col2->second row3, third col3
	// Third row1, first col2->third row3, first col3
	// et cetera
	for (row = 0; row < m1->nrows; row ++){
		for(col2=0; col2<m2->ncols;col2++){  
			for(col = 0; col < m1->ncols; col++){
				ELM(rv, col2, row) += (ELM(m1, col, row) * ELM(m2, col2, col));
			}	
		}
	}
	return rv;
}

