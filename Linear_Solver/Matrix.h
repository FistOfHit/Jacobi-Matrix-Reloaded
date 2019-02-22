#pragma once
#include <string>


// Generates matrices, loads predefined matrices and performs
// basic matrix operations
template <class T>
class Matrix {

	public:

		// Create and allocate the memory, zero array
		Matrix(int num_rows, int num_cols, bool self_allocate);

		// Create and point to memory already allocated before
		Matrix(int num_rows, int num_cols, T *values_ptr);

		// destructor
		virtual ~Matrix();

		// Print out the values in our matrix
		Matrix<T>* transpose();
		void print();
		void fill_zeros();

		// Fills the matrices with a random symmetric positive definite matrix
		void random_pdm(int size);
		// Fills the matrix with random positive values
		void random_B(int rows, int cols);

		// Access specific elements
		T get_value(int row_number, int col_number, bool verbose);
		void set_value(int row_number, int col_number, T value);

		// Load in matrix case
		void mat_load(char name);

		// Read custom matrix from cmd
		void read_LHS(int matrix_size);
		void read_RHS(int num_rows);

		// Perform some operations with our matrix
		void matMatMult(Matrix* mat_right, Matrix* output);
		// Initialise matrix attributes
		T *values = nullptr;
		int num_rows = -1;
		int num_cols = -1;
		int num_values = -1;
		bool self_allocate;
};