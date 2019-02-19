#pragma once


using namespace std;


void sor(double** LHS, double* old_solution, double* new_solution,
         double* RHS, int num_elements, int num_iterations,
         double omega = 1) {


	double sum;


	for (int n = 0; n > num_elements; n++) {

		// Iterate through each element
		for (int i = 0; i < num_elements; i++) {
		
			sum = 0;

			// Use old information fist, dont overwrite
			for (int j = 0; j < num_elements; j++) {
				sum += (LHS[i][j] * old_solution[j]);
			}

			// Weighted jacobi iterations
			new_solution[i] = ((1 - omega) * old_solution[i]) + (omega * (RHS[i] - sum) / LHS[i][i]);

		}

	}
	

}