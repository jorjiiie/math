#include <iostream>

#include <time.h>

#include <gmp.h>
#include "mint.cpp"

mint zero = 0LL;
mint one = 1LL;
mint gcd(mint a, mint b) {
	if (b==zero)
		return a;
	return gcd(b, a%b);

}

mint prho(mint n) {
	mint x,y,d,diff; 
	long long k;
	int c = 1;
	for (;;) {
		long long cnt = 0;
		k = 2LL;
		x = 69; // seed
		y = x;
		for (;;) {
			cnt++;
			x = (x*x)+c;
			x%=n;
			if (y>x)
				diff = y-x;
			else
				diff = x-y;
			d = gcd(n,diff);
			if (d == n) {
				break;
			}
			if (d!=1) {
				return d;
			}
			if (k==cnt) {
				k*=2;
				y = x;
			}
		}
		c++;
	}
}

int main() {
	clock_t start = clock();
	mint ajaja = 399899999999999LL;
	mint bbbb;
	bbbb.set_str("19326223710861634601");
	mint kakaa = "19326223710861634";
	mint two = 2LL;

	std::cout << prho(kakaa/two) << "\n";
	clock_t end = clock();

	printf("took %lf seconds\n", (double) (end-start)/CLOCKS_PER_SEC);

	mpz_t joe;
	mpz_init(joe);
	mpz_set_str(joe,"118293012830",10);
	gmp_printf("num is %Zd\n",joe);

}