/*
	Ryan Zhu
	September 26, 2020
	Miller Rabin in C, improved over my previous C++ version with large number (gmp) support
*/
#include <stdio.h>
#include <time.h>
#include <gmp.h>
#include <stdbool.h>

const int TESTS=50;

int test(mpz_t a, int t, mpz_t u, mpz_t n) {

	mpz_t n2,cur,prev; //n2=n-1;
	mpz_inits(n2,cur,prev,NULL);
	
	mpz_powm(prev,a,u,n);

	mpz_set(n2,n);
	mpz_sub_ui(n2,n2,1);


	for (int i=0;i<t;i++) {
		
		mpz_mul(cur,prev,prev);
		mpz_mod(cur,cur,n);

		// if cur==1 and prev was 1 or n-1
		if (mpz_cmp_ui(cur,1)==0&&(mpz_cmp_ui(prev,1)!=0&&mpz_cmp(prev,n2)!=0)) {
			mpz_clears(cur,n2,prev,NULL);
			return 1;
		}
		mpz_set(prev,cur);
	}
	if (mpz_cmp_ui(prev,1)!=0) {
		mpz_clears(cur,n2,prev,NULL);
		return 1;
	}
	mpz_clears(cur,n2,prev,NULL);
	return 0;
}
int mpz_miller_rabin(mpz_t n) {
	
	if (mpz_cmp_ui(n,2)==0) return 0;
	if (mpz_even_p(n)) return 1;

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,(long int) time(0));

	// decomponse n-1 into 2^t*u
	mpz_t u,n2;
	int t=0;
	mpz_inits(u,n2,NULL);

	mpz_set(u,n);
	mpz_sub_ui(u,u,1);

	mpz_set(n2,n);
	mpz_sub_ui(n2,n2,1);

	while(mpz_even_p(u)) {
		t++;
		mpz_tdiv_q_2exp(u,u,1);
	}

	for (int i=0;i<TESTS;i++) {

		mpz_t cur;
		mpz_init(cur);

		// mpz_urandomm gives a number from [0,n], so to get [1,n-1) we do [0,n-2]+1
		mpz_urandomm(cur,state,n2); 
		mpz_add_ui(cur,cur,1); 

		if (test(cur,t,u,n)) {
			mpz_clears(cur,u,n2,NULL);
			return 1;
		}
	}
	mpz_clears(u,n2,NULL);
	return 0;
}
int main() {

	mpz_t test;
	mpz_init(test);
	for (int i=2;i<1000;i++) {
		mpz_set_ui(test,i);
		if (mpz_miller_rabin(test)==0) {
			printf("%d IS PRIME!!\n",i);
		}
	}
}