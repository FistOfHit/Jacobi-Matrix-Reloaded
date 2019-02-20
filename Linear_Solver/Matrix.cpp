#include <iostream>
#include <string>
#include <typeinfo>
#include "Matrix.h"


// Constructor for zero array
template <class T>
Matrix<T>::Matrix(int num_rows, int num_cols, bool self_allocate):  num_rows(num_rows), num_cols(num_cols),
                                                                    num_values(num_rows * num_cols), self_allocate(self_allocate)  {

   if (self_allocate) {    

      // Destructor will handle deletion
      this->values = new T[this->num_values];

      for (int i = 0; i < this->num_values; i++) {
		  this->values[i] = 0;
      }

   } 

}


// Constructor for already allocated array
template <class T>
Matrix<T>::Matrix(int num_rows, int num_cols, T *ptr_to_array): num_rows(num_rows), num_cols(num_cols),
															    num_values(num_rows * num_cols), values(ptr_to_array) {}


// Destructor - deallocates memory
template <class T>
Matrix<T>::~Matrix() {

   // Delete the array
   if (this->self_allocate) {
      delete[] this->values;
   }

}


// Print out matrix values in a nice, human readable manner
template <class T>
void Matrix<T>::print() { 


	// Size of whats being printed
    std::cout << "Matrix: " << this->num_rows << " X " << this->num_cols << std::endl;
    // Data type of array
    std::cout << "Dtype: " << typeid(this->values[0]).name() << std::endl;


	// Print row by row
    int row_number;
    for (int i = 0; i < this->num_rows; i++) {  

		row_number = i * this->num_cols;
 
		for (int j = 0; j < this->num_cols; j++) {
			std::cout << this->values[row_number + j] << " ";
		}

		std::cout << std::endl;

    }


}


// Return a specific element of the matrix
template <class T>
T Matrix<T>::get_value(int row_number, int col_number, bool verbose) {


	// Checking if the element actually exists
	if ((row_number < 0) || (row_number >= this->num_rows)) {

		std::cout << "Row " << row_number << " is invalid for a matrix with "
				  << this->num_rows << " rows." << std::endl
				  << "Returning -1." << std::endl;
		return -1;

	}
	if ((col_number < 0) || (col_number >= this->num_cols)) {

		std::cout << "Collumn " << col_number << " is invalid for a matrix with "
			<< this->num_cols << " collumns." << std::endl
			<< "Returning -1." << std::endl;
		return -1;

	}


	// Creating memory for the element and finding it
	T required_element = this->values[(row_number * this->num_cols) + col_number];


	// If user wants it printed at runtime
	if (verbose) {
		std::cout << "Value at [" << row_number << "][" << col_number << "] = "
				  << required_element << std::endl;
	}


	return required_element;


}


// Return a matrix containing a selected row or collum of another matrix
template <class T>
Matrix<T>* Matrix<T>::get_value(int line_number, std::string dimension, bool verbose) {


	// Creating a new row matrix
	if (dimension == "row") {


		// Check if this row exists
		if ((line_number < 0) || (line_number >= this->num_rows)) {

			std::cout << "Row " << line_number << " is invalid for a matrix with "
				   	  << this->num_rows << " rows." << std::endl
					  << "Exiting." << std::endl;
			return nullptr;

		}


		// Create new row matrix
		Matrix<T> new_row = Matrix<T>(1, this->num_cols, true);


		// Assign the appropriate values
		for (int i = 0; i < this->num_cols; i++) {
			new_row->values[i] = this->values[(line_number * this->num_cols) + i];
		}


		// Print new row if verbosity
		if (verbose) {


			std::cout << "Row " << line_number << " = [";


			for (int i = 0; i < this->num_cols-1; i++) {
				std::cout << new_row->values[i] << ", ";
			}


			std::cout << new_row->values[this->num_cols-1] << "]" << std::endl;


		}


		// Return the pointer to it
		return &new_row;


	// Creating a new collumn matrix
	} else if (dimension == "collumn") {


		// Check if this collumn exists
		if ((line_number < 0) || (line_number >= this->num_cols)) {

			std::cout << "Collumn " << line_number << " is invalid for a matrix with "
					  << this->num_cols << " collumn." << std::endl
					  << "Exiting." << std::endl;
			return nullptr;

		}


		// Create new collumn matrix
		Matrix<T> new_col = Matrix<T>(this->num_rows, 1, true);


		// Assign the appropriate values
		for (int i = 0; i < this->num_cols; i++) {
			new_col->values[i] = this->values[(i * this->num_cols) + line_number];
		}


		// Print new collumn if verbosity
		if (verbose) {


			std::cout << "Collumn " << line_number << " = [";


			for (int i = 0; i < this->num_rows - 1; i++) {
				std::cout << new_col->values[i] << ", ";
			}


			std::cout << new_col->values[this->num_rows - 1] << "]" << std::endl;


		}


		// Return the pointer to it
		return &new_col;


	// If the dimension isnt correct
	} else {

		std::cout << dimension << " is not recognised as a dimension"
			      << ", either input 'row' or 'collumn' as a string." << std::endl
				  << "Returning null pointer." << std::endl;
		return nullptr;

	}
	

}





//// Do matrix matrix multiplication
//// output = this * mat_right
//template <class T>
//void Matrix<T>::matMatMult(Matrix& mat_right, Matrix& output)
//{
//
//   // Check our dimensions match
//   if (this->num_cols != mat_right.num_rows)
//   {
//      std::cerr << "Input dimensions for matrices don't match" << std::endl;
//      return;
//   }
//
//   // Check if our output matrix has had space allocated to it
//   if (output.values != nullptr) 
//   {
//      // Check our dimensions match
//      if (this->rows != output.rows || this->cols != output.cols)
//      {
//         std::cerr << "Input dimensions for matrices don't match" << std::endl;
//         return;
//      }      
//   }
//   // The output hasn't been preallocated, so we are going to do that
//   else
//   {
//      output.values = new T[this->rows * mat_right.cols];
//   }
//
//   // Set values to zero before hand
//   for (int i = 0; i < output.size_of_values; i++)
//   {
//      output.values[i] = 0;
//   }
//
//   // Now we can do our matrix-matrix multiplication
//   // CHANGE THIS FOR LOOP ORDERING AROUND
//   // AND CHECK THE TIME SPENT
//   // Does the ordering matter for performance. Why??
//   for(int i = 0; i < this->rows; i++)
//   {
//      for(int k = 0; k < this->cols; k++)
//      {
//         for(int j = 0; j < mat_right.cols; j++)
//         {            
//               output.values[i * output.cols + j] += this->values[i * this->cols + k] * mat_right.values[k * mat_right.cols + j];
//         }
//      }
//   }
//}