#ifndef SOLVERS
#define SOLVERS

#include "Matrix.h"


class Solver{	

	public:

		Matrix<double> *A;			// A matrix
		Matrix<double> *B;			// B matrix
		Matrix<double> *x;			// X solution matrix

		Matrix<double>* transpose(Matrix<double> *A);
		void form_LUD(Matrix<double> *U, Matrix<double> *L);
		void form_cholesky(Matrix<double> *L);
		Matrix<double>* forward_substitution(Matrix<double> *L, Matrix<double> *y);
		void backward_substitution(Matrix<double> *U, Matrix<double> *y);
		void LUD_solve();
		void cholesky_solve();
};
#endif