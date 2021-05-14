#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "vector.c"
#ifdef __cplusplus
extern "C" {
#endif
mpz_t N_FOR_SIEVE_SO_I_DONT_HAVE_TO_COPY_EVERY_TIME;
mpz_t LOL_LOL_LOL,XABC;
int check(long long j) {
	// returns nonzero if solution to x*x == n (mod j) exists
	return 1; // for speed testing
	mpz_set_si(LOL_LOL_LOL,j);
	mpz_mod_ui(XABC,N_FOR_SIEVE_SO_I_DONT_HAVE_TO_COPY_EVERY_TIME,j);	
	int res = mpz_legendre(XABC,LOL_LOL_LOL);
	if (res==1) return 1;
	return 0;
}
int* ero(int requested,mpz_t n) {

	// for now its horrible speed and whatnot but whatever! it works

	vector_32 primes;

	requested++;
	
	int * VALID_PRIMES = calloc (requested,sizeof(int));
	VALID_PRIMES[0]=2;

	mpz_init(N_FOR_SIEVE_SO_I_DONT_HAVE_TO_COPY_EVERY_TIME);
	mpz_init(LOL_LOL_LOL);
	mpz_init(XABC);
	mpz_set(N_FOR_SIEVE_SO_I_DONT_HAVE_TO_COPY_EVERY_TIME,n);

	int prime_loc=1;
	vector_init(&primes);	
	int SIEVE_SIZE=10000;
	int * SIF = malloc (sizeof(int) * SIEVE_SIZE);
	
	// first loop of sieve on its own probably
	memset(SIF,0,SIEVE_SIZE*sizeof(int));
	long long i;

	for (i=3;i*i<SIEVE_SIZE*2;i+=2) {
		if (SIF[i/2]) continue;
		vector_push_back(&primes,i); // yes i did implement a vector just for this

		if (check(i)) {
			VALID_PRIMES[prime_loc++]=i;
		}
	
		if (prime_loc==requested) {
			goto end;
		}
		for (int j=i*i;j<SIEVE_SIZE*2;j+=i*2) {
			SIF[j/2]=1;
		}
	}
	for (;i<SIEVE_SIZE*2;i+=2) {
		if (SIF[i/2]) continue;
		vector_push_back(&primes,i);
		if (check(i)) VALID_PRIMES[prime_loc++]=i;
		if (prime_loc==requested) goto end;
	}
	int it = 1;
	while (prime_loc < requested) {
		// do one loop of sieve
		memset(SIF,0,sizeof(int)*SIEVE_SIZE);
		for (i=0;i<primes.back;i++) {
			// sieve out current primes;
			// next num in sieve size is 2*i*((SIEVE_SIZE*it-1)/i+1);
			long long p = primes.nums[i];
			if (p*p>SIEVE_SIZE*(it+1)*2||p*p<0) break; // done for this segment since sorted! also if its way too big
			long long next_number = p*((2*SIEVE_SIZE*it-1)/p+1);
			if ((next_number&1)==0) next_number+=p;
			if (next_number < p*p) next_number=p*p; // i*i if bueno?
			// printf("next num is %lld %lld\n",next_number, p);
			for (;next_number<SIEVE_SIZE*2*(it+1);next_number+=p*2) {
				SIF[(next_number-SIEVE_SIZE*2*(it))/2]=1;
			}

		}
		// do sieve now
		// 'normal sieve'
		for (i=1;i<SIEVE_SIZE*2;i+=2) {
			if (SIF[i/2]) continue;
			// i + SIEVE_SIZE*it is prime
			// if SIEVE_SIZE is anything like
			// well if SIEVE_SIZE*2 < sqrt(SIEVE_SIZE)
			// this won't be used in this segment
			vector_push_back(&primes,i+SIEVE_SIZE*it*2);
			if (check(i+SIEVE_SIZE*it*2)) {
				VALID_PRIMES[prime_loc++]=(i+SIEVE_SIZE*it*2);
			}
			if (prime_loc==requested) goto end;
			
		}
		it++;
		//printf("%d %d up to %d\n",it-1,prime_loc,it*SIEVE_SIZE);
	}
	end:
		vector_free(&primes);
		free(SIF);
		mpz_clear(LOL_LOL_LOL);
		mpz_clear(N_FOR_SIEVE_SO_I_DONT_HAVE_TO_COPY_EVERY_TIME);
		mpz_clear(XABC);
		return VALID_PRIMES;
	
}

int main() {

	mpz_t jo;
	mpz_init(jo);
	mpz_set_si(jo,71);
	clock_t t = clock();
	int * k = ero(50000000,jo);
	clock_t j = clock();
	printf("time taken %lf seconds\n",(double)(j-t)*1.0/CLOCKS_PER_SEC);
	for (int i=0;i<69;i++) printf("%d ", k[i]);
	//printf("\n\n%d\n",k[69000000-1]);
	int lol =  69;
	printf("%d nth prime is something %d\n",lol,k[lol]);
	mpz_clear(jo);
	free(k);

}
#ifdef __cplusplus
}
#endif

