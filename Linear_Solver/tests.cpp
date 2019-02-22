#pragma once
#include <iostream>
#include "Matrix.cpp"
#include "Solvers.h"
#include "tests.h"


void creation_tests() {

	// Lets test if we can create a matrix and then
	// allocate values to it that were allocated before.
	std::cout << "----------Test: Create pre-allocated matrix----------" << std::endl;

	// Manually allocating array
	int prealloc_test_array[25];
	for (int i = 0; i < 25; i++) { prealloc_test_array[i] = i + 1; }

	// Creating a matrix
	Matrix<int>test_matrix1(5, 5, prealloc_test_array);
	std::cout << "Expected print out: " << std::endl
		<< "Matrix 5 X 5" << std::endl
		<< "Data type: int" << std::endl
		<< "1 2 3 4 5" << std::endl
		<< "6 7 8 9 10" << std::endl
		<< "11 12 13 14 15" << std::endl
		<< "16 17 18 19 20" << std::endl
		<< "21 22 23 24 25" << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_matrix1.print();

	// Lets test if we can create an empty matrix
	// (full of zeros) and print it out
	std::cout << "----------Test: Create empty zeros matrix----------" << std::endl;

	// Creating a matrix
	Matrix<int>test_matrix2(5, 5, true);
	std::cout << "Expected print out: " << std::endl << std::endl
		<< "Matrix 5 X 5" << std::endl
		<< "Data type: int" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl
		<< "0 0 0 0 0" << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_matrix2.print();
}

void iterative_solver_tests() {

	// Create a LHS A
	Matrix<double> test_LHS(4, 4, true);
	test_LHS.set_value(0, 0, 10);
	test_LHS.set_value(0, 1, -1);
	test_LHS.set_value(0, 2, 2);
	test_LHS.set_value(0, 3, 0);
	test_LHS.set_value(1, 0, -1);
	test_LHS.set_value(1, 1, 11);
	test_LHS.set_value(1, 2, -1);
	test_LHS.set_value(1, 3, 3);
	test_LHS.set_value(2, 0, 2);
	test_LHS.set_value(2, 1, -1);
	test_LHS.set_value(2, 2, 10);
	test_LHS.set_value(2, 3, -1);
	test_LHS.set_value(3, 0, 0);
	test_LHS.set_value(3, 1, 3);
	test_LHS.set_value(3, 2, -1);
	test_LHS.set_value(3, 3, 8);

	// Create a RHS b
	Matrix<double> test_RHS(4, 1, true);
	test_RHS.set_value(0, 0, 6);
	test_RHS.set_value(1, 0, 25);
	test_RHS.set_value(2, 0, -11);
	test_RHS.set_value(3, 0, 15);

	std::cout << "----------Test: Jacobi iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if jacobi with omega = 1 converges
	Matrix<double> test_jac_sol(4, 1, true);

	class Solver test_solver(&test_LHS, &test_RHS, &test_jac_sol);
	test_solver.jacobi_solve();

	// See if it matches reality
	std::cout << "Expected print out: " << std::endl
		<< "Matrix 4 X 1" << std::endl
		<< "Data type: double" << std::endl
		<< 1 << std::endl
		<< 2 << std::endl
		<< -1 << std::endl
		<< 1 << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_solver.x->print();

	std::cout << "----------Test: Gauss-seidel iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if gauss-seidel with omega = 1 converges
	Matrix<double> test_gs_sol(4, 1, true);

	test_solver.x = &test_gs_sol;
	test_solver.gauss_seidel_solve();

	// See if it matches reality
	std::cout << "Expected print out: " << std::endl
		<< "Matrix 4 X 1" << std::endl
		<< "Data type: double" << std::endl
		<< 1 << std::endl
		<< 2 << std::endl
		<< -1 << std::endl
		<< 1 << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_solver.x->print();

	std::cout << "----------Test: Successive over-relaxation (SOR) iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if gauss-seidel with omega = 1.5 converges (SOR)
	Matrix<double> test_sor_sol(4, 1, true);
	test_solver.x = &test_sor_sol;
	// If the omega parameter is set higher instablility occurs
	test_solver.gauss_seidel_solve(1.5);
	// See if it matches reality

	std::cout << "Expected print out: " << std::endl
		<< "Matrix 4 X 1" << std::endl
		<< "Data type: double" << std::endl
		<< 1 << std::endl
		<< 2 << std::endl
		<< -1 << std::endl
		<< 1 << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_solver.x->print();
}


void direct_solver_tests() {


	int rows = 3;
	int cols = 3;

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

	std::cout << "----------LU-decomposition based solver----------" << std::endl;
	std::cout << "Expected print out: " << std::endl
		   	  << "Matrix 1 X 3" << std::endl
			  << "Data type: double" << std::endl
			  << "8.125 3.25 5" << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	class Solver eq_set_1(A, B, x); // LUD case
	eq_set_1.LUD_solve();
	eq_set_1.x->print();

	// Only works for symmetric matrices
	std::cout << "----------Cholesky decomposition based solver----------" << std::endl;
	std::cout << "Expected print out: " << std::endl
			  << "Matrix 1 X 3" << std::endl
			  << "Data type: double" << std::endl
			  << "123.083 -33.6667 5.33333" << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	x->fill_zeros();
	class Solver eq_set_2(C, B, x); // Cholesky case 
	eq_set_2.cholesky_solve();
	eq_set_2.x->print();

	// Should swap all these out for smart pointers
	delete A;
	delete C;
	delete B;
	delete x;

}

void run_tests() {
	creation_tests();
	iterative_solver_tests();
	direct_solver_tests();
}