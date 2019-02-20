#include <iostream>
#include <math.h>
#include <time.h>
#include <assert.h>

#include "Matrix.h"
//#include "Solvers.h"
#include "Matrix.cpp"


// Performs Cholesky decomposition by reference
Matrix<double>* form_cholesky(Matrix<double> *A, Matrix<double> *L) {
	assert(A->rows == A->cols);
	for (int i = 0; i < A->rows; i++) {
			for (int j = 0; j < (i + 1); j++){
				double s = 0;
				for (int k = 0; k < j; k++) {
					s += (L->values[i * A->rows + k] * L->values[j * A->rows + k]);
				}
				if (i == j) {
					L->values[i * A->rows + j] = sqrt(A->values[i * A->rows + i] - s);
					}
				else{
					L->values[i * A->rows + j] = (1.0 / L->values[j * A->rows + j] * (A->values[i * A->rows + j] - s));
					}
			}
		}
	return L;
}


// Performs Lower Upper decomposition using the Doolitle algorithm
void form_LUD(Matrix<double> *A, Matrix<double> *U, Matrix<double> *L) {
	assert (A->rows == A->cols);
	for (int j=0; j < A->cols; j++){
		for (int i=0; i < j + 1; i++){
			double s1 = 0;

			for (int k = 0; k < i; k++) {
				s1 += U->values[k * A->rows + j] * L->values[i * A->rows + k];
			}
			U->values[i * A->rows + j] = A->values[i * A->rows + j] - s1;
		}

		for (int i = j; i < A->cols; i++){
			double s2 = 0;
				for (int k=0; k<j; k++){
					s2 += U->values[k * A->rows + j] * L->values[i * A->rows + k];
				}

				L->values[i * A->rows + j] = (A->values[i * A->rows + j] - s2) / U->values[j * A->rows + j];
		}
	}
	// Could return an struct of pointers that point to new L and new U
}


// Performs forwards substitution by reference
Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *B, Matrix<double> *y){
	assert(L->rows == L->cols);
	for (int i = 0; i < L->rows; i++) {
		if (i == 0) {
			y->values[i] = B->values[i] / L->values[i  * L->rows + i];
		}
		else if (i != 0) {
			double s = 0;
			for (int j = 0; j < i; j++) {
				s += L->values[i * L->rows + j] * y->values[j];
			}
			y->values[i] = (1 / L->values[i * L->rows + i]) * (B->values[i] - s);
		}
	}
	return y;
}


// Performs backwards substutition by reference
Matrix<double>* backwards_substitution(Matrix<double> *U, Matrix<double> *y, Matrix<double> *x) {
	assert(U->rows == U->cols);
	for (int i = U->rows; i > -1; i--) {
		if (i == U->rows - 1) {
			x->values[U->rows - 1] = y->values[U->rows - 1] / U->values[i *  U->rows + i];
		}
		else if (i != U->rows) {
			double s = 0;
			for (int j = 0; j < U->cols; j++) {
				s += U->values[i* U->rows + j] * x->values[j];
			}
			x->values[i] = (1 / U->values[i* U->rows + i]) * (y->values[i] - s);
		}
	}
	return x;
}


int main() {
	int rows = 3;
	int cols = 3;

	// Initialising neccessary matrices
	auto *A = new Matrix<double>(rows, cols, true);
	auto *C = new Matrix<double>(rows, cols, true);
	auto *L = new Matrix<double>(rows, cols, true);
	auto *U = new Matrix<double>(rows, cols, true);
	auto *y = new Matrix<double>(1, 3, true);
	auto *B = new Matrix<double>(1, 3, true);
	auto *x = new Matrix<double>(1, 3, true);

	// Load example case
	A->mat_load('A'); // A is  LUD, A is non-symmetric
	C->mat_load('B'); // C is  LUD, B is lower Cholesky decomposiiton
	U->mat_load('C'); // U is  LUD, B is Upper triangular Empty
	L->mat_load('D'); // L is  LUD, D is Lower triangular identity
	B->mat_load('F'); // B is [3, 2, 1]
	y->mat_load('E'); // y is empty (1, 3)
	x->mat_load('E'); // x is empty (1, 3)
	
	//L = form_cholesky(C, L);   /////////////// Need to write transpose to implement this

	// Decompose into upper and lower triagular matrices
	form_LUD(A, U, L); 
	// Forward substitution
	y = forward_substitution(L, B, y);
	// Backward substitution
	x = backwards_substitution(U, y, x);
	// Show solution
	x->printMatrix();

	system("pause");
}