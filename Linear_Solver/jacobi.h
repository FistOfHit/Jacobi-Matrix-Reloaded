#pragma once
#include <iostream>
#include "Matrix.cpp"


void jacobi(Matrix<double> &LHS, Matrix<double> &solution,
            Matrix<double> &RHS, int num_iterations, double omega = (2.0/3.0)) {


	// Method valildty check
	if (LHS.num_rows != LHS.num_cols) {

		std::cout << "This method does not support rectangular matricies" << std::endl
			 << "Please consider either padding this array (array.pad(num_rows, num_cols))" << std::endl
			 << "or consider using QR factorisation" << std::endl
			 << "Exiting." << std::endl << std::endl;
		return;
	}

	// LHS-solution compatibility check
	if (LHS.num_cols != solution.num_rows) {

		std::cout << "Left hand side matrix with " << LHS.num_cols << " collumns"
			 << " not compatible with solution with " << solution.num_rows
			 << " elements." << std::endl
			 << "Exiting." << std::endl << std::endl;
		return;
	}

	// Solution-RHS compatibility check
	if (solution.num_rows != RHS.num_rows) {
		std::cout << "Solution with " << solution.num_rows << " elements"
			 << " not compatible with right hand side with " << RHS.num_rows
			 << " elements." << std::endl
			 << "Exiting." << std::endl << std::endl;
		return;
	}


	// Create array to store old solution for jacobi
	double *old_solution = new double[solution.num_rows];

	double sum;
	int row_index;
	for (int n = 0; n < num_iterations; n++) {
		for (int k = 0; k < solution.num_rows; k++) {
			old_solution[k] = solution.values[k];
		}

		// Iterate through each element
		for (int i = 0; i < LHS.num_rows; i++) {
			sum = 0;
			row_index = i * LHS.num_cols;

			// Use old information fist, dont overwrite
			for (int j = 0; j < i; j++) {
				sum += (LHS.values[row_index + j] * old_solution[j]);
			}
			for (int j = i+1; j < LHS.num_cols; j++) {
				sum += (LHS.values[row_index + j] * old_solution[j]);
			}

			// Weighted jacobi iteration
			solution.values[i] = ((1 - omega) * solution.values[i]) +
								 (omega * (RHS.values[i] - sum) / LHS.values[row_index + i]);
		}
	}
	delete[] old_solution;
}