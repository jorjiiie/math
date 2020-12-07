#ifndef ECM_H
#define ECM_H

#include <gmp.h>

typedef struct point {
	mpz_t x,y;
} point;

// initialize a point's mpz_t types
void point_init(point *p);

// modular inverse
int inverse(mpz_t a, mpz_t n, mpz_t x, mpz_t g);

// point addition on curve
int point_addition(point *a, point *b, mpz_t n, mpz_t factor);

// specialized point a + point b = point c where a=b
void point_double(point a, mpz_t n);

// binary multiplication on a curve
int point_mult(point a, point b, mpz_t n, mpz_t factor);

#endif