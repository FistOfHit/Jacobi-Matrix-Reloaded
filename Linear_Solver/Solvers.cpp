#include <iostream>
#include "Solvers.h"
#include "Matrix.h"
#include "Matrix.cpp"
#include <assert.h>


Matrix<double>* Solver::transpose(Matrix<double> *A) {
	auto *A_t = new Matrix<double>(A->num_rows, A->num_cols, true);
	A_t->fill_zeros(); // A_t is Upper triangular Empty
	for (int i = 0; i < A->num_rows; i++) {
		for (int j = 0; j < A->num_cols; j++) {
			A_t->values[j * A->num_rows + i] = A->values[i* A->num_rows + j];
		}
	}
	return A_t;
}


void Solver::form_LUD(Matrix<double> *U, Matrix<double> *L) {
	assert(A->num_rows == A->num_cols);
	for (int j = 0; j < A->num_cols; j++) {
		for (int i = 0; i < j + 1; i++) {
			double s1 = 0;

			for (int k = 0; k < i; k++) {
				s1 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			U->values[i * A->num_rows + j] = A->values[i * A->num_rows + j] - s1;
		}
		for (int i = j; i < A->num_cols; i++) {
			double s2 = 0;
			for (int k = 0; k < j; k++) {
				s2 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			L->values[i * A->num_rows + j] = (A->values[i * A->num_rows + j] - s2) / U->values[j * A->num_rows + j];
		}
	}
}


void Solver::form_cholesky(Matrix<double> *L) {
	assert(A->num_rows == A->num_cols);
	for (int i = 0; i < A->num_rows; i++) {
		for (int j = 0; j < (i + 1); j++) {
			double s = 0;
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


Matrix<double>* Solver::forward_substitution(Matrix<double> *L, Matrix<double> *y) {
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
	std::cout << "reached here";
	// Backward substitution
	backward_substitution(U, y);
	delete U;
	delete L;
	delete y;
}


void Solver::cholesky_solve() {
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