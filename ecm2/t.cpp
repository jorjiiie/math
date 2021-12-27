#include <iostream>
#include <algorithm>
#include <string>


#include <gmpxx.h>

// really got nothing today just doing college apps :(
using namespace std;

#define LINE printf("c: %d\n",__LINE__)



int main() {
	mpz_class a,b,c;
	a = 69;
	b = 69420;
	c = a*b*b*b*b*b*b*b;
	cout << c << "\n";

}