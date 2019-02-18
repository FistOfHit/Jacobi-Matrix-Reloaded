#pragma once

using namespace std;


void restrict_down(double* fine_solution, int fine_size,
				   double* coarse_solution, int coarse_size) {


	// start and end values, special weighting
	coarse_solution[0] = (fine_solution[0] + 
						  fine_solution[1]) / 2;
	coarse_solution[coarse_size - 1] = (fine_solution[fine_size - 1] +
										fine_solution[fine_size - 1]) / 2;


	// All other values
	int interp_index;
	for (int i = 1; i < coarse_size - 1; i++) {

		interp_index = i + i - 1;

		coarse_solution[i] = (fine_solution[interp_index]     * 0.25) +
							 (fine_solution[interp_index + 1] * 0.5) +
							 (fine_solution[interp_index + 2] * 0.25);

	}


}