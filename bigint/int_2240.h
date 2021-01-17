#ifndef INT_2240
#define INT_2240

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

typedef long long ll; // we use base 2^31 with this I'm pretty sure


const int BASE = 2147483648;
const int BSHIFT = 31;

class int_2240 {
	private:
		ll number[70];
		bool sign; 
		static const int BASE = 2147483648;
		static const int BSHIFT = 31;
		
	public: 
		class badNumber {
			// intermediate base 10 for converting strings
			int n[1000]; // actual trash but ok!
			public:
				badNumber();
				badNumber(std::string);
				badNumber(const badNumber&);

				badNumber operator-() const;

				badNumber operator+(const badNumber&);
				badNumber& operator+=(const badNumber&);
				badNumber operator*(const badNumber&);
				badNumber& operator*=(const badNumber&);
				badNumber operator-(const badNumber&);
				badNumber& operator-=(const badNumber&);
				badNumber operator/(const badNumber&);
				badNumber& operator/=(const badNumber&);
   
				void print();
				void printraw();
		};
		int_2240();
		int_2240(ll l);
		int_2240(const int_2240&);
		int_2240(std::string);

		//addition
		int_2240 operator+(const int_2240&);


};
#endif