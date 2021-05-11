#pragma once
/*
	Ryan Zhu
	File with relations and relation matrix
	just abstraction (i'm programming in c with abstraction, look at me!)
*/
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct relation
{
	uint32_t * factors;
	int len, primes;
	mpz_t a,b;

} relation;

void r_init(relation* rel, uint32_t primes)
{
	//round primes to nearest mult of 32
	rel->len = (((primes-1)>>5)+1);
	rel->primes = primes;
	rel->factors = (uint32_t*) malloc(sizeof(uint32_t) * rel->len);
}
void r_set_mpz(relation* rel, mpz_t Y, mpz_t X)
{
	mpz_init(rel->a);
	mpz_init(rel->b);
	mpz_set(rel->a,Y);
	mpz_set(rel->b,X);
}
void r_clear(relation* rel)
{
	mpz_clear(rel->a);
	mpz_clear(rel->b);
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

typedef struct matrix
{
	relation * rels;
	uint32_t len;
} matrix_r;
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
