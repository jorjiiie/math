#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct relation
{
	// we need the Y(x) and Y'(x) I think
	// mpz_t a,b;
	uint32_t * factors;
	int len, primes;
} relation;

void r_init(relation* rel, uint32_t primes)
{
	//round primes to nearest mult of 32
	rel->len = (((primes-1)>>5)+1);
	rel->primes = primes;
	rel->factors = (uint32_t*) malloc(sizeof(uint32_t) * rel->len);
}
uint32_t* r_get(relation *rel, uint32_t location)
{
	// get int with location
	return &(rel->factors[location>>5]); 
}
void r_ch(relation *rel, uint32_t prime)
{
	// change bit at prime
	rel->factors[prime>>5]^=(1<<(31-prime&31));
}
void r_print(relation *rel)
{
	printf("[");
	for (int i=0;i<rel->len;i++)
	{
		printf("%d ", rel->factors[i]);
	}
	printf("]");
}
void r_printb(relation *rel)
{
	printf("[");
	int pos = 0;
	for (int i=0;i<rel->len;i++)
	{
		for(int j=0;j<32;j++)
		{
			printf("%d ", (rel->factors[i]&(1<<(31-pos&31)))?1:0);
			pos++;
		}
	}
	printf("]");
}
int main()
{
	relation joe;
	r_init(&joe, 36);
	r_ch(&joe,5);
	*r_get(&joe,33)=20;
	r_print(&joe);
	printf("\n");
	r_printb(&joe);
}
