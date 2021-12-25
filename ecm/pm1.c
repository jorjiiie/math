#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include <gmp.h>

/*
 * Ryan Zhu
 * December 5 2020
 * Pollard's p-1 factorization
 * I get this one!
 * Working on stage 1 
*/

mpz_t POWBASE;
mpz_t TMP_NUM;
mpz_t prime;
int isp[100000001];
int highest_pow(int n, mpz_t BIG_NUMBER) {	
	int current = 1;
	// binary search on power
	int left = 0, right = mpz_sizeinbase (BIG_NUMBER, 2);
	int power = 0;
	mpz_set_ui(POWBASE,n);	
	while (left <= right) {
		int mid = (left+right)/2;
		mpz_pow_ui(TMP_NUM, POWBASE, mid);
		if (mpz_cmp(BIG_NUMBER,TMP_NUM)>0) {
			// too small
			left = mid+1;
			power = mid;
		} else {
			right = mid-1;
		}
	}
	return power;
	
	while (mpz_cmp(BIG_NUMBER,POWBASE)>0) {
		mpz_pow_ui(POWBASE,POWBASE,2);
		current<<=1;
	}
	return current;
}


int p_minus_one(mpz_t n) {
	FILE *PRIMES = fopen("PRIMES.txt","r");

	mpz_init(POWBASE);
	mpz_init(TMP_NUM);
	mpz_init(prime);
	mpz_t a,b;
	mpz_init(a);
	mpz_init(b);
	mpz_set_si(a,2);
	mpz_root(b,n,6);


	gmp_printf("%Zd\n",b);
	int next_prime;
	fscanf(PRIMES,"%d",&next_prime);
	// will get into an infinite loop if b > largest prime
	while (mpz_cmp_si(b,next_prime)>=0) {
		printf("%d\n",next_prime);

		int power = highest_pow(next_prime,n);
		mpz_set_si(prime,next_prime);

		mpz_pow_ui(TMP_NUM,prime,power);
		mpz_powm(a,a,TMP_NUM,n);
		
		fscanf(PRIMES,"%d",&next_prime);
	}
	mpz_t factor_maybe;
	mpz_init(factor_maybe);
	mpz_sub_ui(a,a,1);
	mpz_gcd(factor_maybe,a,n);

	gmp_printf("%Zd factor (unless it is n lol)\n",factor_maybe);
	mpz_clears(a,b,POWBASE,TMP_NUM,prime,NULL);
	return 69;
}

void sieve(int n) {
	memset(isp,0,sizeof(isp));
	isp[2]=1;
	for (long long i=3;i<=n;i+=2) {
		if (isp[i]) {
			for (long long j=i*i;j<=n;j+=i*2) {
				isp[j]=0;
			}
		}

	}
}
int main() {

	sieve(1e8);
	mpz_t n;
	mpz_init(n);
	mpz_set_str(n,"1728937891273891723897129386",10);
	int x = highest_pow(2,n);
	printf("%d\n", x);


	p_minus_one(n);
}
