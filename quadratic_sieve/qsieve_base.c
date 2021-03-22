#ifndef QSIEVE_H

#include "qsieve.h"

#endif

// we'll have a define here for now but move around later
#define segment_length 100000

#define BASE_SIZE 10000 
// idk how many is a good number but yeah!
ll factor_base[BASE_SIZE]; // 4 now


mpz_t sieve_segment[segment_length];
double log_sieve[segment_length];

mpz_t sqrt_n
void qsieve(mpz_t n, mpz_t factor) {
	// generate factor base (and filter out small primes)
	for (int i=0,int loc = 0; loc<BASE && i<PRIMES;i++) {
		
	}
	// get sqrt(n);
	if (mpz_root(sqrt_n,n,2)) mpz_add_si(sqrt_n,sqrt_n,1); // ceil
	
}
void factorize(mpz_t n, mpz_t factor) {
	// for now just call qsieve
	qsieve(n,factor);
	// later will just be the recursive call go here! (or iterative)

}
int main() {
	mpz_t factorNumber,fac;
	mpz_init(fac);
	mpz_init(factorNumber);
	mpz_set_str(factorNumber,"123456789012345678901",10);
	
	factorize(factorNumber,fac);

}
