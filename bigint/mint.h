#ifndef MINT
#define MINT

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

// macros lol
#define fi first
#define se second


class mint {
	private:
		std::vector<unsigned int> num;
		bool sign = false;
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

		// since division calculates both, we may as well have it like this
		void helper(const mint&, mint&, mint&);

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
		bool operator!=(const mint&);

		int cmp(const mint&);
		void changeBit(int, bool);
		void clean();

		mint slow_mult(const mint&);

		void shiftx(int);
		void lshiftx(int);

		std::string baseten();
		friend std::ostream& operator<< (std::ostream&, const mint&);
};

#endif
