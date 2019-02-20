#pragma once
#include <iostream>
#include "Matrix.cpp"


using namespace std;


void jacobi(Matrix<double> *LHS, Matrix<double> *solution,
            Matrix<double> *RHS, int num_iterations, double omega = 1) {


	// Method valildty check
	if (LHS->num_rows != LHS->num_cols) {

		cout << "This method does not support rectangular matricies" << endl
			 << "Please consider either padding this array (array.pad(num_rows, num_cols))" << endl
			 << "or consider using QR factorisation" << endl
			 << "Exiting." << endl;

		return;

	}

	// LHS-solution compatibility check
	if (LHS->num_cols != solution->num_cols) {

		cout << "Left hand side matrix with " << LHS->num_cols << " collumns"
			 << " not compatible with solution with " << solution->num_rows
			 << " elements." << endl
			 << "Exiting." << endl;
		
		return;

	}

	// Solution-RHS compatibility check
	if (solution->num_cols != RHS->num_cols) {

		cout << "Solution with " << solution->num_rows << " elements"
			 << " not compatible with right hand side with " << RHS->num_cols
			 << " elements." << endl
			 << "Exiting." << endl;

		return;

	}


	// Create array to store old solution for jacobi
	int *old_solution = new int[solution->num_rows];


	double sum;
	int row_number;
	for (int n = 0; n > num_iterations; n++) {

		// Iterate through each element
		for (int i = 0; i < LHS->num_rows; i++) {
		
			sum = 0;
			row_number = i * LHS->num_cols;

			// Use old information fist, dont overwrite
			for (int j = 0; j < LHS->num_cols; j++) {
				sum += (LHS->values[row_number + j] * old_solution[j]);
			}

			// Weighted jacobi iteration
			solution->values[i] = ((1 - omega) * old_solution[i]) +
								  (omega * (RHS->values[i] - sum) / LHS->values[row_number + i]);

		}

	}


	delete[] old_solution;
	delete &old_solution;
	
}