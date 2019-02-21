#include <iostream>
#include <math.h>
#include <time.h>
#include <assert.h>

#include "Matrix.h"
#include "Matrix.cpp"
#include "Solvers.h"


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


int main() {
	int rows = 3;
	int cols = 3;

	//run_tests(); // If you want to run the tests
	
	// Initialising neccessary matrices
	auto *A = new Matrix<double>(rows, cols, true);
	auto *A_t = new Matrix<double>(rows, cols, true);
	auto *C = new Matrix<double>(rows, cols, true);
	auto *L = new Matrix<double>(rows, cols, true);
	auto *L_t = new Matrix<double>(rows, cols, true);
	auto *U = new Matrix<double>(rows, cols, true);
	auto *B = new Matrix<double>(1, 3, true);
	auto *y = new Matrix<double>(B->num_rows, B->num_cols, true);
	auto *x = new Matrix<double>(B->num_rows, B->num_cols, true);

	// Load example case
	A->mat_load('A');   // A is  LUD, A is non-symmetric
	B->mat_load('B');   // B is [3, 2, 1]
	L->mat_load('L');   // L is  LUD, 'D' is Lower triangular identity


	// Example LUD case
	class Solver eq_set_1;
	eq_set_1.A = A;
	eq_set_1.x = x;
	eq_set_1.B = B;
	eq_set_1.LUD_solve();
	eq_set_1.x->print();

	// Example Cholesky case
	C->mat_load('C');   // C is  Chol matrix, summetric
	class Solver eq_set_2;
	eq_set_2.A = C;
	eq_set_2.x = x;
	eq_set_2.B = B;
	eq_set_2.cholesky_solve();
	eq_set_2.x->print();
	
	// Should swap all these out for smart pointers
	delete A;
	delete A_t;
	delete C;
	delete L;
	delete L_t;
	delete U;
	delete B;
	delete y;
	delete x;

	system("pause");
}