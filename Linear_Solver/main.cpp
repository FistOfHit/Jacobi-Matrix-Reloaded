#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.cpp"
#include "Solvers.h"
#include "jacobi.h"
#include "gauss_siedel_sor.h"
#include <assert.h>
#include "tests.h"

int main() {
	int rows = 3;
	int cols = 3;

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

	//run_tests();
	system("pause");
}