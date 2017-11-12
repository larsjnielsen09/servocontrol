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
#include "matrix.h"

#define ELM(m, col, row) (m->v[(m->ncols*row)+col])

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

void matrix_del(matrix_t* m)
{
	assert(m);
	assert(m->v);
	free(m->v);
	free(m);
}

/*
	Extract a column vector from a matrix
	Yes, I know it returns a vector.
	My point is: Whatever you call it, don't forget to free it after use!
*/
matrix_t* matrix_get_col_vector(matrix_t* m, int col_no){
	int i;
	
	assert(m->ncols<col_no);
	
	matrix_t* rv = matrix_new(1, m->nrows);
	for (i = 0; i < m->nrows; i += m->ncols){
		*rv->v++=m->v[i];
	}
	return rv;
}


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

/*
Same as ELM, but a lot safer.
*/
void matrix_set(matrix_t* m, int col, int row, double d){
	assert(col<m->ncols);
	assert(row<m->nrows);
	m->v[(m->ncols*row) + col] = d;
}

double* matrix_get(matrix_t* m, int col, int row){
	assert(col<m->ncols);
	assert(row<m->nrows);
	return m->v + (m->ncols*row) + col;
}


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

void matrix_rol(matrix_t* m, double theta){
}


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

