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
#include "matrix.h"

void test_matrix_new(){
	matrix_t* m = matrix_new(3,3);
	matrix_printf("%f ", m);
	matrix_del(m);
}

void test_matrix_mul()
{
	matrix_t* m = matrix_new(3,3);
	matrix_t* m2 = matrix_new(1,3);
	matrix_t* m3;
	
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

	
	matrix_del(m2);
	matrix_del(m3);
	
	matrix_del(m);

}

void test_matrix_col()
{
}

void test_matrix_set_col()
{
	matrix_t* m = matrix_new(3,3);
	
	matrix_set_col(m, 1, 1.0, 2.0, 3.0);
	matrix_printf("%1.0f ", m);
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
}
