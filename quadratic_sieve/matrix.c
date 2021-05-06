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
#include <stdint.h>
typedef struct matrix
{
	// will i deal with this cancer yes apparently so
	uint32_t ** a;
	int rows, cols;

} matrix;
// i'll leave it as r,c but 
void m_init(matrix* mat, int r, int c)
{
	(mat->a) = (uint32_t**)  malloc(r * sizeof *mat->a);
	if (mat->a)
	{
		for (int i = 0; i < r; i++)
		{
			mat->a[i] = malloc(sizeof(mat->a[i]) * c);
		}
	}
	mat->rows = r;
	mat->cols = c;
}

uint32_t* m_get(matrix* mat, int i, int j)
{
	return &(mat->a[i][j]);
}
void m_set(matrix* mat, int i, int j, int v)
{
	mat->a[i][j]=v;
}
void m_ch(matrix* mat, int i, int bitNum)
{
	// ith row, and the int is bitNum/32 
	uint32_t* num = m_get(mat, i, bitNum>>5); 
	// uhh idk if this is the best but whatever!!
	(*num)^=((uint32_t) 1<<(31-bitNum&31));

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
		printf("X]");
		if (i+1<mat->rows) printf("\n");
		else printf(" ]\n");
	}
}
// we need a copy here so we don't screw up the original matrix, if the first solve doesn't work, (then permute)
int gauss(matrix* mat, int* sol)
{
	return 1;
}

int main()
{
	matrix joe;
	m_init(&joe,5,5);
	m_print(&joe);
//	m_set(&joe,1,1,64);
//	*m_get(&joe,0,0)=5;
	m_ch(&joe,0,0);
	m_print(&joe);
}	
