/*
 * test_matrix.c
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
#include <assert.h>
#include "matrix.h"

#define PI 3.141592654
// TODO assert post-conditions (tedious, manual work, but necessary)

void test_matrix_new(){
	matrix_t* m = matrix_new(3,3);
	printf("\n----------------- Create:-----------\n");
	assert(m);
	assert(m->v);
	matrix_printf("%f ", m);
	printf("**** PASSED!\n");
	matrix_del(m);
}

void test_matrix_mul()
{
	matrix_t* m = matrix_new(3,3);
	matrix_t* m2 = matrix_new(1,3);
	matrix_t* m3;
	printf("\n----------------- Multiply -----------\n");
	printf("\n----------------- 3x1:-----------\n");	
	matrix_set_col(m,0, 1.0, 2.0, 3.0);
	matrix_set_col(m,1, 4.0, 5.0, 6.0);
	matrix_set_col(m,2, 7.0, 8.0, 9.0);
	matrix_printf("%2.0f ", m);
	printf("*\n");
	
	matrix_set_col(m2,0, 1.0, 2.0, 3.0);
	matrix_printf("%2.0f ", m2);
	printf("=\n");
	
	m3 = matrix_mul(m, m2);
	matrix_printf("%2.0f ", m3);
	
	// TODO Assert postcondition
	assert(ELM(m3, 0,0)==30);
	assert(ELM(m3, 0,1)==36);
	assert(ELM(m3, 0,2)==42);
	printf("**** PASSED!\n");
	
	matrix_del(m2);
	matrix_del(m3);

	printf("\n----------------- 3x3:-----------\n");
// Do a 3x3 matrix
	matrix_printf("%2.0f ", m);
	printf("*\n");

	m2 = matrix_new(3,3);
	matrix_set_col(m2,0, 1.0, 2.0, 3.0);
	matrix_set_col(m2,1, 4.0, 5.0, 6.0);
	matrix_set_col(m2,2, 7.0, 8.0, 9.0);
	matrix_printf("%2.0f ", m2);
	printf("=\n");

	m3 = matrix_mul(m, m2);
	matrix_printf("%2.0f ", m3);

// TODO Assert postcondition
/*
	30    66   102
    36    81   126
    42    96   150*/

	assert(ELM(m3, 0,0)==30);
	assert(ELM(m3, 1,0)==66);
	assert(ELM(m3, 2,0)==102);
	assert(ELM(m3, 0,1)==36);
	assert(ELM(m3, 1,1)==81);
	assert(ELM(m3, 2,1)==126);
	assert(ELM(m3, 0,2)==42);
	assert(ELM(m3, 1,2)==96);
	assert(ELM(m3, 2,2)==150);
	printf("**** PASSED!\n");
	
	matrix_del(m2);
	matrix_del(m3);
	
	matrix_del(m);

}

void test_matrix_rol()
{
	matrix_t* m = matrix_new(1,2);
	matrix_t* m2;
	printf("\n----------------- Rotate 30 deg:-----------\n");
	
	matrix_set_col(m, 0, 4.0, 5.0);
	matrix_printf("%2.0f ", m);
	printf("\n");
	m2 = matrix_rol2r(m, (30*PI)/180);
	matrix_printf("%2.3f", m2);
	// TODO Assert postcondition
	
	matrix_del(m);
	matrix_del(m2);
}

void test_matrix_set_col()
{
	matrix_t* m = matrix_new(3,3);
	printf("\n----------------- set_col :-----------\n");
	matrix_set_col(m, 1, 1.0, 2.0, 3.0);
	matrix_printf("%1.0f ", m);
	
	// TODO Assert postcondition
	assert(ELM(m, 1,0)==1.0);
	assert(ELM(m, 1,1)==2.0);
	assert(ELM(m, 1,2)==3.0);
	printf("**** PASSED!\n");
	
	matrix_del(m);
}

void test_matrix_printf()
{
}

int main()
{
	test_matrix_new();
	test_matrix_set_col();
	test_matrix_mul();
	test_matrix_rol();
}
