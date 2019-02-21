#pragma once
#include <string>

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
		void print();
		void fill_zeros();

		// Access specific elements
		T get_value(int row_number, int col_number, bool verbose);
	
		void set_value(int row_number, int col_number, T value);

		// Load in matrix case
		void mat_load(char name);

		// Initialise matrix attributes
		T *values = nullptr;
		int num_rows = -1;
		int num_cols = -1;
		int num_values = -1;
		bool self_allocate;
};