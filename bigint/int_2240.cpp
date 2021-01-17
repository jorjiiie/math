#include "int_2240.h"

// handles string conversion
int_2240::badNumber::badNumber() {
	for (int i=0;i<1000;i++) n[i]=0;
}
int_2240::badNumber::badNumber(std::string s) {
	for (int i=0;i<1000;i++) n[i]=0;
	std::reverse(s.begin(),s.end());
	for (int i=s.length()-1;i>=0;i--) {
		n[i]=s[i]-'0';
	}
}
int_2240::badNumber::badNumber(const badNumber& b) {
	for (int i=0;i<1000;i++) n[i]=b.n[i];
}

int_2240::badNumber int_2240::badNumber::operator-() const {
	badNumber r = *this;
	for (int i=0;i<1000;i++) {
		r.n[i]=-r.n[i];
	}
	return r;
}
// actual pain lol
int_2240::badNumber int_2240::badNumber::operator+(const badNumber& o) {
	// now we just go through digits;
	badNumber c = *this;
	c+=o;
	return c;
}
int_2240::badNumber& int_2240::badNumber::operator+=(const badNumber& o) {
	int carry = 0;
	for (int i=0;i<1000;i++) {
		this->n[i]+=(o.n[i]+carry);
		carry=this->n[i]/10;
		this->n[i]%=10;
	}
	assert(carry==0);
	return *this;
}
//multiplication
int_2240::badNumber int_2240::badNumber::operator*(const badNumber& o) {
	badNumber c;
	// LOL n*n MULTIPLICATION TIME!!!
	for (int i=0;i<500;i++) { // can't handle more than 500 LOL!!!!!!!!!!!!
		for (int j=0;j<500;j++) {
			c.n[i+j]+=this->n[i]*o.n[j];
			// this should work lmao
		}
	}
	int	carry=0;
	for (int i=0;i<1000;i++) {
		c.n[i]+=carry;
		carry=c.n[i]/10;
		c.n[i]%=10;
	}
	return c;
}
int_2240::badNumber& int_2240::badNumber::operator*=(const badNumber& o) {
	*this = *this * o;
	return *this;
}

int_2240::badNumber int_2240::badNumber::operator-(const badNumber& o) {
	badNumber c = *this;
	return c-=o;
}
int_2240::badNumber& int_2240::badNumber::operator-=(const badNumber& o) {
	int carry = 0;
	for (int i=0;i<1000;i++) {
		// add 10 and if its bad we carry the negative?
		this->n[i]+=carry;
		this->n[i]-=o.n[i];
		if (this->n[i]<0) {
			carry = -1;
			this->n[i]+=10;
		} else {
			carry = 0;
		}
	}
	return *this;
}
void int_2240::badNumber::print() {
	bool on = false;
	for (int i=999;i>=0;i--) {
		if (on||n[i]!=0){
			on=true;
			std::cout << n[i];
		}
	} 
	std::cout << "\n";
	return;
}
void int_2240::badNumber::printraw() {
	for (int i=0;i<1000;i++) {
		std::cout << n[i];
	}
	std::cout << "\n";
}


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