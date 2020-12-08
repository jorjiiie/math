#include <gmp.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "mpz_aprcl.c"
// #include "ecm.h"

/*
 * Ryan Zhu 
 * December 5, 2020
 * Elliptic curve factorization
 * I have no idea what I'm doing, essentially I have been copying wikipedia's formula's and whatnot
 * I don't understand why anything works, I just get that it does
 * Pollard's p-1 somewhat makes sense, but the order of elliptic curves doesn't really :(
 * Should be able to factor out ~30 digit factors from what I've read
 * Currently unfinished (stage 1 only)
*/

typedef struct point {
	mpz_t x,y;
} point;

mpz_t GLOBAL_Y,GLOBAL_X, BOUND_A;
mpz_t TOP, BOTTOM, TEMP_T, TEMP_R, TEMP_PROD, SLOPE, N;

mpz_t CURVE_A, CURVE_B;

int BOUND_A_LOG;
int NUMBER_OF_CURVES=5;

void init_all() {
	mpz_init(GLOBAL_Y);
	mpz_init(GLOBAL_X);
	mpz_init(BOUND_A);
	mpz_init(TOP);
	mpz_init(BOTTOM);
	mpz_init(TEMP_T);
	mpz_init(TEMP_R);
	mpz_init(TEMP_PROD);
	mpz_init(SLOPE);
	mpz_init(N);
	mpz_init(CURVE_A);
	mpz_init(CURVE_B);
}

void clear_all() {
	mpz_clear(GLOBAL_Y);
	mpz_clear(GLOBAL_X);
	mpz_clear(BOUND_A);
	mpz_clear(TOP);
	mpz_clear(BOTTOM);
	mpz_clear(TEMP_T);
	mpz_clear(TEMP_R);
	mpz_clear(TEMP_PROD);
	mpz_clear(SLOPE);
	mpz_clear(N);
	mpz_clear(CURVE_A);
	mpz_clear(CURVE_B);
}
void LINECHECK(int l) {
	printf("LINE %d\n",l);
	fflush(stdout);
}
void point_init(point *p) {
	mpz_inits(p->x,p->y,NULL);
}

int is_on_curve(point *p) {

	//temp_t = y^2, temp_r = x^3 + ax + b
	mpz_pow_ui(TEMP_T,p->y,2);
	
	mpz_pow_ui(TEMP_R,p->x,3);
	mpz_add(TEMP_R,TEMP_R,CURVE_B);
	mpz_mul(TEMP_PROD,p->x,CURVE_A);
	mpz_add(TEMP_R,TEMP_R,TEMP_PROD);

	mpz_mod(TEMP_R,TEMP_R,N);
	mpz_mod(TEMP_T,TEMP_T,N);
	return (mpz_cmp(TEMP_R,TEMP_T)==0?1:-1);

}

int point_addition(point *a, point *b, mpz_t factor) {
	//sets a to a + b	
	point c;
	point_init(&c);

	if (mpz_cmp(a->x,b->x)==0&&mpz_cmp(a->y,b->y)!=0) {
		//idfk what to do when this happens but it shouldnt
		assert(0>1);
	}
	if (mpz_cmp(a->x,b->x)==0) {
		// slope = 3x^2+a * inverse(2*y,N)
		mpz_pow_ui(TEMP_T,a->x,2);
		mpz_mul_ui(TEMP_T,TEMP_T,3);
		mpz_add(TEMP_T,CURVE_A,TEMP_T);


		mpz_mul_2exp(TEMP_R,a->y,1);
		if (mpz_invert(TEMP_R,TEMP_R,N)==0) {
			mpz_gcd(factor,TEMP_R,N);
			return 1;
		}
		mpz_mul(SLOPE,TEMP_R,TEMP_T);
		
		

	} else {
		// slope = actual slope

		mpz_sub(TOP,b->y,a->y);
		mpz_sub(BOTTOM,b->x,a->x);

		if (mpz_invert(SLOPE,SLOPE,N)==0) {
			gmp_printf("%Zd CANNOT INVERT\n",SLOPE);
			mpz_gcd(factor,SLOPE,N);
			return 1;
		}
		
		mpz_mul(SLOPE,SLOPE,TOP);

	}
	mpz_mod(SLOPE,SLOPE,N);
	
	//x = SLOPE^2-xa-xb
	mpz_pow_ui(TEMP_T,SLOPE,2);
	mpz_sub(TEMP_T,TEMP_T,a->x);
	mpz_sub(c.x,TEMP_T,b->x);

	//y = SLOPE(xa-x)-ya
	mpz_sub(TEMP_T,a->x,c.x);
	mpz_mul(TEMP_T,TEMP_T,SLOPE);
	mpz_sub(c.y,TEMP_T,a->y);

	mpz_mod(c.y,c.y,N);
	mpz_mod(c.x,c.x,N);

	assert(is_on_curve(a)==1);
	*a=c;
	return -1;

}

int point_multiplication(point *a, mpz_t b, mpz_t factor) {
	// sets A to bA
	point c;
	point_init(&c);
	LINECHECK(__LINE__);
	while (mpz_cmp_ui(b,0)>0) {
		LINECHECK(__LINE__);
		if (mpz_odd_p(b)!=0) {
			if (point_addition(&c,a,factor)>0) {
				// uhh this means uninvertible
				// factor has the factor
				return 1;
			}
		}
		point_addition(a,a,factor);
		mpz_tdiv_q_2exp(b,b,1);
	}
	*a = c;
	return -1;
}
int blog(int n) {
	int lg = 0;
	while (n>1) {
		lg++;
		n>>=1;
	}
	return lg;
}
int highest_power(int n) {
	int lg = blog(n);
	return (BOUND_A_LOG/lg);
}


int ECM(mpz_t number) {
	init_all();
	mpz_set(N,number);
	mpz_set_str(BOUND_A,"10",10);
	FILE *IN = fopen("PRIMES.txt","r");
	
	// choose random a and (x,y) for y^2 = x^3 + ax + b
	// set b = y^2-x^3-ax
	gmp_randstate_t state;

	gmp_randinit_mt(state);
	gmp_randseed_ui(state, (long) time(0));

	point p;
	point_init(&p);

	mpz_t factor;
	mpz_init(factor);

	gmp_printf("N is %Zd\n",N);
	for (int i=0;i<NUMBER_OF_CURVES;i++) {
		//initialize p.x, p.y and x

		LINECHECK(__LINE__);
		mpz_urandomm(CURVE_A,state,N);
		mpz_urandomm(p.x,state,N);
		mpz_urandomm(p.y,state,N);
	
		mpz_powm_ui(TEMP_T,p.x,3,N);
		mpz_powm_ui(TEMP_R,p.y,2,N);
		mpz_mul(TEMP_PROD,CURVE_A,p.x);

		LINECHECK(__LINE__);
		mpz_sub(TEMP_R,TEMP_R,TEMP_T);
		mpz_sub(TEMP_R,TEMP_R,TEMP_PROD);

		mpz_mod(CURVE_B,TEMP_R,N);
		assert(is_on_curve(&p)>0);
		int next_prime = 0;
		
		gmp_printf("BOUND_A %Zd\n",BOUND_A);
		while (mpz_cmp_ui(BOUND_A,next_prime)>0) {
			LINECHECK(__LINE__);
			fscanf(IN,"%d",&next_prime);
			LINECHECK(__LINE__);
			mpz_set_si(GLOBAL_Y,next_prime);
			mpz_pow_ui(GLOBAL_Y,GLOBAL_Y,highest_power(next_prime));
			LINECHECK(__LINE__);
			gmp_printf("%Zd %Zd moved %Zd %d\n",p.x,p.y,GLOBAL_Y,next_prime);
			if(point_multiplication(&p,GLOBAL_Y,factor)>0&&mpz_cmp(factor,N)!=0) {
				gmp_printf("Factor of %Zd is %Zd\n",N,factor);
				goto end;
			}
			assert(is_on_curve(&p)>0);
		}

	}
	
	
	end:	
		clear_all();
}
int main() {

	mpz_init_set_str(BOUND_A,"10000000",10);
	
	/*
	mpz_set_si(CURVE_B,15);
	mpz_set_si(CURVE_A,9);

	mpz_set_si(N,151);
	point a,b;
	point_init(&a);
	point_init(&b);
	
	mpz_set_si(a.x,1);
	mpz_set_si(a.y,5);

	mpz_set_si(b.x, 1);
	mpz_set_si(b.y,5);

	mpz_t fac;
	mpz_init(fac);

	// check(__LINE__);
	// printf("point a is yes? on curve %d\n",is_on_curve(&b));
	point_addition(&a,&b,fac);

	gmp_printf("%Zd %Zd\n",a.x,a.y);

	*/
	mpz_t test;
	mpz_init_set_str(test,"123781218371232",10);
	ECM(test);
}
