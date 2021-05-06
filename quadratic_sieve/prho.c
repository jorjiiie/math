#pragma once

#include <stdio.h>
#include <gmp.h>
#include <time.h>

/*
 * Ryan Zhu
 * September 28, 2020
 * Last Updated 05/06/21
 *
 * Pollard Rho Factoring
 * Uses APR-CL for prime testing, and GNU GMP for supporting large integers
 * Implementation is mostly similar to the implementation in CLRS, but has a slight modification to the function f(x)=x*x+c
 * (update may 2021) I better unstand pollard rho now and am tempted to use a random function but I'm pretty sure the point of the cycle finding is to break out if there's an actual cycle sad
*/ 

void prho(mpz_t n, mpz_t res) {
	mpz_t x,y,k,d,diff; 
	gmp_randstate_t state;
	
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,(long int) time(0));

	mpz_inits(x,y,k,d,diff, NULL);
	int c=1; // f(x)=(x*x)+c
	while(1) { 
		int cnt = 1;
		mpz_set_si(k,2);
		mpz_urandomm(x,state,n);
		mpz_set(y,x);	
		while (1) {
			// Pollard Rho
			cnt++;
			mpz_mul(x,x,x);
			mpz_add_ui(x,x,c);

			mpz_mod(x,x,n);
			mpz_sub(diff,y,x);
			mpz_gcd(d,diff,n);
			if (mpz_cmp(d,n)==0) {
				break;
			}
			if (mpz_cmp_si(d,1)!=0) {
				mpz_set(res,d);
				mpz_clears(y,x,diff,d,k, NULL);
				return;
			}
			if (mpz_cmp_ui(k,cnt)==0) {
				mpz_set(y,x);
				mpz_add(k,k,k);
			}
		}
		c++;
		// if we y==x then we break the loop and try again with a different value of c
	}
}

void rhofactor(mpz_t n, mpz_t *vec, int *pos) {
	if (mpz_probab_prime_p(n,50)) { // check factor is prime
		mpz_set(vec[(*pos)++],n);
		return;
	}
	mpz_t aaa,next;
	mpz_inits(aaa,next, NULL);
	
	prho(n,aaa);
	mpz_tdiv_q(next,n,aaa);

	rhofactor(next,vec,pos);
	rhofactor(aaa,vec,pos);
	
	mpz_clears(aaa,next, NULL);
	return;
}

void prho_factor(mpz_t n, mpz_t *vec, int *pos)
{
	if (mpz_probab_prime_p(n,50)) { // check factor is prime
		mpz_set(vec[(*pos)++],n);
		return;
	}
	while (mpz_even_p(n)) 
	{ // handle even
		mpz_tdiv_q_2exp(n,n,1);
		mpz_set_si(vec[(*pos)++],2);
	}
	rhofactor(n,vec,pos);
}

/*
int main() {
	mpz_t test,arr[1000],a,b;
	mpz_inits(a,b,test,NULL);
	mpz_set_str(a,"399899999999999",10);
	mpz_set_str(b,"493935332521159",10);
	mpz_mul(test,a,b);
	// mpz_init_set_str(test,"19326223710861634601",10);
	int cnt = 0;
	rhofactor(test,arr,&cnt);
	printf("num has %d factors\n",cnt);
	for (int i=0;i<cnt;i++)
	{
		gmp_printf("%Zd ",arr[i]);
	}
}
*/