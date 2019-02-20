#pragma once
#include <iostream>
#include "Matrix.cpp"


using namespace std;


void jacobi(Matrix<double> &LHS, Matrix<double> &solution,
            Matrix<double> &RHS, int num_iterations) {


	// Method valildty check
	if (LHS.num_rows != LHS.num_cols) {

		cout << "This method does not support rectangular matricies" << endl
			 << "Please consider either padding this array (array.pad(num_rows, num_cols))" << endl
			 << "or consider using QR factorisation" << endl
			 << "Exiting." << endl << endl;

		return;

	}

	// LHS-solution compatibility check
	if (LHS.num_cols != solution.num_rows) {

		cout << "Left hand side matrix with " << LHS.num_cols << " collumns"
			 << " not compatible with solution with " << solution.num_rows
			 << " elements." << endl
			 << "Exiting." << endl << endl;
		
		return;

	}

	// Solution-RHS compatibility check
	if (solution.num_rows != RHS.num_rows) {

		cout << "Solution with " << solution.num_rows << " elements"
			 << " not compatible with right hand side with " << RHS.num_rows
			 << " elements." << endl
			 << "Exiting." << endl << endl;

		return;

	}


	// Create array to store old solution for jacobi
	double *old_solution = new double[solution.num_rows];


	double sum;
	int row_number;
	for (int n = 0; n < num_iterations; n++) {


		for (int i = 0; i < solution.num_rows; i++) {
			old_solution[i] = solution.values[i];
		}


		// Iterate through each element
		for (int i = 0; i < LHS.num_rows; i++) {
		
			sum = 0;
			row_number = i * LHS.num_cols;

			// Use old information fist, dont overwrite
			for (int j = 0; j < LHS.num_cols; j++) {
				sum += (LHS.values[row_number + j] * old_solution[j]);
			}

			// jacobi iteration
			solution.values[i] = (RHS.values[i] - sum) / LHS.values[row_number + i];

		}


	}


	delete[] old_solution;
	
}