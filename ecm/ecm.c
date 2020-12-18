#include <gmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "mpz_aprcl.c"
// #include "ecm.h"

#define LINE LINECHECK(__LINE__);
#define ONCURVE(x) assert(is_on_curve(x)>0);
/*
 * Ryan Zhu 
 * December 11, 2020
 * Elliptic curve factorization
 * This version has curves in Montgomery form and projective points to avoid GCD operations
 * Montgomery curves have to have 4 | group order, and Suyama's parametrization guarantees the group order to be divisible by 3 as well, meaning that 12| group order
 * Stage two might be implemented as Brent's Birthday Paradox or the standard p-1 continuation 
*/
typedef struct point {
	//defined in projective coordinates (X,,Z) (y is ommitted because it's irrelevant in calculations)
	mpz_t x,z;
} point;

mpz_t GLOBAL_Y,GLOBAL_X, BOUND_A;
mpz_t TOP, BOTTOM, TEMP_T, TEMP_R, TEMP_PROD, SLOPE, N, THREE, PROD_D;

mpz_t CURVE_A, CURVE_B;

point c;
int BOUND_A_LOG;
int BOUND_R = 100;
int NUMBER_OF_CURVES=20;
int PRIME_COUNT;

long primes[50000000];
clock_t start,end;

double ADDITION_TIME,MULT_TIME,TOTAL_TIME, SLOPE_TIME;

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
	mpz_init(THREE);
	mpz_init(PROD_D);
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
	mpz_clear(THREE);
	mpz_clear(PROD_D);
}
void LINECHECK(int l) {
	printf("LINE %d\n",l);
	fflush(stdout);
}
void point_init(point *p) {
	mpz_inits(p->x,p->y,NULL);
}
void copy_point(point *to, point *base) {
	point_init(to);
	mpz_set(to->x,base->x);
	mpz_set(to->y,base->y);
}

void point_addition(point *a, point *b, point *one) {
	// sets a to a + b	
	// a = kP, b = (k+1)P - this has to be checked in multiplication
	// this isn't universal since we need a-b for this to work (which is always 1 in a montgomery ladder so it's easy)
	// X (m+n) = Z (m-n) * [ {X(m) - Z(m)}{(X(n) + Z(n)} + {X(m)+Z(M)}{X(n)-Z(n)}]^2
	// Z (m+n) = X (m-n) * [ "" - "" ] ^2
	start = clock();
	mpz_sub(TEMP_T,b->x,b->z);
	mpz_add(TEMP_R,a->x,a->z);
	mpz_mul(TEMP_PROD,TEMP_T,TEMP_R);
	mpz_mod(TEMP_PROD,TEMP_PROD,N); // is equal to first part of the equation

	mpz_add(TEMP_T,b->x,b->z);
	mpz_sub(TEMP_R,a->x,a->z);
	mpz_mul(GLOBAL_X,TEMP_T,TEMP_R);
	mpz_mod(GLOBAL_X,GLOBAL_X,N);

	mpz_add(TEMP_T,GLOBAL_X,TEMP_PROD);
	mpz_powm_ui(TEMP_T,TEMP_T,2,N);

	mpz_mul(c->x,one->z,TEMP_T);

	mpz_sub(TEMP_T,TEMP_PROD,GLOBAL_X);
	mpz_powm_ui(TEMP_T,TEMP_T,2,N);

	mpz_mul(c->z,one->x,TEMP_T);

	mpz_mod(c->x,c->x,N);
	mpz_mod(c->z,c->z,N);

	*a=c;
	end = clock();
	ADDITION_TIME+=(double)(end-start)/CLOCKS_PER_SEC;

}

int point_double(point *a) {
	
}

int point_multiplication(point *a, mpz_t b) {
	// sets A to bA
	// point c;
	// point_init(&c);
	// LINE
	clock_t aa = clock();
	while (mpz_cmp_ui(b,0)>0) {
		// LINE
		if (mpz_odd_p(b)!=0) {
			// printf("actual additon below\n");
			if (point_addition(&c,a,factor)>0) {
				// uhh this means uninvertible
				// factor has the factor
				return 1;
			}
		}   
		// point double
		point_addition(a,a,factor);
		mpz_tdiv_q_2exp(b,b,1);
		// ONCURVE(a)
	}
	*a = c;
	clock_t bb = clock();
	MULT_TIME+=(double)(bb-aa)/CLOCKS_PER_SEC;
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

	clock_t wtf = clock();
	point_init(&c);
	mpz_set(N,number);
	mpz_set_str(BOUND_A,"1000000",10);
	BOUND_A_LOG = (int) mpz_sizeinbase(BOUND_A,2);\
	BOUND_A_LOG--;
	mpz_set_ui(THREE,3);

	FILE *IN = fopen("PRIMES.txt","r");
	fscanf(IN,"%ld",&primes[0]);
	while (mpz_cmp_ui(BOUND_A,primes[PRIME_COUNT])>0) {
		PRIME_COUNT++;
		fscanf(IN,"%ld",&primes[PRIME_COUNT]);
	}
	PRIME_COUNT++;
	// choose random a and (x,y) for y^2 = x^3 + ax + b
	// set b = y^2-x^3-ax
	gmp_randstate_t state;

	gmp_randinit_mt(state);
	gmp_randseed_ui(state, (long) time(0));

	point p;
	point_init(&p);
	point_init(&c);

	mpz_t factor;
	mpz_init(factor);

	gmp_printf("N is %Zd\n",N);
	for (int i=0;i<NUMBER_OF_CURVES;i++) {
		//initialize p.x, p.y and x
		
		// LINE
		mpz_urandomm(CURVE_A,state,BOUND_A);
		mpz_urandomm(p.x,state,N);
		mpz_urandomm(p.y,state,N);
	
		mpz_powm_ui(TEMP_T,p.x,3,N);
		mpz_powm_ui(TEMP_R,p.y,2,N);
		mpz_mul(TEMP_PROD,CURVE_A,p.x);

		// LINE
		mpz_sub(TEMP_R,TEMP_R,TEMP_T);
		mpz_sub(TEMP_R,TEMP_R,TEMP_PROD);

		mpz_mod(CURVE_B,TEMP_R,N);
		assert(is_on_curve(&p)>0);
		
		// gmp_printf("CURVE IS: y^2 = x^3 + %Zdx + %Zd\n",CURVE_A,CURVE_B);

		// gmp_printf("BOUND_A %Zd\n",BOUND_A);

		//stage 1
		for (int j=0;j<PRIME_COUNT;j++) {
			// LINE
			mpz_set_si(GLOBAL_Y,primes[j]);
			mpz_pow_ui(GLOBAL_Y,GLOBAL_Y,highest_power(primes[j]));
			// LINE
			// gmp_printf("%Zd %Zd moved %Zd %d\n",p.x,p.y,GLOBAL_Y,primes[j]);

			if(point_multiplication(&p,GLOBAL_Y,factor)>0&&mpz_cmp(factor,N)!=0) {
				gmp_printf("Factor of %Zd is %Zd\n",N,factor);
				goto end;
			}
		}
		// stage 2 lol
		// Brent's birthday paradox contiuation, chooses r points such Q[j] (0<j<r) is randomly 2Q[j-1] or 3Q[j-1] and Q[0]=p
		time_t t;
		srand((unsigned) time(&t));

		point Q[10000];
		copy_point(&Q[0],&p);
	

		for (int j=1;j<BOUND_R;j++) {
			int DOUBLE = rand()%2;
			if (DOUBLE) {
				point_addition(&p,&p,factor);
				copy_point(&Q[j],&p);
			} else {
				point_multiplication(&p,THREE,factor);
				copy_point(&Q[j],&p);
			}
		}
		mpz_set_si(PROD_D,1);
		for (int j=0;j<BOUND_R;j++) {
			for (int k=j+1;k<BOUND_R;k++) {
				mpz_sub(TEMP_T,Q[j].y,Q[k].y);
				mpz_mul(PROD_D,PROD_D,TEMP_T);
				mpz_mod(PROD_D,PROD_D,N);
			}
		}
		mpz_gcd(factor,PROD_D,N);
		if (mpz_cmp_si(factor,0)!=0&&mpz_cmp(factor,N)!=0) {
			gmp_printf("Factor of %Zd is %Zd AAAAAASDJHASDJKASDJ\n",N,factor);
			goto end;
		}
		clock_t bro = clock();
		printf("ITeration %d and it took %lf\n",i+1,(double)(bro-wtf)/CLOCKS_PER_SEC);

	}
	
	
	end:	
		printf("aa\n");
		clock_t bruh = clock();
		printf("this took %lf time\n",(double)(bruh-wtf)/CLOCKS_PER_SEC);
		clear_all();
}
int main() {

	mpz_init_set_str(BOUND_A,"10000000",10);
	


	// init_all();
	// mpz_set_si(CURVE_B,3);
	// mpz_set_si(CURVE_A,2);

	// mpz_set_si(N,97);
	// point a,b;
	// point_init(&a);
	// point_init(&b);
	
	// mpz_set_si(a.x,0);
	// mpz_set_si(a.y,10);

	// mpz_set_si(b.x, 95);
	// mpz_set_si(b.y,31);

	// mpz_t fac;
	// mpz_init(fac);

	// // check(__LINE__);
	// // printf("point a is yes? on curve %d\n",is_on_curve(&b));
	// point_addition(&a,&b,fac);

	// gmp_printf("%Zd %Zd\n",a.x,a.y);

	mpz_t a,b;
	mpz_inits(a,b,NULL);
	// mpz_set_str(a,"5915587277",10);
	// mpz_set_ui(b,3267000013);
	LINE
	mpz_t test;
	// mpz_init(test);
	// mpz_init_set_str(test,"18197496879513753447134071421",10);
	mpz_init_set_str(test,"242735959",10);
	// mpz_mul(test,a,b);
	ECM(test);
	printf("%lf %lf %lf\n",MULT_TIME,ADDITION_TIME,SLOPE_TIME);

}
