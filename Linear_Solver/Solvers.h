#ifndef SOLVERS
#define SOLVERS

#include "Matrix.h"


class Solver{	

	public:
		Solver(Matrix<double> *A, Matrix<double> *B, Matrix<double> *x);

		Matrix<double> *A;			// A matrix
		Matrix<double> *B;			// B matrix
		Matrix<double> *x;			// X solution matrix

		Matrix<double>* random_pdm(int size);
		Matrix<double>* random_B(int rows, int cols);

		Matrix<double>* transpose(Matrix<double> *A);
		void form_LUD(Matrix<double> *U, Matrix<double> *L);
		void form_cholesky(Matrix<double> *L);
		Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *y);
		void backward_substitution(Matrix<double> *U, Matrix<double> *y);
		void LUD_solve();
		void cholesky_solve();
		void gauss_seidel_solve(int num_iterations = 100, double omega = 1);
		void jacobi_solve(int num_iterations = 100, double omega = (2.0 / 3.0));
};
#endif