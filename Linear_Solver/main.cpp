#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.cpp"
#include "Solvers.h"
#include <assert.h>
#include "tests.h"

int main() {
	int rows = 3;
	int cols = 3;

	run_tests();

	// Initialising neccessary matrices
	auto *A = new Matrix<double>(rows, cols, true);				
	auto *C = new Matrix<double>(rows, cols, true);
	auto *B = new Matrix<double>(1, 3, true);					 
	auto *x = new Matrix<double>(B->num_rows, B->num_cols, true); 

	// Load example case
	A->mat_load('A');   // A is  LUD, A is non-symmetric		
	C->mat_load('C');   // C is  Chol matrix
	B->mat_load('B');   // B is [3, 2, 1]										
	x->fill_zeros();

	std::cout << "Lower Upper Decomposition" << std::endl << "------------------" << std::endl;
	class Solver eq_set_1(A, B, x); // LUD case
	eq_set_1.LUD_solve();
	eq_set_1.x->print();

	// Only works for symmetric matrices
	std::cout << "Cholesky Decomposition" << std::endl << "------------------" << std::endl;
	x->fill_zeros(); 
	class Solver eq_set_2(C, B, x); // Cholesky case 
	eq_set_2.cholesky_solve();
	eq_set_2.x->print();

	//// Should swap all these out for smart pointers
	delete A;
	delete C;
	delete B;
	delete x;

	system("pause");
}