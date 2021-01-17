#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/*
 *Pretty bad wheel sieve
 * I'll implement this with doubly linked lists which should vastly improve performance
 * I used a set cuz I was lazy
 *
*/
typedef long long ll;

vector<ll> primes;
set<ll> wheel;
ll k,p,prod,BOUND,h;
int main() {

	primes.push_back(2);
	wheel.insert(1);

	ll N = 10000000;
	// cin >> N;
	k=1;
	p=3;
	prod=2;
	while (p*p<=N) {
		if (prod*p>prod)
			BOUND = min(N,prod*p);
		else BOUND = N;
		// 'roll out'
		// for every int we add prod until its bigger than N or p*prod
		// cout << BOUND << " " << prod << " " << wheel.size() << "\n";
		for (ll num : wheel) {
			if (num+prod<=BOUND) wheel.insert(num+prod);
			else break;
		}
		prod*=p;
		if (prod<0||prod>N) prod = N;
		// now remove all multiples of p
		h=p;
		while (h*p<=BOUND) {
			h = *wheel.upper_bound(h);
		}
		auto it = wheel.find(h);
		// auto it = wheel.find(BOUND/p); // i think this performes better
		while (*it > 1) {
			it--;
			wheel.erase((*it)*p);
		}
		// if (p==5) break;
		primes.push_back(p);
		p = *wheel.upper_bound(1);
	}
	for (ll num : wheel) primes.push_back(num);
	// primes.erase(1);
	// for (ll prime : primes) {
		// cout << prime << " ";
	// }
	cout << "\n" << primes.size()-1 << " primes\n";
}