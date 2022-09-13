#include "Matrix.hpp"

template <class T, size_t N>
Matrix<T, N>::Matrix() {
	// initialize all the thigns

	std::cout << sz << "\n";
	for (int i=0;i<sz;i++) {
		nums[i] = new T[sz+1];
	}

}
// returns this matrix LOL IM CRYING
// should probably return a deep copy but im too lazy for that rn
template <class T, size_t N>
Matrix<T, N> Matrix<T,N>::solve() {
	// perform gaussian elimination on this stuffz

	for (int i=0;i<sz;i++) {
		int good_row = -1;

		for (int j=i;j<sz;j++) {
			if (abs(nums[j][i]) > EPSILON) {
				good_row = j;
				break;
			}
		}
		if (good_row < i) {
			std::cout << "YIKES\n";
			return (*this);
		}

		std::swap(nums[good_row], nums[i]);

		// first divide out so pivot = 1
		for (int j=sz;j>=i;j--) {
			nums[i][j] /= nums[i][i];
		}
		// pivot across all
		for (int j=0;j<sz;j++) {
			if (j == i)
				continue;
			if (abs(nums[j][i]) > EPSILON) {
				// remove
				// std::cout << "using pivot as " << i << " and clearing out " << j << "\n";
				for (int k=sz;k>=i;k--) {
					nums[j][k] -= nums[i][k] * nums[j][i];
					if (k == sz) {
						// std::cout << nums[j][k] << " " << nums[i][k] << " " << nums[j][i] << " AJSHDLJASDLKASJDLKAJSD\n" ;
					}
				}
			}
		}
		print_mat();
		std::cout << "\n";

	}

	return (*this);
}

template <class T, size_t N>
void Matrix<T, N>::print_mat() {
	std::cout << "[";
	for (int i=0;i<sz;i++) {
		if (i)
			std::cout << " ";
		std::cout << "[ ";
		for (int j=0;j<sz+1;j++) {
			std::cout << nums[i][j] << " ";
		}
		std::cout << "]";
		if (i+1 < sz)
			std::cout << "\n";
	}
	std::cout << "]";
}

template <class T, size_t N>
void Matrix<T, N>::set_mat(T* mat[]) {
	for (int i=0;i<sz;i++) {
		for (int j=0;j<sz;j++) {
			nums[i][j] = mat[i][j];
		}
	}
}

template <class T, size_t N>
void Matrix<T, N>::set_augment(T augmented_col[]) {
	for (int i=0;i<sz;i++) {
		nums[i][sz] = augmented_col[i];
	}
}


int main() {
	Matrix<double, 3> mat;
	double* bb[3];
	for (int i=0;i<3;i++) {
		bb[i] = new double[3];
	}
	double a[] = {0,1,5};
	double b[] = {1,4,3};
	double c[] = {2,7,1};
	double sol[] = {4,-2,-2};
	bb[0] = a;
	bb[1] = b;
	bb[2] = c;
	mat.set_augment(sol);
	mat.set_mat(bb);
	mat.print_mat();
	std::cout << "\n";
	mat.solve();
	mat.print_mat();


}