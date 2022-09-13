#include <iostream>


// ONLY SQUARE MATRIX FOR NOW

template <class T, size_t N> 
class Matrix {
	private:
		int sz = N;
		T* nums[N];
	public:
		static constexpr double EPSILON = 0.0001;
		Matrix();
		Matrix<T, N> solve();
		T*& operator[](int);
		void print_mat();
		void set_mat(T*[]);
		void set_augment(T[]);
};

