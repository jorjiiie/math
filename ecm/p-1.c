#include <gmp.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "mpz_aprcl.c"

/*
 * Ryan Zhu
 * December 5 2020
 * Pollard's p-1 factorization
 * I get this one!
 * Working on stage 1 
*/

int p_minus_one(mpz_t n) {
	FILE *PRIMES = fopen("PRIMES.txt","r");
	mpz_t M,a,b;
	mpz_init(M);
	mpz_init(a);
	mpz_init(b);
	mpz_set_si(M,1);
	mpz_set_si(a,2);
	mpz_root(b,n,6);

	int next_prime;
	fscanf(PRIMES,"%d",&next_rpime);
	while (mpz_cmp_si(b,next_prime)>=0) {



		fscanf(PRIMES,"%d",&next_rpime);
	}
}

