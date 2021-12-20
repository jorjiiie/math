#include "mint.h"


#define lc() std::cerr << "@: " << __LINE__ << "\n", std::fflush(stderr); 

mint::mint() {
	num.clear();
	sign = false;
}
mint::mint(std::string s) {
	num.clear();
	mint n = 0LL;
	for (char c : s) {
		n*=10;
		n+=(long long)(c-'0');
		std::cout << n << " " << c << " " << (c-'0') << " \n";
	}

	*this = n;
	std::cout << (*this) << " " << n << "\n";
}
mint::mint(long long n) {
	// this can be like pretty big
	if (n<0) {
		sign = true;
		n=-n;
	}
	num.clear();
	num.push_back(n&0x7FFFFFFF);

	if (n>>31) num.push_back(n>>31);

	// shouldn't have anything else after that
}

mint::mint(const char* c) {
	mint(std::string(c));
}
mint::mint(const mint& k) {
	this->num=k.num;
	this->sign=k.sign;
}

mint mint::operator+(const mint& k) {
	mint c = *this;
	c+=k;
	return c;
}
mint& mint::operator+=(const mint& k) {
	//pad the shorter one so they're the same length
	// hopefully this doesn't create memory leaks 
	mint tmp = k;
	// inefficient but I'm too lazy (for now) to impl a case for this and we just have the carry digit go over
	while (tmp.num.size()<this->num.size()) {
		tmp.num.push_back(0);
	}
	while (tmp.num.size()>this->num.size()) {
		this->num.push_back(0);
	}
	int n = tmp.num.size();
	int carry = 0;
	for (int i=0;i<n;i++) {
		// long is enuf
		unsigned int nxt = this->num[i]+tmp.num[i]+carry; 
		// max nxt can be is 4294967294
		carry=nxt>>31;
		// then we need to clear the 32nd bit always
		this->num[i]=nxt&0x7FFFFFFF;
	}
	if (carry) this->num.push_back(carry); // this should be ok!
	return *this;
}
mint mint::operator-(const mint& k) {
	mint c = *this;
	c-=k;
	return c;
}
mint& mint::operator-=(const mint& k) {
	// this is so annoying
	// essentially if opposite signs, then add them and adjust the sign accordingly
	// else, subtract the small one from the big one and make it negative
	if (k.sign ^ this->sign) {
		*this += k;
		return *this;
	}
	mint tmp1 = *this;
	mint tmp2 = k;
	tmp1.sign = false;
	tmp2.sign = false;
	if (tmp1 < tmp2) {
		std::swap(tmp1,tmp2);
		this->sign ^=1;
	}
	// tmp1 is the bigger one
	// now essentially same as addition
	tmp1.clean();
	tmp2.clean();
	int n = tmp1.num.size();
	for (int i=(n-tmp2.num.size());i;i--) {
		tmp2.num.push_back(0);
	}
	int carry = 0;
	for (int i=0;i<n;i++) {
		if (tmp1.num[i]+carry < tmp2.num[i]) {
			carry = -1;
			tmp1.num[i] -= (tmp2.num[i] - 2147483648LL);
		} else {
			if (carry) 
				tmp1.num[i]+=carry;
			tmp1.num[i]-=tmp2.num[i];
		}
	}
	this->num = tmp1.num;
	return *this;
}
mint mint::operator*(const mint& k) {
	mint c = *this;
	c*=k;
	return c;
}

mint& mint::operator*=(const mint& k) {
	// joe inefficient
	mint joe = 0LL;
	for (int i=0;i<this->num.size();i++) {
		for (int j=0;j<k.num.size();j++) {
			long long prod = (long long)(this->num[i])* 1LL * (long long)k.num[j];
			mint tmp = prod;
			tmp.shiftx(i+j);
			joe += tmp;
		}
	}
	this->sign ^= k.sign;
	*this = joe;
	return *this;

}
mint mint::operator/(const mint& k) {
	mint c = *this;
	c/=k;
	return c;
}
mint& mint::operator/=(const mint& k) {
	mint q,r;
	(*this).helper(k,q,r);
	*this = q;
	return *this;
}
mint mint::operator%(const mint& k) {
	mint c = *this;
	c%=k;
	return c;
}
mint& mint::operator%=(const mint& k) {
	mint q,r;
	(*this).helper(k,q,r);
	*this=r;
	return *this;
}
mint mint::operator+(const long long k) {
	mint c = *this;
	c+=k;
	return c;
}
mint& mint::operator+=(const long long k) {
	// do smth
	// LOL LAZY SOLUTION:
	mint tmp = k;
	*this+=tmp;
	return *this;
}
mint mint::operator*(const long long k) {
	mint c = *this;
	c*=k;
	return c;
}
mint& mint::operator*=(const long long k) {
	// do smth
	mint aa = k;
	return *this*=aa;
}
void mint::helper(const mint& divisor, mint& quotient, mint& remainder) {
	mint z = 0LL;
	mint x = *this;
	mint d = divisor;
	bool eq = d==z; // why do I have to do this cuz otherwise it says it'll get changed which is true but wtf
	assert(!eq && "DIVISION BY ZERO");

	if (x==z) {
		quotient = 0LL;
		remainder = 0LL;
		return;
	}
	mint current = 0LL;

	// if |x| < |divisor| then quotient = 0, remainder = x
	bool sign = (x.sign ^ d.sign);
	x.sign = false;
	d.sign = false;
	if (x<d) {
		

		quotient = 0LL;
		remainder = x;
		if (sign)
			remainder-=d;
		return;
	}
	d.clean();
	x.clean();
	
	for (int i= x.num.size()-1;i>=0;i--) {
		// uwu
		current.shiftx(1);


		current += (x.num[i]);

		if (current < d) {
			quotient.shiftx(1);
			continue;
		}
		// binary search it out uwu
		long long right = 2147483648LL;
		long long left = 1;
		long long fac = -1;
		while (left <= right) {
			long long mid = (right+left)/2;
			if (d*mid > current) {
				// bad

				right = mid-1;
			} else {
				left = mid+1;
				fac = mid;
			}
		}
		current -= (d*fac);
		assert (fac!=-1 && "wtf is goign on");
		quotient.shiftx(1);
		quotient += fac;
	}
	remainder = current;
	return;

}
mint mint::operator>>(const int k) {
	// right shift k bits
	// ABSOLUTELY NOT GOING BIT BY BIT
	// BUT IT WILL WORK FOR NOW :((((((((((
	mint c = *this;
	for (int i=0;i<this->num.size()*31;i++) {
		c.changeBit(i,this->num[i+k]);
	}
	return c;
}
bool mint::operator[](int k) {
	// access bit k
	if (k<0) return 0;
	if (k> 31*num.size()) return 0;
	int block = k/31;
	k-=(block*31);
	return num[block]&(1<<k);
}

mint::~mint() {
	num.clear();
}
bool mint::operator<(const mint& k) {
	return cmp(k)==-1;
}
bool mint::operator>(const mint&k) {
	return cmp(k)==1;
}
bool mint::operator<=(const mint& k) {
	int res = cmp(k);
	return res==-1||res==0;
}
bool mint::operator>=(const mint& k) {
	int res = cmp(k);
	return res==1||res==0;
}
bool mint::operator==(const mint& k) {
	return cmp(k)==0;
}
bool mint::operator!=(const mint& k) {
	return cmp(k)!=0;
}
int mint::cmp(const mint& k) {
	// clear out empty cells tho first?
	mint c = k;
	mint b = *this;
	b.clean();
	c.clean();
	if (b.num.size()<c.num.size()) return -1; // less
	if (b.num.size()>c.num.size()) return 1; // greater
	for (int i=b.num.size()-1;i>=0;i--) {
		if (b.num[i]<c.num[i]) return -1;
		if (b.num[i]>c.num[i]) return 1;
	}
	return 0;
}
void mint::changeBit(int k, bool b) {
	// will not check for oob 
	int block = k/31;
	k-=block*31;
	num[block]&=(~0&((int)b<<k));
}  
void mint::clean() {
	while (!(this->num.empty())&&this->num.back()==0) {
		this->num.pop_back();
	}
}
void mint::shiftx(int x) {
	// multiplies by base (2^31)
	if (x<0) {
		(*this).lshiftx(-x);
		return;
	}
	// add zeros at the front
	for (int i=0;i<x;i++)
		this->num.push_back(0);
	std::rotate(this->num.rbegin(), this->num.rbegin() + x, this->num.rend());
}
void mint::lshiftx(int x) {
	std::rotate(this->num.begin(),this->num.begin()+x, this->num.end());
	while ((x--)&&!this->num.empty()) {
		this->num.pop_back();
	}
}
std::string mint::baseten() {
	std::string uwu = "";
	mint zero = 0LL;
	mint tmp = *this;
	mint q,r;
	mint ten = 10;
	while (tmp > zero) {
		tmp.helper(ten,q,r);
		tmp = q;
		uwu += std::to_string(r.num[0]);
		q = r = zero;

	}
	std::reverse(uwu.rbegin(),uwu.rend());
	return uwu;

}
std::ostream& operator<<(std::ostream& stream, const mint& k) {
	// temporary lol
	for (unsigned int i : k.num) {
		stream << i << " ";
	}
	return stream;
}

void mint::set_str(const std::string& s) {
	num.clear();
	mint n = 0LL;
	for (char c : s) {
		n*=10;
		n+=(long long)(c-'0');
	}

	*this = n;
}
int main() {
	mint joe;
	joe.set_str("69420128397128937819272389473924723984");
	mint pork;
	pork.set_str("172812763816736182393179282748397824723947239482343");
	mint k = joe*pork;
	std::cout << "AJSKDLJAKLSD: " << joe*10LL << "\n";
	// return 0;
	std::cout << "num: " << k.baseten() << "\n";
}
