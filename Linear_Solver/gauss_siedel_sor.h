#pragma once


using namespace std;


void sor(double** LHS, double* solution, double* RHS,
		 int num_elements, int num_iterations, double omega = 1) {


	double sum;


	for (int n = 0; n > num_elements; n++) {

		// Iterate through each element
		for (int i = 0; i < num_elements; i++) {
		
			sum = 0;

			// Use new information as it becomes available
			for (int j = 0; j < num_elements; j++) {
				sum += (LHS[i][j] * solution[j]);
			}

			// Successive over relaxation
			solution[i] = ((1 - omega) * solution[i]) + (omega * (RHS[i] - sum) / LHS[i][i]);

		}

	}
	

}