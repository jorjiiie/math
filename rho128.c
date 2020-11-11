/*
 * Ryan Zhu
 * Basic implementation of Pollard's Rho factoring algorithm, utilizing Brent's cycle modification and a gcd optimization to increase speed
 * Supports factoring integers ~ 1e19 since 2^128 is 3e38, it will overflow in calculating f(x) = x^2 + c
 * I wrote a modular multiplication which does multiplication by doubling, but it's far too slow and utilizing GMP arbitrary precision numbers is faster for anything above, which goes against the point of using 128 bit integers in the first place
 * The log(n) factor of modular multiplication significantly increases the runtime, making the algorithm logn*n^(1/4) (assuming arithmatic is O(1)), which is not practical for numbers on the order of 1e30
 * Improvements can obviously be made, but I'm probably going to implement ECM and the Quadratic Sieve anyways with GMP, so it wouldn't be that helpful
 * GCD optimizations are a constant factor optimization, but in testing in my GMP implementation there was a ~100x difference in speed difference multiplication and gcd operations, and the optimized times were anywhere from the same or slower (on small inputs) to 10x faster
 * Choice of log2(n) for the GCD "trade" is so that we can still factor small numbers, i.e. a number like 25 will introduce its square root 5 many times within the first 10 numbers generated
*/

#include <stdio.h>

#ifndef HAVE_int128
#define HAVE_int128
typedef __int128 int128_t;
#endif

void print128(__int128 n) {
	if (n==0) return;
	print128(n/10);
	printf("%c",(char)('0'+(n%10)));
}
void print_int128(__int128 n) {
	if (n==0) printf("0");
	else print128(n);
}


int128_t modmul(int128_t a, int128_t b, int128_t n) {
	int128_t i,sum=0;
	for (i=b;i;i>>=1) {
		if (i&1) {
			sum+=a;
			if (sum>n) sum-=n;
		}
		a<<=1;
		if (a>n)a-=n;
	}
	return sum;
}

int128_t gcd(int128_t a, int128_t b) {
	int shift = 0;
	int128_t tmp;
	while (!(a&1||b&1)) {
		a>>=1;
		b>>=1;
		shift++;
	}
	while (b!=0) {
		tmp = b;
		b = a%b;
		a=tmp;
	}

	return (a<<shift);
}
int128_t int128_prho(int128_t n) {
	int128_t x,y,d,acumulate,divide;
	int k=0,m=1,c=1;

	// do a gcd operation every log2(n) numbers generated instead of every time
	int REP_LIMIT=1;
	int128_t cp = n,one=1;
	while (cp>0) REP_LIMIT++,cp>>=1;
	while(1) {
		x=y=acumulate=1;

		while (1) {
			for (int i=0;i<REP_LIMIT;i++) {
				x=(x*x+c)%n;
				d=x-y;
				if (d<0) d=-d;
				if (d==0) break;
				acumulate=acumulate*d;
				acumulate%=n;
				if (k>=m) {
					m<<=1;
					y=x;
				}
				k++;
			}
			
			divide = gcd(acumulate,n);
			if (divide==n) break;
			if (divide!=1) return divide;
			if (d==0) break;
			acumulate=1;
		}
		printf("again\n");
		c++;
	}
}
int main() {

	int128_t a,b,c;
	a = 193707721;
	b = 193818613;
	c = int128_prho(a*b);
	print128(c);	
}