#pragma once
#include <iostream>
#include "Solvers.h"
#include "Matrix.h"
#include "Matrix.cpp"
#include <assert.h>
#include <algorithm>


// Transpose any matrix
Matrix<double>* Solver::transpose(Matrix<double> *A) {
	auto *A_t = new Matrix<double>(A->num_rows, A->num_cols, true);

	// Iterate through elements, swapping
	for (int i = 0; i < A->num_rows; i++) {
		for (int j = 0; j < A->num_cols; j++) {
			A_t->values[j * A->num_rows + i] = A->values[i* A->num_rows + j];
		}
	}
	return A_t;
}

// Checks if inputs are actually valid fror the defined
// problem before solver proceeds
void Solver::check_input_validity() {

	// Method valildty check
	if (A->num_rows != A->num_cols) {

		std::cout << "This method does not support rectangular matricies" << std::endl
			<< "Please consider either padding this array (array.pad(num_rows, num_cols))" << std::endl
			<< "or consider using QR factorisation" << std::endl
			<< "Exiting." << std::endl << std::endl;
		return;
	}
	// LHS-solution compatibility check
	if (A->num_cols != x->num_rows) {

		std::cout << "Left hand side matrix with " << A->num_cols << " collumns"
			<< " not compatible with solution with " << x->num_rows
			<< " elements." << std::endl
			<< "Exiting." << std::endl << std::endl;
		return;
	}
	// Solution-RHS compatibility check
	if (x->num_rows != B->num_rows) {
		std::cout << "Solution with " << x->num_rows << " elements"
			<< " not compatible with right hand side with " << B->num_rows
			<< " elements." << std::endl
			<< "Exiting." << std::endl << std::endl;
		return;
	}

}


// Perform the decomposition to L and U
void Solver::form_LUD(Matrix<double> *U, Matrix<double> *L) {
	// For square matrices only
	assert(A->num_rows == A->num_cols);
	for (int j = 0; j < A->num_cols; j++) {
		for (int i = 0; i < j + 1; i++) {
			double s1 = 0;
			// Subtract values of previous UL's
			for (int k = 0; k < i; k++) {
				s1 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			U->values[i * A->num_rows + j] = A->values[i * A->num_rows + j] - s1;
		}
		for (int i = j; i < A->num_cols; i++) {
			double s2 = 0;
			// Add values of previous UL's
			for (int k = 0; k < j; k++) {
				s2 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			L->values[i * A->num_rows + j] = (A->values[i * A->num_rows + j] - s2) / U->values[j * A->num_rows + j];
		}
	}
}


// Perform decomposition to L and L*
void Solver::form_cholesky(Matrix<double> *L) {
	// For square matrices only
	assert(A->num_rows == A->num_cols);
	for (int i = 0; i < A->num_rows; i++) {
		for (int j = 0; j < (i + 1); j++) {
			double s = 0;
			// Add or subtract values of previous UL's
			for (int k = 0; k < j; k++) {
				s += (L->values[i * A->num_rows + k] * L->values[j * A->num_rows + k]);
			}
			if (i == j) {
				L->values[i * A->num_rows + j] = sqrt(A->values[i * A->num_rows + i] - s);
			}
			else {
				L->values[i * A->num_rows + j] = (1.0 / L->values[j * A->num_rows + j] * (A->values[i * A->num_rows + j] - s));
			}
		}
	}
}


// Perform the forward substitution to solve Lx = b
Matrix<double>* Solver::forward_substitution(Matrix<double> *L, Matrix<double> *y) {
	// For square matrices only
	assert(L->num_rows == L->num_cols);
	for (int i = 0; i < L->num_rows; i++) {
		if (i == 0) {
			y->values[i] = B->values[i] / L->values[i  * L->num_rows + i];
		}
		else if (i != 0) {
			double s = 0;
			for (int j = 0; j < i; j++) {
				s += L->values[i * L->num_rows + j] * y->values[j];
			}
			y->values[i] = (1 / L->values[i * L->num_rows + i]) * (B->values[i] - s);
		}
	}
	return y;
}


// Perform the backwards substitution to solve L*z = y
void Solver::backward_substitution(Matrix<double> *U, Matrix<double> *y) {
	assert(U->num_rows == U->num_cols);
	for (int i = U->num_rows; i>-1; i--) {
		if (i == U->num_rows - 1) {
			x->values[U->num_rows - 1] = y->values[U->num_rows - 1] / U->values[i *  U->num_rows + i];
		}
		else if (i != U->num_rows) {
			double s = 0;
			for (int j = 0; j < U->num_cols; j++) {
				s += U->values[i* U->num_rows + j] * x->values[j];
			}
			x->values[i] = (1 / U->values[i * U->num_rows + i]) * (y->values[i] - s);
		}
	}
}


void Solver::LUD_solve() {

	// Checking to see if problem is valid
	check_input_validity();

	// U and L the same shape as A
	auto *U = new Matrix<double>(A->num_rows, A->num_cols, true);
	auto *L = new Matrix<double>(A->num_rows, A->num_cols, true);
	// y and x the same shape as B
	auto *y = new Matrix<double>(B->num_rows, B->num_cols, true);

	U->fill_zeros();
	y->fill_zeros();
	x->fill_zeros();

	// Decompose into upper and lower triagular matrices
	// No scope issues as both declaration and function called within this function
	form_LUD(U, L);
	// Forward substitution
	y = forward_substitution(L, y);
	// Backward substitution
	backward_substitution(U, y);
	delete U;
	delete L;
	delete y;
}


void Solver::cholesky_solve() {

	// Checking to see if problem is valid
	check_input_validity();

	// Initialise empty matrices for lower and lower transpose
	auto *L = new Matrix<double>(A->num_rows, A->num_cols, true);
	auto *L_t = new Matrix<double>(A->num_rows, A->num_rows, true);
	// y and x the same shape as B
	auto *y = new Matrix<double>(B->num_rows, B->num_cols, true);

	L_t->fill_zeros();
	y->fill_zeros();
	x->fill_zeros();

	// Decompose A matrix into lower triangular
	form_cholesky(L);
	// Form upper triangular from lower triangular
	L_t = transpose(L);
	// Forward substitution
	y = forward_substitution(L, y);
	delete L;
	// Backward substitution
	backward_substitution(L_t, y);
	delete L_t;
}


void Solver::gauss_seidel_solve(double omega) {

	// Checking to see if problem is valid
	check_input_validity();

	double sum;
	double max_change = 1;
	double new_value;
	int row_index;

	double tolerance = 0.0001;
	while (max_change > tolerance) {
		max_change = 0;
		// Iterate through each element
		for (int i = 0; i < A->num_rows; i++) {

			sum = 0;
			row_index = i * A->num_cols;

			// Use new information as it becomes available
			for (int j = 0; j < i; j++) {
				sum += (A->values[row_index + j] * x->values[j]);
			}
			for (int j = i + 1; j < A->num_cols; j++) {
				sum += (A->values[row_index + j] * x->values[j]);
			}
			// Successive over relaxation
			new_value = ((1 - omega) * x->values[i]) +
				(omega * (B->values[i] - sum) / A->values[row_index + i]);

			// Check to see if tolerance has been reached
			max_change = std::max(abs(x->values[i] - new_value), max_change);

			x->values[i] = new_value;

		}
	}
}


void Solver::jacobi_solve(double omega) {

	// Checking to see if problem is valid
	check_input_validity();
	
	// Create array to store old solution for jacobi
	double *old_solution = new double[x->num_rows];
	double sum;
	double max_change = 1;
	int row_index;

	for (int k = 0; k < x->num_rows; k++) {
		old_solution[k] = x->values[k];
	}

	double tolerance = 0.0001;
	while (max_change > tolerance) {

		max_change = 0;
		
		// Iterate through each element
		for (int i = 0; i < A->num_rows; i++) {
			sum = 0;
			row_index = i * A->num_cols;
			// Use old information fist, dont overwrite
			for (int j = 0; j < i; j++) {
				sum += (A->values[row_index + j] * old_solution[j]);
			}
			for (int j = i + 1; j < A->num_cols; j++) {
				sum += (A->values[row_index + j] * old_solution[j]);
			}
			// Weighted jacobi iteration
			x->values[i] = ((1 - omega) *  x->values[i]) +
				(omega * (B->values[i] - sum) / A->values[row_index + i]);
		}


		// Check to see if tolerance has been reached
		for (int k = 0; k < x->num_rows; k++) {
			max_change = std::max(abs(old_solution[k] - x->values[k]), max_change);
		}

		// Replace old with new and iterate onwards
		for (int k = 0; k < x->num_rows; k++) {
			old_solution[k] = x->values[k];
		}
	}
	delete[] old_solution;
}