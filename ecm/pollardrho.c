#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include "mpz_aprcl.h"
#include "mpz_aprcl.c"

/*
 * Ryan Zhu
 * September 28, 2020
 * Last Updated 9/29/20
 *
 * Pollard Rho Factoring
 * Uses APR-CL for prime testing, and GNU GMP for supporting large integers
 * Implementation is mostly similar to the implementation in CLRS, but has a slight modification to the function f(x)=x*x+c
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
	if (mpz_aprcl(n)==2) { // check factor is prime
		mpz_set(vec[(*pos)++],n);
		return;
	}
	if (mpz_divisible_ui_p(n, 2)) { // handle even
		mpz_t two,go;
		mpz_init_set_str(two,"2",10);
		mpz_set(vec[(*pos)++],two);
		
		mpz_init(go);
		mpz_tdiv_q(go,n,two);
		mpz_clear(two);
		rhofactor(go,vec,pos);
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
int rhocount(mpz_t n) {
	if (mpz_aprcl(n)==2) {
		return 1;
	}
	if (mpz_divisible_ui_p(n,2)) {
		mpz_t two,nxt;
		mpz_init_set_str(two,"2",10);
		mpz_init(nxt);
		mpz_tdiv_q(nxt,n,two);
		int ret= rhocount(nxt);
		mpz_clears(two,nxt,NULL);
		return ret+1;
	}
	mpz_t p,q; //n=pq (p and q are not necessarily prime
	mpz_inits(p,q,NULL);
	prho(n,p);
	mpz_tdiv_q(q,n,p);
	int ret = 0;
	ret+=rhocount(p);
	ret+=rhocount(q);
	mpz_clears(p,q,NULL);
	return ret;

}

int main() {
	mpz_t test,arr[1000],a,b;
	mpz_inits(a,b,test,NULL);
	mpz_set_str(a,"399899999999999",10);
	mpz_set_str(b,"493935332521159",10);
	//mpz_mul(test,a,b);
	mpz_init_set_str(test,"19326223710861634601",10);
	int cnt = 0;
	rhofactor(test,arr,&cnt);
	printf("num has %d factors\n",cnt);
}
