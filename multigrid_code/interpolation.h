#pragma once

using namespace std;

void interpolate_up(double* fine_solution, int fine_size,
					double* coarse_solution, int coarse_size) {

	
	for (int i = 0; i < coarse_size; i++) {

		fine_solution[i + i] = coarse_solution[i];

	}

	for (int i = 1; i < coarse_size - 1; i += 2) {

		fine_solution[i] = (fine_solution[i - 1] + fine_solution[i + 1]) / 2;

	}

}