#include <iostream>
#include <algorithm>
#include <string>


#include <gmpxx.h>

using namespace std;

int main() {
	mpz_class a,b,c;
	a = 69;
	b = 69420;
	c = a*b*b*b*b*b*b*b;
	cout << c << "\n";

}