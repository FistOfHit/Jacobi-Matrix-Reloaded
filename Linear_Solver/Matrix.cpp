#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "Matrix.h"


 //Constructor for zero array
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
    std::cout << "Data type: " << typeid(this->values[0]).name() << std::endl;


	// Print row by row
    int row_number;
    for (int i = 0; i < this->num_rows; i++) {  

		row_number = i * this->num_cols;
 
		for (int j = 0; j < this->num_cols; j++) {
			std::cout << this->values[row_number + j] << " ";
		}

		std::cout << std::endl;

    }


	std::cout << std::endl;


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
			<< this->num_cols << " columns." << std::endl
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


template <class T>
void Matrix<T>::set_value(int row_number, int col_number, T value) {


	// Checking if the element actually exists
	if ((row_number < 0) || (row_number >= this->num_rows)) {

		std::cout << "Row " << row_number << " is invalid for a matrix with "
			<< this->num_rows << " rows." << std::endl
			<< "Exiting." << std::endl;
		return;

	}
	if ((col_number < 0) || (col_number >= this->num_cols)) {

		std::cout << "Collumn " << col_number << " is invalid for a matrix with "
			<< this->num_cols << " collumns." << std::endl
			<< "Exiting." << std::endl;
		return;

	}


	this->values[(row_number * this->num_cols) + col_number] = value;

}


template <class T>
void Matrix<T>::mat_load(char name)
{
	if (name == 'A') { // LU Decomposition
		this->values[0] = 2;
		this->values[1] = -1;
		this->values[2] = -2;
		this->values[3] = -4;
		this->values[4] = 6;
		this->values[5] = 3;
		this->values[6] = -4;
		this->values[7] = -2;
		this->values[8] = 8;
	}
	else if (name == 'B') { // Cholesky
		this->values[0] = 4;
		this->values[1] = 12;
		this->values[2] = -16;
		this->values[3] = 12;
		this->values[4] = 37;
		this->values[5] = -43;
		this->values[6] = -16;
		this->values[7] = -43;
		this->values[8] = 98;
	}
	else if (name == 'C') { // Upper Empty
		for (int i = 0; i < 9; i++) {
			this->values[i] = 0;
		}
	}
	else if (name == 'D') { // Lower Identity
		for (int i = 0; i < this->num_rows; i++) {
			for (int j = 0; j < this->num_cols; j++) {
				if (i == j) {
					this->values[i * this->num_rows + j] = 1;
				}
				else {
					this->values[i * this->num_rows + j] = 0;
				}
			}
		}
	}
	else if (name == 'E') { // y and x empty
		for (int i = 0; i < 3; i++) {
			this->values[i] = 0;
		}
	}
	else if (name == 'F') { // B 
		this->values[0] = 3;
		this->values[1] = 2;
		this->values[2] = 1;
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

