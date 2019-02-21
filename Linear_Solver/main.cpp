#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.cpp"
#include "jacobi.h"
#include "gauss_siedel_sor.h"
#include <assert.h>
#include "tests.h"

// Performs Cholesky decomposition by reference
Matrix<double>* form_cholesky(Matrix<double> *A, Matrix<double> *L) {
	assert(A->num_rows == A->num_cols);
	for (int i = 0; i < A->num_rows; i++) {
			for (int j = 0; j < (i + 1); j++){
				double s = 0;
				for (int k = 0; k < j; k++) {
					s += (L->values[i * A->num_rows + k] * L->values[j * A->num_rows + k]);
				}
				if (i == j) {
					L->values[i * A->num_rows + j] = sqrt(A->values[i * A->num_rows + i] - s);
					}
				else{
					L->values[i * A->num_rows + j] = (1.0 / L->values[j * A->num_rows + j] * (A->values[i * A->num_rows + j] - s));
					}
			}
		}
	return L;
}


void form_LUD(Matrix<double> *A, Matrix<double> *U, Matrix<double> *L) {
	assert (A->num_rows == A->num_cols);
	for (int j=0; j < A->num_cols; j++){
		for (int i = 0; i < j + 1; i++) {
			double s1 = 0;

			for (int k = 0; k < i; k++) {
				s1 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			U->values[i * A->num_rows + j] = A->values[i * A->num_rows + j] - s1;
		}
		for (int i = j; i < A->num_cols; i++){
			double s2 = 0;
				for (int k=0; k<j; k++){
					s2 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
				}
				L->values[i * A->num_rows + j] = (A->values[i * A->num_rows + j] - s2) / U->values[j * A->num_rows + j];
		}
	}
}


int main() {


	//int rows = 3;
	//int cols = 3;

	//// Performs Lower Upper decomposition using the Doolitle algorithm
	//// Initialising neccessary matrices
	//auto *A = new Matrix<double>(rows, cols, true);
	//auto *C = new Matrix<double>(rows, cols, true);
	//auto *L = new Matrix<double>(rows, cols, true);
	//auto *U = new Matrix<double>(rows, cols, true);
	//auto *y = new Matrix<double>(1, 3, true);
	//auto *B = new Matrix<double>(1, 3, true);
	//auto *x = new Matrix<double>(1, 3, true);

	//// Load example case
	//A->mat_load('A'); // A is  LUD, A is non-symmetric
	//C->mat_load('B'); // C is  LUD, B is lower Cholesky decomposiiton
	//U->mat_load('C'); // U is  LUD, B is Upper triangular Empty
	//L->mat_load('D'); // L is  LUD, D is Lower triangular identity
	//B->mat_load('F'); // B is [3, 2, 1]
	//y->mat_load('E'); // y is empty (1, 3)
	//x->mat_load('E'); // x is empty (1, 3)
	//
	////L = form_cholesky(C, L);   /////////////// Need to write transpose to implement this

	//// Decompose into upper and lower triagular matrices
	//form_LUD(A, U, L); 
	//// Forward substitution
	//y = forward_substitution(L, B, y);
	//// Backward substitution
	//x = backwards_substitution(U, y, x);
	//// Show solution
	//x->print();

	// If you want to run the tests
	run_tests();

	system("pause");


}