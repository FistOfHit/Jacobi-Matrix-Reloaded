#pragma once
#include <iostream>
#include "tests.h"
#include "generate_spd.h"
#include "Solvers.h"


using namespace std;


// Print all options from start every time
void print_options() {

	cout << "--------------------------------------------" << endl
		 << "       The Jacobian Matrix: Reloaded        " << endl
		 << "--------------------------------------------" << endl << endl

		// Choices
		<< "Lets start by loading up the problem (A and B)." << endl << endl
		<< "You have the following choices: " << endl
		<< "1) Run our pre-defined tests for all of our solvers" << endl
		<< "2) Randomly create a N X N SPD matrix to test the solvers on" << endl
		<< "3) Enter your own A and b, element by element to solve" << endl
		<< "4) Close and quit" << endl << endl;

}


void make_choice() {

	print_options();

	bool re_print = true;
	while (re_print) {

		// Keep going until user quits
		re_print = true;

		// Prompt to user for input
		cout << "Please enter your choice (1, 2, 3 or 4): " << endl << endl;
		int choice;
		cin >> choice;

		// Switch board for various choices
		switch (choice) {

		case 1:

			cout << "--------------------------------------------" << endl
				 << "       Running pre-defined test now!        " << endl
				 << "--------------------------------------------" << endl << endl;

			run_tests();

			print_options();
			break;

		case 2:

			cout << "--------------------------------------------" << endl
				 << "  Lets create and solve our own SPD system! " << endl
				 << "--------------------------------------------" << endl << endl;

			// Prompt to user for input
			cout << "Please enter the size of square SPD left hand side matrix A you want: " << endl << endl;
			int spd_size;
			cin >> spd_size;

			generate_solve_spd(spd_size);

			print_options();
			break;

		case 3:

			cout << "Test 3";

			print_options();
			break;

		case 4:

			cout << "--------------------------------------------" << endl
				 << "                   Goodbye!                 " << endl
				 << "--------------------------------------------" << endl << endl;

			re_print = false;
			break;

		default:

			cout << endl
				 << "--------------------------------------------" << endl
				 << "Invalid choice. Please choose 1, 2, 3 or 4." << endl
				 << "--------------------------------------------" << endl << endl;
			print_options();
			break;

		}

	}
}