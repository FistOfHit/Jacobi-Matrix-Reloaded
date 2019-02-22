#pragma once
#include "Matrix.h"


// Class that loads the problem matrices,
// and implements the solvers.
class Solver{	

	public:
		Solver(Matrix<double> *A, Matrix<double> *B, Matrix<double> *x);

		// Problem defintiion
		Matrix<double> *A;			// A matrix
		Matrix<double> *B;			// B matrix
		Matrix<double> *x;			// X solution matrix

		// To check if the inputs are valid.
		void check_input_validity();
		// Transposing any matrix
		
		// Create the L and U/L* for the direct methods
		void form_LUD(Matrix<double> *U, Matrix<double> *L);
		void form_cholesky(Matrix<double> *L);
		// Forward/backwards substitution sub-routines
		Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *y);
		void backward_substitution(Matrix<double> *U, Matrix<double> *y);
		// Solvers themselves
		void LUD_solve();
		void cholesky_solve();
		void gauss_seidel_solve(double omega = 1.0);
		void jacobi_solve(double omega = 1.0);
};