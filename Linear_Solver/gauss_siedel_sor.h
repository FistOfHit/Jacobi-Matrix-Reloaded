#pragma once
#include <iostream>


void gauss_seidel(double* LHS, double* solution, double* RHS,
				  int num_rows, int num_cols, int num_iterations,
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

			// Use new information as it becomes available
			for (int j = 0; j < num_cols; j++) {
				sum += (LHS[row_number + j] * solution[j]);
			}

			// Successive over relaxation
			solution[i] = ((1 - omega) * solution[i]) + (omega * (RHS[i] - sum) / LHS[row_number + i]);

		}

	}
	

}