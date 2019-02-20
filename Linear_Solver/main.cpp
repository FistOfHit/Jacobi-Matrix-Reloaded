#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.h"
#include "Matrix.cpp"

int index_convert(int row_ind, int col_ind, int row_count) {
	return row_ind * row_count + col_ind;
}

int main() {
	std::cout << "Hello World";
	int rows = 3;
	int cols = 3;
	auto *A = new Matrix<double>(rows, cols, true);
	auto *L = new Matrix<double>(rows, cols, true);

	A->values[0] = 4;
	A->values[1] = 12;
	A->values[2] = -16;
	A->values[3] = 12;
	A->values[4] = 37;
	A->values[5] = -43;
	A->values[6] = -16;
	A->values[7] = -43;
	A->values[8] = 98;

	for (int i = 0; i < 9; i++) {
		L->values[i] = 0;
	}

	A->print();
	L->print();

	std::cout << "Cholesky decomposition" << std::endl;

	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < (i + 1); j++){
			double s = 0;
			for (int k = 0; k < j; k++) {
				s += (L->values[i * rows + k] * L->values[j * rows + k]);
			}
			if (i == j) {
				L->values[i * rows + j] = sqrt(A->values[i * rows + i] - s);
				}
			else{
				L->values[i * rows + j] = (1.0 / L->values[j * rows + j] * (A->values[i * rows + j] - s));
				}
		}
	}

	L->print();

	delete A;
	delete L;
	system("pause");
}