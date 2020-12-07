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

mpz_t POWBASE;

int highest_pow(int n, mpz_t BIG_NUMBER) {	
	int current = 1, previous = 0;
	mpz_set_ui(POWBASE,n);	
	while (mpz_cmp(BIG_NUMBER,POWBASE)>0) {
		mpz_pow_ui(POWBASE,POWBASE,2);
		current<<=1;
	}
	return current;
}


int p_minus_one(mpz_t n) {
	FILE *PRIMES = fopen("PRIMES.txt","r");

	mpz_init(POWBASE);
	mpz_t a,b;
	mpz_init(a);
	mpz_init(b);
	mpz_set_si(a,2);
	mpz_root(b,n,6);


	int next_prime;
	fscanf(PRIMES,"%d",&next_prime);
	while (mpz_cmp_si(b,next_prime)>=0) {
		//printf("%d\n",next_prime);

		int power = highest_pow(next_prime,n);
		mpz_powm_ui(a,a,next_prime,n);
		mpz_powm_ui(a,a,power,n);
		
		//gmp_printf("%Zd\n",a);
		fscanf(PRIMES,"%d",&next_prime);
	}
	mpz_t factor_maybe;
	mpz_init(factor_maybe);
	mpz_sub_ui(a,a,1);
	mpz_gcd(factor_maybe,a,n);

	gmp_printf("%Zd factor maybe\n",factor_maybe);
	mpz_clears(a,b,POWBASE,NULL);
}


int main() {
	mpz_t n;
	mpz_init(n);
	mpz_set_str(n,"20880179768762133619",10);
	p_minus_one(n);
}
