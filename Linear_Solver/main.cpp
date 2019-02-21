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

	//// Initialising neccessary matrices
	//auto *A = new Matrix<double>(rows, cols, true);				// LHS A->
	//auto *A_t = new Matrix<double>(rows, cols, true);
	//auto *C = new Matrix<double>(rows, cols, true);
	//auto *L = new Matrix<double>(rows, cols, true);
	//auto *L_t = new Matrix<double>(rows, cols, true);
	//auto *U = new Matrix<double>(rows, cols, true);
	//auto *B = new Matrix<double>(1, 3, true);					// rhs  B->
	//auto *y = new Matrix<double>(B->num_rows, B->num_cols, true);
	//auto *x = new Matrix<double>(B->num_rows, B->num_cols, true); // Solution x->

	//// Load example case
	//A->mat_load('A');   // A is  LUD, A is non-symmetric		
	//C->mat_load('C');   // C is  Chol matrix

	//B->mat_load('B');   // B is [3, 2, 1]									
	//L->mat_load('L');   // L is  LUD, 'D' is Lower triangular identity		
	//x->fill_zeros();    // Setting up solution array with zeroes

	//std::cout << "Lower Upper Decomposition" << std::endl << "------------------" << std::endl;
	//class Solver eq_set_1; // LUD case
	//eq_set_1.A = A;
	//x->fill_zeros();
	//eq_set_1.x = x;
	//eq_set_1.B = B;
	//eq_set_1.LUD_solve();
	//eq_set_1.x->print();

	//std::cout << "Cholesky Decomposition" << std::endl << "------------------" << std::endl;
	//class Solver eq_set_2; // Cholesky case
	//eq_set_2.A = C;
	//x->fill_zeros();
	//eq_set_2.x = x;
	//eq_set_2.B = B;
	//eq_set_2.cholesky_solve();
	//eq_set_2.x->print();

	//std::cout << "Jacobi" << std::endl << "------------------" << std::endl;
	//class Solver eq_set_3; // Jacobi case
	//eq_set_3.A = A;
	//x->fill_zeros();
	//eq_set_3.x = x;
	//eq_set_3.B = B;
	//eq_set_3.jacobi_solve();
	//eq_set_3.x->print();

	//std::cout << "Gauss Seidel" << std::endl << "------------------" << std::endl;
	//class Solver eq_set_4; // Gauss Seidel case
	//eq_set_4.A = A;
	//x->fill_zeros();
	//eq_set_4.x = x;
	//eq_set_4.B = B;
	//eq_set_4.gauss_seidel_solve();
	//eq_set_4.x->print();

	//// Should swap all these out for smart pointers
	//delete A;
	//delete A_t;
	//delete C;
	//delete L;
	//delete L_t;
	//delete U;
	//delete B;
	//delete y;
	//delete x;

	system("pause");
}