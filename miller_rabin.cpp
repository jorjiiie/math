#include <iostream>
#include <random>
#include <chrono>
// global variables bad but I don't want to keep creating random generators

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int TESTS=50; // idk clrs says this is good so i use it lol

long long fpow(long long a, long long b, long long m) {
	long long ret = 1LL;
	while(b) {
		// std::cout <<a  << " a\n";
		if (b&1) ret=ret*a%m;
		a=a*a%m;
		b>>=1;
	}
	// std::cout << ret%m << "\n";
	return ret%m;
}
bool test(long long a, long long n) {
	// decompose n-1 into 2^t*u
	long long t=0;
	long long n2 = n-1;
	while (!(n2&1)) t++,n2>>=1;
	// n2=u now;
	long long x;
	long long last = fpow(a,n2,n);
	for (int i = 0; i < t; i++) {
		x=last*last%n;
		if (x==1&&last!=1&&last!=n-1) {
			return true;
		}
		last=x;
	}
	if (last!=1) return true;
	return false;
}
bool miller_rabin(long long num, int tests) {

	std::uniform_int_distribution<> dist(1,num-1);
	for (int i = 0; i < tests; i++) {
		long long cur = dist(rng);
		if (test(cur,num)) return false;
	}
	return true; // likely
}
int main() {

	std::cout << miller_rabin(2000,TESTS);
}