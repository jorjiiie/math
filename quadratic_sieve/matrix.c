#pragma once
/*
	Ryan Zhu
	April 2020
	Matrix class so we can do stuff, both manipulation and yadayada
	i may or may not be switching to c++ but i'll see
	maybe still c...
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct matrix
{
	// will i deal with this cancer yes apparently so
	int * a;
	int rows, cols;

} matrix;

void m_init(matrix* mat, int r, int c)
{
	(mat->a) = (int*)  malloc(r * c * sizeof *mat->a);
	mat->rows = r;
	mat->cols = c;
}

int* m_get(matrix* mat, int i, int j)
{
	return &(mat->a[i*mat->cols+j]);
}
void m_set(matrix* mat, int i, int j, int v)
{
	mat->a[i*mat->cols+j]=v;
}
void m_ch(matrix* mat, int i, int bitNum)
{
	int shift = 32;
	// ith row, and the int is bitNum/32 
	int* num = m_get(mat, i, bitNum>>5); 
	// uhh idk if this is the best but whatever!!
	(*num)^(1<<(bitNum&7));

	return;
}
void m_print(matrix* mat)
{
	printf("[ ");
	for (int i=0;i<mat->rows;i++)
	{
		printf("[");
		for (int j=0;j<mat->cols;j++)
		{
			printf("%d, ",*(m_get(mat,i,j)));
		}
		printf("X]\n");
	}
}
int main()
{
	matrix* joe;
	m_init(joe,5,5);
	m_print(joe);
}	
