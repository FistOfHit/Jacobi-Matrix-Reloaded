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

	std::cout << "Jacobi Solver" << std::endl << "------------------" << std::endl;
	x->fill_zeros();				// Jacobi case
	eq_set_1.x = x;
	eq_set_1.jacobi_solve();
	eq_set_1.x->print();

	std::cout << "Gauss Seidel Solve" << std::endl << "------------------" << std::endl;
	x->fill_zeros();				// Gauss Seidel case
	eq_set_1.x = x;
	eq_set_1.gauss_seidel_solve();
	eq_set_1.x->print();

	// Only works for symmetric matrices
	std::cout << "Cholesky Decomposition" << std::endl << "------------------" << std::endl;
	x->fill_zeros(); 
	class Solver eq_set_2(C, B, x); // Cholesky case 
	eq_set_2.cholesky_solve();
	eq_set_2.x->print();

	int size = 8;
	std::cout << "Random Positive Definite Matrix of size:  " << size << std::endl << "------------------" << std::endl;
	auto *pdm = new Matrix<double>(size, size, true);
	pdm = eq_set_1.random_pdm(size);
	pdm->print();

	auto *B_rand = new Matrix<double>(size, size, true);
	B_rand = eq_set_1.random_B(1, size);
	std::cout << "Random RHS side:" << std::endl;
	B_rand->print();
	auto *x_new = new Matrix<double>(1, size, true);
	x_new->fill_zeros();
	class Solver random_test(pdm, B_rand, x_new);
	random_test.A->print();
	random_test.B->print();
	std::cout << "Solution:" << std::endl;
	random_test.LUD_solve();
	random_test.x->print();

	// Should swap all these out for smart pointers
	delete A;
	delete C;
	delete B;
	delete x;

	system("pause");
}