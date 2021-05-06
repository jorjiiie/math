#ifndef POLLARD_RHO

#define POLLARD_RHO

#include <stdio.h>
#include <gmp.h>


// pollard stuff
mpz_t POLLARD_X;
mpz_t POLLARD_Y;
mpz_t POLLARD_Q;
mpz_t POLLARD_D;
mpz_t POLLARD_G;
mpz_t POLLARD_Y_C
void pollardrho(mpz_t n, mpz_t factor) {
	// hmmm
	// go through x^2 + c and find nums such
	// x[i] == x[j] (mod p) where p divides N
	// we have to guarentee N isn't prime as well so it'll be handled in subroutine

	// we can do the gcd thing where it's we build up a product Q and each iteration Q *= |y-x|

	// if p divides Q at any point, then p still divides Q (mod N) because p divides N as well

	// good gcd tradeoff is probably ~ 100 since the asymptomatic is the same but gcd is just a lot slower than multiplication

	// we could comp with the first to see if we should break?

	int c = 1;
	int m=0,k=1;
	for (;;) {
		// can be random but for reproducable results ill just set to one
		mpz_set_si(POLLARD_X,1);
		mpz_set_si(POLLARD_Q,1);
		
		for (;;) {
			mpz_set(POLLARD_Y_C,POLLARD_Y);



			mpz_gcd(POLLARD_G,POLLARD_Q,n);
			if (mpz_cmp(POLLARD_G,n)==0) {
				// then backtrack from Y_C and go until 
			}
		}
		c++;
	}
}

void pollard_init() {
	mpz_init(POLLARD_X);
	mpz_init(POLLARD_Y);
	mpz_init(POLLARD_Q);
	mpz_init(POLLARD_G);
	mpz_init(POLLARD_D);
	mpz_init(POLLARD_Y_C);

}
void pollard_free() {
	mpz_free(POLLARD_X);
	mpz_free(POLLARD_Y);
	mpz_free(POLLARD_G);
	mpz_free(POLLARD_Q);
	mpz_free(POLLARD_D);
	mpz_free(POLLARD_Y_C);
}

void pfactor(mpz_t n, , int *fpos) {
	pollard_init();

	// use gmp's builtin probably prime because it's ok in 99.999% of cases
	if (mpz_probab_prime_p(n,50)) {
		mpz_set()
	}


	pollard_free();
}

#endif