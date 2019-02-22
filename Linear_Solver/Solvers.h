#pragma once
#include "Matrix.h"


// Class that loads the problem matrices,
// and implements the solvers.
class Solver{	

	public:
		//Constructor with the system of equations to be solved
		Solver(Matrix<double> *A, Matrix<double> *B, Matrix<double> *x);

		// Problem defintiion
		Matrix<double> *A;		// A matrix - Physics/Mapping vector of the system
		Matrix<double> *B;		// B matrix - The data vector
		Matrix<double> *x;		// X matrix - The solution to the system

		void check_input_validity();
		
		// Create the L and U/L* for the direct methods
		void form_LUD(Matrix<double> *U, Matrix<double> *L);
		void form_cholesky(Matrix<double> *L);

		// Forward and backwards substitution sub-routines
		Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *y);
		void backward_substitution(Matrix<double> *U, Matrix<double> *y);

		// Solvers
		void LUD_solve();							 // Lower Upper Decomposition
		void cholesky_solve();						 // Cholesky Decomposition
		void gauss_seidel_solve(double omega = 1.0); // Gauss Seidel
		void jacobi_solve(double omega = 1.0);		 // Jacobi Iteration
};