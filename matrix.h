/*
 * matrix.h
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

typedef struct matrix {
	int nrows, ncols;
	double *v;
} matrix_t;

matrix_t* matrix_new(int columns, int rows);
void matrix_del(matrix_t* m);
matrix_t* matrix_get_col_vector(matrix_t* m, int col_no);
void matrix_set_col(matrix_t* m, int col_no, ...);
matrix_t* matrix_mul(matrix_t* m1, matrix_t* m2);
void matrix_set(matrix_t* m, int col, int row, double v);
double* matrix_get(matrix_t* m, int col, int row);
void matrix_printf(char* format, matrix_t* m);
