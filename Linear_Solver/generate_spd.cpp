#pragma once
#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
#include "Solvers.h"
#include "generate_spd.h"


void print_solver_choices() {

	std::cout << "You have four solvers to choose from:" << std::endl
			  << "1) LU-decomposition based solver" << std::endl
			  << "2) Cholesky decomposition based solver" << std::endl
			  << "3) Iterative Jacobi solver" << std::endl
			  << "4) Iterative Gauss-seidel solver" << std::endl
			  << "5) Finished testing, return to main menu" << std::endl << std::endl;

}


void generate_solve_spd(int size) {

	std::cout << "----------Generating random SPD matrix and appropriate RHS with " << size << " rows and collumns----------" << std::endl;

	// LHS A
	auto *rand_spd_matrix = new Matrix<double>(size, size, true);

	// RHS b
	auto *rand_b = new Matrix<double>(1, size, true);

	// Empty solution vector
	auto *solution = new Matrix<double>(1, size, true);
	
	// Create matrix and solvers
	rand_spd_matrix->random_pdm(size);
	rand_b->random_B(1, size);
	class Solver generated_problem(rand_spd_matrix, rand_b, solution); // LUD case

	// What SPD matrix has been created
	std::cout << "----------SPD Left hand side matrix, A----------" << std::endl;
	std::cout << "Expected print out: " << std::endl
			  << "Matrix " << size << " X " << size << std::endl
			  << "Data type: double" << std::endl
			  << "RANDOMISED, SYMMETRIC MATRIX"<< std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	rand_spd_matrix->print();

	// What RHS has been created
	std::cout << "----------Right hand side vector, B----------" << std::endl;
	std::cout << "Expected print out: " << std::endl
		<< "Matrix 1 X " << size << std::endl
		<< "Data type: double" << std::endl
		<< "RANDOMISED ROW MATRIX" << std::endl << std::endl;
	std::cout << "Actual print out: " << std::endl;
	rand_b->print();
	
	// Call the solver choices for first time
	print_solver_choices();

	bool re_print = true;
	while (re_print) {

		// Keep going until user quits or choice is made
		re_print = true;

		// Prompt to user for input
		std::cout << "Please enter your choice (1, 2, 3, 4 or 5): " << std::endl << std::endl;
		int method;
		std::cin >> method;
		
		// Switchboard for methods to use
		switch (method) {

		case 1:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "       LU-decomposition based solver        " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			generated_problem.LUD_solve();
			generated_problem.x->print();
			return;

		case 2:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "     Cholesky decomposition based solver    " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			generated_problem.cholesky_solve();
			generated_problem.x->print();
			return;

		case 3:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "          Iterative Jacobi solver           " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			generated_problem.jacobi_solve();
			generated_problem.x->print();
			return;

		case 4:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "       Iterative Gauss-seidel solver        " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			generated_problem.gauss_seidel_solve();
			generated_problem.x->print();
			return;

		case 5:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "           returning to main menu           " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			re_print = false;
			break;

		default:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "Invalid choice. Please choose 1, 2, 3 or 4." << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;
			print_solver_choices();
			break;

		}

	}


} 
