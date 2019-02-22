#pragma once
#include <iostream>
#include "tests.h"
#include "generate_spd.h"
#include "Solvers.h"
#include "solve_custom.h"



// Print all options from start every time
void print_options() {

	std::cout << "--------------------------------------------" << std::endl
			  << "       The Jacobian Matrix: Reloaded        " << std::endl
		      << "--------------------------------------------" << std::endl << std::endl

		// Choices
		<< "Lets start by loading up the problem (A, the Left hand side matrix, and B, the Right hand side vector)." << std::endl << std::endl
		<< "You have the following choices: " << std::endl
		<< "1) Run our pre-defined tests for all of our solvers" << std::endl
		<< "2) Randomly create a N X N SPD matrix to test the solvers on" << std::endl
		<< "3) Enter your own A and b, element by element to solve" << std::endl
		<< "4) Close and quit" << std::endl << std::endl;

}


void make_choice() {

	print_options();

	bool re_print = true;
	while (re_print) {

		// Keep going until user quits
		re_print = true;

		// Prompt to user for input
		std::cout << "Please enter your choice (1, 2, 3 or 4): " << std::endl << std::endl;
		int choice;
		std::cin >> choice;

		// Switch board for various choices
		switch (choice) {

		case 1:

			system("cls");
			std::cout << "--------------------------------------------" << std::endl
					  << "       Running pre-defined test now!        " << std::endl
					  << "--------------------------------------------" << std::endl << std::endl;

			run_tests();

			print_options();
			break;

		case 2:

			system("cls");
			std::cout << "--------------------------------------------" << std::endl
					  << "  Lets create and solve our own SPD system! " << std::endl
					  << "--------------------------------------------" << std::endl << std::endl;

			// Prompt to user for input
			std::cout << "Please enter the size of square SPD left hand side matrix A you want: " << std::endl << std::endl;
			int spd_size;
			std::cin >> spd_size;

			generate_solve_spd(spd_size);

			print_options();
			break;

		case 3: {

			system("cls");
			std::cout << "--------------------------------------------" << std::endl
				 	  << "     Entering our own problem to solve      " << std::endl
				 	  << "--------------------------------------------" << std::endl << std::endl;

			// Get size of the matrix about to be typed up
			int problem_size;
			std::cout << "Enter size of the problem you want to write: " << std::endl
				<< "(LHS will be square and RHS will be a column vector of this size)" << std::endl;
			std::cin >> problem_size;

			// Create the problem
			Solver *custom_solver = create_custom_problem(problem_size);

			// Solve the problem
			solve_custom_problem(*custom_solver);

			print_options();
			break;
		}

		case 4:

			system("cls");
			std::cout << "--------------------------------------------" << std::endl
					  << "                   Goodbye!                 " << std::endl
					  << "--------------------------------------------" << std::endl << std::endl;

			re_print = false;
			break;

		default:

			system("cls");
			std::cout << std::endl
					 << "--------------------------------------------" << std::endl
					 << "Invalid choice. Please choose 1, 2, 3 or 4." << std::endl
					 << "--------------------------------------------" << std::endl << std::endl;
			print_options();
			break;

		}

	}
}