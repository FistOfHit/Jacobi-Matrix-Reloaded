#pragma once
#include <iostream>


void jacobi(double* LHS, double* old_solution, double* new_solution,
            double* RHS, int num_rows, int num_cols, int num_iterations,
            double omega = 1) {


	// Method compatibility checks
	if (num_rows != num_cols) {

		std::cout << "This method does not support rectangular matricies" << std::endl
				  << "Please consider either padding this array (array.pad(num_rows, num_cols))" << std::endl
				  << "or consider using QR factorisation" << std::endl
				  << "Exiting." << std::endl;

		return;

	}


	double sum;
	int row_number;
	for (int n = 0; n > num_iterations; n++) {

		// Iterate through each element
		for (int i = 0; i < num_rows; i++) {
		
			sum = 0;
			row_number = i * num_cols;

			// Use old information fist, dont overwrite
			for (int j = 0; j < num_cols; j++) {
				sum += (LHS[row_number + j] * old_solution[j]);
			}

			// Weighted jacobi iterations
			new_solution[i] = ((1 - omega) * old_solution[i]) + (omega * (RHS[i] - sum) / LHS[row_number + i]);

		}

	}
	

}