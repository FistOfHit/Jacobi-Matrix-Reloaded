#include <iostream>
#include <math.h>
#include <time.h>
#include <assert.h>

#include "Matrix.h"
#include "Matrix.cpp"


void creation_tests() {
	// Lets test if we can create a matrix and then
	// allocate values to it that were allocated before.
	std::cout << "----------Test: Create pre-allocated matrix----------" << std::endl;

	// Manually allocating array
	int prealloc_test_array[25];
	for (int i = 0; i < 25; i++) { prealloc_test_array[i] = i + 1; }

	// Creating a matrix
	Matrix<int>test_matrix(5, 5, prealloc_test_array);

	std::cout << "Expected print out: " << std::endl << std::endl
		<< "Matrix 5 X 5" << std::endl
		<< "Data type: int" << std::endl
		<< "1 2 3 4 5" << std::endl
		<< "6 7 8 9 10" << std::endl
		<< "11 12 13 14 15" << std::endl
		<< "16 17 18 19 20" << std::endl
		<< "21 22 23 24 25" << std::endl;

	test_matrix.print();

	// Lets test if we can create an empty matrix
	// (full of zeros) and print it out
	std::cout << "----------Test: Create empty zeros matrix----------" << std::endl;

	// Creating a matrix
	Matrix<int>test_matrix_2(5, 5, true);

	std::cout << "Expected print out: " << std::endl << std::endl
		<< "Matrix 5 X 5" << std::endl
		<< "Data type: int" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl;

	test_matrix_2.print();
}


void run_tests() {
	creation_tests();
}


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


// Performs forwards substitution by reference
Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *B, Matrix<double> *y){
	assert(L->num_rows == L->num_cols);
	for (int i = 0; i < L-> num_rows; i++) {
		if (i == 0) {
			y->values[i] = B->values[i] / L->values[i  * L->num_rows + i];
		}
		else if (i != 0) {
			double s = 0;
			for (int j = 0; j < i; j++) {
				s += L->values[i * L->num_rows + j] * y->values[j];
			}
			y->values[i] = (1 / L->values[i * L->num_rows + i]) * (B->values[i] - s);
		}
	}
	return y;
}


// Performs backwards substutition by reference
Matrix<double>* backwards_substitution(Matrix<double> *U, Matrix<double> *y, Matrix<double> *x) {
	assert(U->num_rows == U->num_cols);
	for (int i = U->num_rows; i > -1; i--) {
		if (i == U->num_rows - 1) {
			x->values[U->num_rows - 1] = y->values[U->num_rows - 1] / U->values[i *  U->num_rows + i];
		}
		else if (i != U->num_rows) {
			double s = 0;
			for (int j = 0; j < U->num_cols; j++) {
				s += U->values[i* U->num_rows + j] * x->values[j];
			}
			x->values[i] = (1 / U->values[i* U->num_rows + i]) * (y->values[i] - s);
		}
	}
	return x;
}


int main() {
	int rows = 3;
	int cols = 3;

	//run_tests(); // If you want to run the tests

	// Performs Lower Upper decomposition using the Doolitle algorithm
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
	x->print();

	system("pause");
}