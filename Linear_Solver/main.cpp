#include <iostream>
#include <math.h>
#include <time.h>
#include "Matrix.cpp"


using namespace std;


void creation_tests() {


	// Lets test if we can create a matrix and then
	// allocate values to it that were allocated before.
	cout << "----------Test: Create pre-allocated matrix----------" << endl;

	// Manually allocating array
	int prealloc_test_array[25];
	for (int i = 0; i < 25; i++) { prealloc_test_array[i] = i+1; }

	// Creating a matrix
	Matrix<int>test_matrix(5, 5, prealloc_test_array);

	cout << "Expected print out: " << endl << endl
		 << "Matrix 5 X 5" << endl
		 << "Data type: int" << endl
		 << "1 2 3 4 5" << endl
		 << "6 7 8 9 10" << endl
		 << "11 12 13 14 15" << endl
		 << "16 17 18 19 20" << endl
		 << "21 22 23 24 25" << endl;

	test_matrix.print();


	// Lets test if we can create an empty matrix
	// (full of zeros) and print it out
	cout << "----------Test: Create empty zeros matrix----------" << endl;

	// Creating a matrix
	Matrix<int>test_matrix(5, 5, true);

	cout << "Expected print out: " << endl << endl
		 << "Matrix 5 X 5" << endl
		 << "Data type: int" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl
		 << "0 0 0 0 0" << endl;

	test_matrix.print();


}

void run_tests() {

	creation_tests();

}



int index_convert(int row_ind, int col_ind, int row_count) {
	return row_ind * row_count + col_ind;
}

int main() {


	// If you want to run the tests
	//run_tests();


	int rows = 3;
	int cols = 3;
	auto *A = new Matrix<double>(rows, cols, true);
	auto *L = new Matrix<double>(rows, cols, true);

	A->values[0] = 4;
	A->values[1] = 12;
	A->values[2] = -16;
	A->values[3] = 12;
	A->values[4] = 37;
	A->values[5] = -43;
	A->values[6] = -16;
	A->values[7] = -43;
	A->values[8] = 98;

	for (int i = 0; i < 9; i++) {
		L->values[i] = 0;
	}

	A->print();
	L->print();

	std::cout << "Cholesky decomposition" << std::endl;

	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < (i + 1); j++){
			double s = 0;
			for (int k = 0; k < j; k++) {
				s += (L->values[i * rows + k] * L->values[j * rows + k]);
			}
			if (i == j) {
				L->values[i * rows + j] = sqrt(A->values[i * rows + i] - s);
				}
			else{
				L->values[i * rows + j] = (1.0 / L->values[j * rows + j] * (A->values[i * rows + j] - s));
				}
		}
	}

	L->print();

	delete A;
	delete L;


	system("pause");
}