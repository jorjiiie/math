#include "mint.h"


#define lc() std::cout << "@: " << __LINE__ << "\n", std::fflush(stdout); 

mint::mint() {
	num.clear();
	sign = false;
}
mint::mint(std::string s) {
	num.clear();
	mint n;
	// go from lsd to msd
	std::reverse(s.begin(),s.end());
	for (char c : s) {
		n*=10;
		n+=(int)(c-'0');
	}
}
mint::mint(long long n) {
	// this can be like pretty big
	if (n<0) {
		sign = true;
		n=-n;
	}
	num.clear();

	if (n>>31) num.push_back(n>>31);
	num.push_back(n&0x7FFFFFFF);
	
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
	lc()
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
	lc()
	std::cout << "tmp1: " << tmp1 << "\n" << "tmp2: " << tmp2 << "\n";
	fflush(stdout);
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
	// for now we will impl a slow multiplication
	std::vector<std::pair<unsigned long long, unsigned long long> > tmp; // we have two so we can handle overflow better
	// it's essentially a two-leg 128 bit number

	// tmp.push_back(0);
	for (int i=0;i<this->num.size();i++) {
		for (int j=0;j<k.num.size();j++) {
			while (tmp.size()<1+i+j) {
				// make the size right
				tmp.push_back({0,0}); 
			}
			tmp[i+j].fi+=(unsigned long long)this->num[i]*k.num[j];
			tmp[i+j].se+=(tmp[i+j].fi)>>31;
			tmp[i+j].fi&=0x7FFFFFFF;
		}
	}
	// then do addition

	unsigned long long carry=0; 
	int current = 0;
	// realistically carry can be like really big so can't use int 
	for (int i=0;i<tmp.size();i++) {
		tmp[i].fi+=carry;
		carry = tmp[i].fi>>31;
		carry+=tmp[i].se;
		this->num[i]=(unsigned int) (tmp[i].fi&0x7FFFFFFF);
	}
	while (carry) {
		num.push_back(carry&0x7FFFFFFF);
		carry>>=31;
	}
	// always positive if they are the same sign and negative otherwise
	this->sign^=k.sign; 
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
		lc()
		// binary search it out uwu
		long long right = 2147483648LL;
		long long left = 1;
		long long fac = -1;
		lc()
		while (left <= right) {
			long long mid = (right+left)/2;
			std::cout << mid << " " << (d*mid) << " c:" << current << "\n";
			if (d*mid > current) {
				// bad

				right = mid-1;
			} else {
				left = mid+1;
				fac = mid;
			}
		}
		std::cout << "current is : " << current << " d*fac: " << (d*fac) << "\n";
		current -= (d*fac);
				std::cout << "current is : " << current << "\n";

		assert (fac!=-1 && "wtf is goign on");
		quotient.shiftx(1);
		quotient += fac;
		lc()
		std::cout << quotient << " " << current << " " << fac << "\n";
	}
	remainder = current;
	return;
	/*
	if (*this<k) { 
		// if its smaller then its zero
		this->num.clear();
		this->sign=false;
		return *this;
	}
	// algorithm is ripped off wikipedia
	mint c = k;
	c.clean();
	// this is already clean
	int n = this->num.size();
	int m = c.num.size();
	mint q=0,r;
	long long d;
	// initialize d (current) to first m-1 digits of n
	for (int i=0;i<m-1;i++) {
		r.num.push_back(this->.num[i]);
	}
	*/
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
int main() {
	lc()

	std::cout<<"HASDH\n";
	mint a = (1<<30);
	std::cout << a << "\n" << a[1] << "\n";
	mint b = (1<<30);
	mint c = a*b;
	mint k = 69;
	mint d = 58488;
	mint t = 10;
	c*=d;
	std::cout << c.baseten() << "\n";
	// std::cout << k*d << "\n";
	// std::cout << a%d << "\n";
	/*
	mint ajaj = c/t;
	mint abab = c%t;
	std::cout << "C: " << c << "\n";
	std::cout << "IMPORTANT: " << ajaj  << " + " << abab<< "\n";
	c.shiftx(1);
	std::cout << c << "\n";
	c.shiftx(-2);
	std::cout << c << "\n";
	*/
}
