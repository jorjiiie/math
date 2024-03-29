#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

long sum = 0;
int* ero(int requested) {

	// for now its horrible speed and whatnot but whatever! it works
	int * PRIMES = calloc (requested,sizeof(int));
	if (requested==0) return PRIMES;
	PRIMES[0]=2;
	int prime_loc = 1;
	if (requested==1) return PRIMES; // everything is quadratic residue (mod 2)
	// should make more efficient with bit array instead of int - will be 32x less memory and prob a good bit faster? (idk about that part actually but defo much less memory)
	// can prob just use relation LMAOOAOAOOO
	int SIEVE_SIZE=100000;
	int * SIF = malloc (sizeof(int) * SIEVE_SIZE);
	// first loop of sieve on its own probably
	memset(SIF,0,SIEVE_SIZE*sizeof(int));
	long long i;
	for (i=2;i*i<SIEVE_SIZE;i++) {
		if (SIF[i]) continue;
		PRIMES[prime_loc++]=i;
		//printf("%d\n",i);
		if (prime_loc==requested) {
			for (int j=0;j<prime_loc;j++) printf("%d ",PRIMES[j]);
			return PRIMES;
		}
		for (int j=i*i;j<SIEVE_SIZE;j+=i) {
			SIF[j]=1;
		}
	}
	for (;i<SIEVE_SIZE;i++) {
		if (SIF[i]) continue;
		PRIMES[prime_loc++]=i;
		if (prime_loc==requested) return PRIMES;
	}
	int it = 1;
	while (prime_loc < requested) {
		// do one loop of sieve
		memset(SIF,0,sizeof(int)*SIEVE_SIZE);
		for (i=0;i<prime_loc;i++) {
			// sieve out current primes;
			// next num in sieve size is i*((SIEVE_SIZE*it-1)/i+1);
			if (PRIMES[i]*1LL*PRIMES[i]>SIEVE_SIZE*(it+1)||PRIMES[i]*1LL*PRIMES[i]<0) break; // done for this segment since sorted! also if its way too big
			long long next_number = PRIMES[i]*((SIEVE_SIZE*it-1)/PRIMES[i]+1);
			if (next_number < PRIMES[i]*1LL*PRIMES[i]) next_number=PRIMES[i]*1LL*PRIMES[i]; // i*i if bueno?
		//	printf("%d NEXT IS %lld\n",PRIMES[i],next_number);
			for (;next_number<SIEVE_SIZE*(it+1);next_number+=PRIMES[i]) {
				SIF[next_number-SIEVE_SIZE*(it)]=1;
			}

		}
		// do sieve now
		// 'normal sieve'
		for (i=0;i<SIEVE_SIZE;i++) {
			if (SIF[i]) continue;
			// i + SIEVE_SIZE*it is prime
			// if SIEVE_SIZE is anything like
			// well if SIEVE_SIZE*2 < sqrt(SIEVE_SIZE)
			// this won't be used in this segment
			PRIMES[prime_loc++]=(i+SIEVE_SIZE*it);
			if (prime_loc==requested) return PRIMES;
			
		}
		it++;
		// printf("%d %d %d\n",it,prime_loc, SIEVE_SIZE*it);
	}
	return PRIMES;
	
}
int main() {
	clock_t t = clock();
	int * k = ero(1e7);
	printf("primes done in %f seconds\n",(double)(clock()-t)/CLOCKS_PER_SEC);
	for (int i=1;i<69;i++) printf("%d ", k[i]);
	for (int i=1;i<1e7;i++) {
		if (k[i] < 2e7) {
			sum +=k[i];
		} else break;
	}
	printf("%ld", sum);
}
