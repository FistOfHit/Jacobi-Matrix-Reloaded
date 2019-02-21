#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.cpp"
#include "jacobi.h"
#include "gauss_siedel_sor.h"
#include <assert.h>


void creation_tests() {


	// Lets test if we can create a matrix and then
	// allocate values to it that were allocated before.
	std::cout << "----------Test: Create pre-allocated matrix----------" << std::endl;


	// Manually allocating array
	int prealloc_test_array[25];
	for (int i = 0; i < 25; i++) { prealloc_test_array[i] = i + 1; }


	// Creating a matrix
	Matrix<int>test_matrix1(5, 5, prealloc_test_array);
	std::cout << "Expected print out: " << std::endl
		<< "Matrix 5 X 5" << std::endl
		<< "Data type: int" << std::endl
		<< "1 2 3 4 5" << std::endl
		<< "6 7 8 9 10" << std::endl
		<< "11 12 13 14 15" << std::endl
		<< "16 17 18 19 20" << std::endl
		<< "21 22 23 24 25" << std::endl;
	std::cout << "Actual print out: " << std::endl;
	test_matrix1.print();


	// Lets test if we can create an empty matrix
	// (full of zeros) and print it out
	std::cout << "----------Test: Create empty zeros matrix----------" << std::endl;


	// Creating a matrix
	Matrix<int>test_matrix2(5, 5, true);
	cout << "Expected print out: " << endl << endl
		 << "Matrix 5 X 5" << endl
		 << "Data type: int" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl;
	std::cout << "Actual print out: " << std::endl;
	test_matrix2.print();


}

void iterative_solver_tests() {


	// Create a LHS A
	Matrix<double> test_LHS(4, 4, true);
	test_LHS.set_value(0, 0, 10);
	test_LHS.set_value(0, 1, -1);
	test_LHS.set_value(0, 2, 2);
	test_LHS.set_value(0, 3, 0);
	test_LHS.set_value(1, 0, -1);
	test_LHS.set_value(1, 1, 11);
	test_LHS.set_value(1, 2, -1);
	test_LHS.set_value(1, 3, 3);
	test_LHS.set_value(2, 0, 2);
	test_LHS.set_value(2, 1, -1);
	test_LHS.set_value(2, 2, 10);
	test_LHS.set_value(2, 3, -1);
	test_LHS.set_value(3, 0, 0);
	test_LHS.set_value(3, 1, 3);
	test_LHS.set_value(3, 2, -1);
	test_LHS.set_value(3, 3, 8);


	// Create a RHS b
	Matrix<double> test_RHS(4, 1, true);
	test_RHS.set_value(0, 0, 6);
	test_RHS.set_value(1, 0, 25);
	test_RHS.set_value(2, 0, -11);
	test_RHS.set_value(3, 0, 15);


	std::cout << "----------Test: Jacobi iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if jacobi with omega = 1 converges
	Matrix<double> test_jacobi(4, 1, true);
	jacobi(test_LHS, test_jacobi, test_RHS, 100);
	// See if it matches reality
	cout << "Expected print out: " << endl
		 << "Matrix 4 X 1" << endl
		 << "Data type: double" << endl
		 << 1 << endl
		 << 2 << endl
		 << -1 << endl
		 << 1 << endl;
	std::cout << "Actual print out: " << std::endl;
	test_jacobi.print();


	std::cout << "----------Test: Gauss-seidel iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if gauss-seidel with omega = 1 converges
	Matrix<double> test_gs(4, 1, true);
	gauss_seidel(test_LHS, test_gs, test_RHS, 100);
	// See if it matches reality
	cout << "Expected print out: " << endl
		 << "Matrix 4 X 1" << endl
		 << "Data type: double" << endl
		 << 1 << endl
		 << 2 << endl
		 << -1 << endl
		 << 1 << endl;
	std::cout << "Actual print out: " << std::endl;
	test_gs.print();


	std::cout << "----------Test: Successive over-relaxation (SOR) iterative solver----------" << std::endl;
	// Start with initial condition 0 vector,
	// See if gauss-seidel with omega = 1.5 converges (SOR)
	Matrix<double> test_sor(4, 1, true);
	gauss_seidel(test_LHS, test_sor, test_RHS, 100, 1.5);
	// See if it matches reality
	cout << "Expected print out: " << endl
		 << "Matrix 4 X 1" << endl
		 << "Data type: double" << endl
		 << 1 << endl
		 << 2 << endl
		 << -1 << endl
		 << 1 << endl;
	std::cout << "Actual print out: " << std::endl;
	test_sor.print();


}


//void operator_overload_tests() {
//
//
//	// Create a left operand for all operators
//	Matrix<double> left_operand(3, 3, true);
//	left_operand.set_value(0, 0, 1);
//	left_operand.set_value(0, 1, 1);
//	left_operand.set_value(0, 2, 1);
//	left_operand.set_value(1, 0, 1);
//	left_operand.set_value(1, 1, 1);
//	left_operand.set_value(1, 2, 1);
//	left_operand.set_value(2, 0, 1);
//	left_operand.set_value(2, 1, 1);
//	left_operand.set_value(2, 2, 1);
//
//
//	// Create a right operand for all operators
//	Matrix<double> right_operand(3, 3, true);
//	right_operand.set_value(0, 0, 1);
//	right_operand.set_value(0, 1, 1);
//	right_operand.set_value(0, 2, 1);
//	right_operand.set_value(1, 0, 1);
//	right_operand.set_value(1, 1, 1);
//	right_operand.set_value(1, 2, 1);
//	right_operand.set_value(2, 0, 1);
//	right_operand.set_value(2, 1, 1);
//	right_operand.set_value(2, 2, 1);
//
//
//	Matrix<double> sum_matrix = left_operand + right_operand;
//	sum_matrix.print();
//
//
//	Matrix<double> sub_matrix = left_operand - right_operand;
//	sub_matrix.print();
//
//
//}


void run_tests() {
	creation_tests();
	iterative_solver_tests();
	//operator_overload_tests();
}


// Performs Cholesky decomposition by reference
Matrix<double>* form_cholesky(Matrix<double> *A, Matrix<double> *L) {
	assert(A->num_rows == A->num_cols);
	for (int i = 0; i < A->num_rows; i++) {
			for (int j = 0; j < (i + 1); j++){
				double s = 0;
				for (int k = 0; k < j; k++) {
					s += (L->values[i * A->num_rows + k] * L->values[j * A->num_rows + k]);
				}
				if (i == j) {
					L->values[i * A->num_rows + j] = sqrt(A->values[i * A->num_rows + i] - s);
					}
				else{
					L->values[i * A->num_rows + j] = (1.0 / L->values[j * A->num_rows + j] * (A->values[i * A->num_rows + j] - s));
					}
			}
		}
	return L;
}


void form_LUD(Matrix<double> *A, Matrix<double> *U, Matrix<double> *L) {
	assert (A->num_rows == A->num_cols);
	for (int j=0; j < A->num_cols; j++){
		for (int i = 0; i < j + 1; i++) {
			double s1 = 0;

			for (int k = 0; k < i; k++) {
				s1 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
			}
			U->values[i * A->num_rows + j] = A->values[i * A->num_rows + j] - s1;
		}
		for (int i = j; i < A->num_cols; i++){
			double s2 = 0;
				for (int k=0; k<j; k++){
					s2 += U->values[k * A->num_rows + j] * L->values[i * A->num_rows + k];
				}
				L->values[i * A->num_rows + j] = (A->values[i * A->num_rows + j] - s2) / U->values[j * A->num_rows + j];
		}
	}
}


int main() {


	//int rows = 3;
	//int cols = 3;

	//// Performs Lower Upper decomposition using the Doolitle algorithm
	//// Initialising neccessary matrices
	//auto *A = new Matrix<double>(rows, cols, true);
	//auto *C = new Matrix<double>(rows, cols, true);
	//auto *L = new Matrix<double>(rows, cols, true);
	//auto *U = new Matrix<double>(rows, cols, true);
	//auto *y = new Matrix<double>(1, 3, true);
	//auto *B = new Matrix<double>(1, 3, true);
	//auto *x = new Matrix<double>(1, 3, true);

	//// Load example case
	//A->mat_load('A'); // A is  LUD, A is non-symmetric
	//C->mat_load('B'); // C is  LUD, B is lower Cholesky decomposiiton
	//U->mat_load('C'); // U is  LUD, B is Upper triangular Empty
	//L->mat_load('D'); // L is  LUD, D is Lower triangular identity
	//B->mat_load('F'); // B is [3, 2, 1]
	//y->mat_load('E'); // y is empty (1, 3)
	//x->mat_load('E'); // x is empty (1, 3)
	//
	////L = form_cholesky(C, L);   /////////////// Need to write transpose to implement this

	//// Decompose into upper and lower triagular matrices
	//form_LUD(A, U, L); 
	//// Forward substitution
	//y = forward_substitution(L, B, y);
	//// Backward substitution
	//x = backwards_substitution(U, y, x);
	//// Show solution
	//x->print();

	// If you want to run the tests
	run_tests();

	system("pause");


}