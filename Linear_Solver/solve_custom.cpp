#pragma once
#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
#include "Solvers.h"


void print_custom_solver_choices() {

	std::cout << "You have four solvers to choose from:" << std::endl
		<< "1) LU-decomposition based solver" << std::endl
		<< "2) Cholesky decomposition based solver" << std::endl
		<< "3) Iterative Jacobi solver" << std::endl
		<< "4) Iterative Gauss-seidel solver" << std::endl
		<< "5) Iterative Successive Over-relaxation solver" << std::endl
		<< "6) Finished testing, return to main menu" << std::endl << std::endl;

}


Solver* create_custom_problem(int size) {

	// Initialise matrix object
	auto* custom_LHS = new Matrix<double>(size, size, true);
	custom_LHS->read_LHS(size);
	custom_LHS->print();

	// Initialise RHS vector
	auto* custom_RHS = new Matrix<double>(size, 1, true);
	custom_RHS->read_RHS(size);
	custom_RHS->print();

	// Initialise solution
	auto* solution  = new Matrix<double>(size, 1, true);

	// Create the solver itself now and return
	auto *loaded_solver = new Solver(custom_LHS, custom_RHS, solution);
	return loaded_solver;

}

void solve_custom_problem(Solver &loaded_solver) {

	// Call the solver choices for first time
	print_custom_solver_choices();

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

			loaded_solver.LUD_solve();
			loaded_solver.x->print();
			return;

		case 2:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "     Cholesky decomposition based solver    " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			loaded_solver.cholesky_solve();
			loaded_solver.x->print();
			return;

		case 3:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "          Iterative Jacobi solver           " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			loaded_solver.jacobi_solve(0.0);
			loaded_solver.x->print();
			return;

		case 4:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "       Iterative Gauss-seidel solver        " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			loaded_solver.gauss_seidel_solve();
			loaded_solver.x->print();
			return;

		case 5:

			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "Iterative Successive over-relaxation solver " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			loaded_solver.gauss_seidel_solve(1.8);
			loaded_solver.x->print();
			return;

		case 6:

			system("cls");
			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "           returning to main menu           " << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;

			re_print = false;
			break;

		default:

			system("cls");
			std::cout << std::endl
				<< "--------------------------------------------" << std::endl
				<< "Invalid choice. Please choose 1, 2, 3 or 4." << std::endl
				<< "--------------------------------------------" << std::endl << std::endl;
			print_custom_solver_choices();
			break;
		}
	}
	delete loaded_solver.A;
	delete loaded_solver.B;
	delete loaded_solver.x;
	delete &loaded_solver;
}