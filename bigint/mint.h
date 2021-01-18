#ifndef MINT
#define MINT

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class mint {
	private:
		std::vector<unsigned int> num;
		bool sign;
		static const unsigned int base = 2147483648;
	public:
		mint();
		mint(const char*);
		mint(std::string);
		mint(long long);
		mint(const mint&);

		mint operator+(const mint&);
		mint& operator+=(const mint&);
		mint operator-(const mint&);
		mint& operator-=(const mint&);
		mint operator*(const mint&);
		mint& operator*=(const mint&);
		mint operator/(const mint&);
		mint& operator/=(const mint&);
		mint operator%(const mint&);
		mint& operator%=(const mint&);

		mint operator+(const long long);
		mint& operator+=(const long long);
		mint operator*(const long long);
		mint& operator*=(const long long);
		mint operator-(const long long);
		mint& operator-=(const long long);
		mint operator/(const long long);
		mint& operator/=(const long long);
		mint operator%(const long long);
		mint& operator%=(const long long);

		// for obvious reasons I'm not supporting this with anything beyond int
		mint operator>>(const int);
		mint& operator>>=(const int);
		mint operator<<(const int);
		mint& operator<<=(const int);

		// access bit at index
		bool operator[](int);

		~mint();

		bool operator<(const mint&);
		bool operator>(const mint&);
		bool operator<=(const mint&);
		bool operator>=(const mint&);
		bool operator==(const mint&);

		void changeBit(int, bool);

		mint slow_mult(const mint&);

		friend std::ostream& operator<< (std::ostream&, const mint&);
};

#endif