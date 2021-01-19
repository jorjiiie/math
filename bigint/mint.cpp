#include "mint.h"

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
mint mint::operator*(const mint& k) {
	mint c = *this;
	c*=k;
	return c;
}
mint& mint::operator*=(const mint& k) {
	// for now we will impl a slow multiplication, will be moved to its own method later
	std::vector<unsigned long long> tmp;
	// tmp.push_back(0);
	for (int i=0;i<this->num.size();i++) {
		for (int j=0;j<k.num.size();j++) {
			while (tmp.size()<1+i+j) {
				// make the size right
				tmp.push_back(0); 
			}
			tmp[i+j]+=(unsigned long long)this->num[i]*k.num[j];
		}
	}
	// then do addition

	unsigned long long carry=0; 
	// realistically carry can be like really big so can't use int 
	for (int i=0;i<tmp.size();i++) {
		tmp[i]+=carry;
		carry = tmp[i]>>31;
		this->num[i]=(unsigned int) (tmp[i]&0x7FFFFFFF);
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
	for (int i=0;i<=n-m;i++) {
		// r < 2^31
		d = r.num[0];
		d<<31; // shift over
		d+=this->num[i+m-1];
		// time to guess the divisor thing
		// essentially divisor can't be greater than 2^32 so it's ok to have ll but the product can be big so we should declare a big one
		// binary search ig
		long long HIGH = 1LL<<31;
		long long LOW = 0;
		long long MID = (HIGH+LOW)/2;
		while (HIGH>LOW) {
			mint prod = d*mid;
			if (prod>0) {
				// can try to be bigger
				LOW = MID+1;
			} else {
				HIGH = MID-1;
			}		
		}
		// 

}
mint mint::operator+(const long long k) {
	mint c = *this;

	return c;
}
mint& mint::operator+=(const long long k) {
	// do smth
	return *this;
}
mint mint::operator*(const long long k) {
	mint c = *this;

	return c;
}
mint& mint::operator*=(const long long k) {
	// do smth
	return *this;
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
bool mint::oeprator==(const mint& k) {
	return cmp(k)==0;
}
int cmp(const mint& k) {
	// clear out empty cells tho first?
	*this.clean();
	mint c = k;
	c.clean();
	if (this->num.size()<c.num.size()) return -1; // less
	if (this->num.size()>c.num.size()) return 1; // greater
	for (int i=this->num.size()-1;i>=0;i--) {
		if (this->num[i]<c.num[i]) return -1;
		if (this->num[i]>c.num[i]) return 1;
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
	while (this->num.back()==0&&!(this->num.empty())) {
		this->num.pop_back();
	}
}
std::ostream& operator<<(std::ostream& stream, const mint& k) {
	// temporary lol
	for (unsigned int i : k.num) {
		stream << i << " ";
	}
	return stream;
}
int main() {
	std::cout<<"HASDH\n";
	mint a = 34+(1LL<<34);
	std::cout << a << "\n" << a[1] << "\n";
	mint b = 200;
	mint c = a*b;
}
