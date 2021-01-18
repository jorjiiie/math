#include "int_2240.h"
#include "badnum.cpp"

// constructors!
int_2240::int_2240() {
	sign = false;
}

int_2240::int_2240(ll x) {
	if (x<0) {
		sign = true;
		x=-x;
	} else {
		sign = false;
	}
}

int_2240::int_2240(std::string s) {
	badNumber a;
	if (s[0]=='-') {
		sign = true;
		a = s.substr(1);

	} else {
		sign = true;
		a = s;
	}
}