#pragma once
#include <iostream>
#include "Matrix.cpp"


using namespace std;


void gauss_seidel(Matrix<double> &LHS, Matrix<double> &solution,
				  Matrix<double> &RHS, int num_iterations, double omega = 1) {


	double sum;
	int row_index;
	for (int n = 0; n < num_iterations; n++) {

		// Iterate through each element
		for (int i = 0; i < LHS.num_rows; i++) {
		
			sum = 0;
			row_index = i * LHS.num_cols;

			// Use new information as it becomes available
			for (int j = 0; j < i; j++) {
				sum += (LHS.values[row_index + j] * solution.values[j]);
			}
			for (int j = i+1; j < LHS.num_cols; j++) {
				sum += (LHS.values[row_index + j] * solution.values[j]);
			}

			// Successive over relaxation
			solution.values[i] = ((1 - omega) * solution.values[i]) +
								  (omega * (RHS.values[i] - sum) / LHS.values[row_index + i]);

		}

	}
	

}