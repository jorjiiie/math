#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct vector_32 {
	// int array
	// i should honestly use c++ instead but nop i want to do this
	// implementing an entire vector struct instead of using c++ LOL
	int * nums;
	int size;
	int back;
} vector_32;
void vector_init(vector_32 * vec) {
	(vec->nums) = (int* )malloc(sizeof(int) * 2);
	vec->size = 1;
	vec->back = 0;
}
void resize(vector_32 * vec) {
	// double current capacity
	int sz = (vec)->size;
	int * n = malloc(sizeof(int)*sz*2);
	for (int i=0;i<sz;i++) {
		n[i]=(vec)->nums[i];
	}
	free((vec)->nums);
	(vec)->size<<=1;
	(vec)->nums=n;
}
void vector_init_c(vector_32 * vec, int sz)
{
	while (vec->size < sz) resize(vec);
	vec->back=0;
}


void vector_push_back(vector_32 * vec, int n) {
	vec->nums[vec->back++]=n;
	if (vec->back==vec->size) resize(vec);
}
void vector_free(vector_32 *vec) {
	free(vec->nums);
	vec->size=vec->back=0;
}
void vector_pop_back(vector_32 * vec) {
	if (vec->back==0) return;
	vec->back--;
}
int sz(vector_32 * vec) {
	return vec->back;
}
int space(vector_32 * vec) {
	return vec->size;
}
void print(vector_32 * vec) {
	for (int i=0;i<vec->back;i++) printf("%d ",vec->nums[i]);
}
int* v32_get(vector_32 * vec, int p)
{
	return &(vec->nums[p]);
}

/*
int main() {
	vector_32 joe;
	vector_init(&joe);
	vector_push_back(&joe,4);
	vector_push_back(&joe,69);
	print(&joe);
	for (int i=0;i<5000;i++) vector_push_back(&joe,69);
	vector_free(&joe);
}
*/
