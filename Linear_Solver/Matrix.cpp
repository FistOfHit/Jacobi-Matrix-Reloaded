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

		std::cout << "Column " << col_number << " is invalid for a matrix with "
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
	if (name == 'A') { // LU Decomposition example
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
	else if (name == 'B') { // B 
		this->values[0] = 3;
		this->values[1] = 2;
		this->values[2] = 1;
	}
	else if (name == 'C') { // Cholesky example
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
	else if (name == 'L') { // Lower Identity
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
}


template <class T>
void Matrix<T>::fill_zeros() {
	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++)
		this->values[i * this->num_rows + j] = 0;
	}
}


//template <class T>
//void Matrix<T>::operator=(const Matrix<T> &matrix_RHS) {
//
//	num_rows = matrix_RHS.num_rows;
//	num_cols = matrix_RHS.num_cols;
//	num_values = matrix_RHS.num_values;
//	self_allocate = matrix_RHS.self_allocate;
//	values = matrix_RHS.values;
//
//}
//
//
//
//template <class T>
//Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix_RHS) {
//
//
//	// Creating output matrix
//	Matrix<T> output_matrix(this->num_rows, matrix_RHS.num_cols, true);
//
//
//	// Checking if dimensions are compatible
//	if (this->num_rows != matrix_RHS.num_cols) {
//		cout << "left matrix with " << this->num_rows
//			 << " cannot be multiplied by a right matrix with " 
//			 << matrix_RHS.num_cols << " collumns." << endl
//			 << "Please check the dimensions of your operands." << endl
//			 << "Returning " << this->num_rows << " X " << matrix_RHS.num_cols
//			 << " matrix of zeros. " << endl;
//		return output_matrix;
//	}
//
//	
//	int sum;
//	// Variables for indexing our rows, saves a lot of computation
//	int right_row_index;
//	int left_row_index;
//	int output_row_index;
//
//
//	// Rows in left operand
//	for (int i = 0; i < this->num_rows; i++) {
//
//		left_row_index = i * this->num_cols;
//		output_row_index = i * matrix_RHS.num_cols;
//
//		// Collumns in right operand
//		for (int j = 0; j < matrix_RHS.num_cols; j++) {
//
//			sum = 0;
//
//			// Iterating through each element
//			for (int k = 0; k < this->num_rows; k++) {
//
//				right_row_index = k * matrix_RHS.num_cols;
//				sum += (this->values[left_row_index + k] * matrix_RHS.values[right_row_index + j]);
//
//			}
//
//			output_matrix.values[output_row_index + j] = sum;
//
//		}
//
//	}
//
//
//	return output_matrix;
//
//
//}
//
//
//template <class T>
//Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix_RHS) {
//
//
//	// Creating output matrix
//	Matrix<T> output_matrix(this->num_rows, this->num_cols, true);
//
//
//	// Checking if dimensions are compatible
//	if (this->num_rows != matrix_RHS.num_rows) {
//		cout << "left matrix with " << this->num_rows
//			 << " rows cannot be added to a right matrix with "
//			 << matrix_RHS.num_rows << " rows." << endl
//			 << "Please check the dimensions of your operands." << endl
//			 << "Returning " << this->num_rows << " X " << this->num_cols
//			 << " matrix of zeros. " << endl;
//		return output_matrix;
//	}
//	if (this->num_cols != matrix_RHS.num_cols) {
//		cout << "left matrix with " << this->num_cols
//			 << " collumns cannot be added to a right matrix with "
//			 << matrix_RHS.num_cols << " collumns." << endl
//			 << "Please check the dimensions of your operands." << endl
//			 << "Returning " << this->num_rows << " X " << this->num_cols
//			 << " matrix of zeros. " << endl;
//		return output_matrix;
//	}
//
//
//	// Variables for indexing our rows, saves a lot of computation
//	int row_index;
//
//
//	// Rows in left operand
//	for (int i = 0; i < this->num_rows; i++) {
//
//		row_index = i * this->num_cols;
//
//		// Collumns in right operand
//		for (int j = 0; j < matrix_RHS.num_cols; j++) {
//			output_matrix.values[row_index + j] = this->values[row_index + j] + matrix_RHS.values[row_index + j];
//		}
//
//	}
//
//
//	return output_matrix;
//
//
//}
//
//
//template <class T>
//Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix_RHS) {
//
//
//	// Creating output matrix
//	Matrix<T> output_matrix(this->num_rows, this->num_cols, true);
//
//
//	// Checking if dimensions are compatible
//	if (this->num_rows != matrix_RHS.num_rows) {
//		cout << "right matrix with " << matrix_RHS.num_rows
//			 << " rows cannot be subtracted from a left matrix with "
//			 << this->num_rows << " rows." << endl
//			 << "Please check the dimensions of your operands." << endl
//			 << "Returning " << this->num_rows << " X " << this->num_cols
//			 << " matrix of zeros. " << endl;
//		return output_matrix;
//	}
//	if (this->num_cols != matrix_RHS.num_cols) {
//		cout << "right matrix with " << matrix_RHS.num_cols
//			 << " collumns cannot be subtracted from a left matrix with "
//			 << this->num_cols << " collumns." << endl
//			 << "Please check the dimensions of your operands." << endl
//			 << "Returning " << this->num_rows << " X " << this->num_cols
//			 << " matrix of zeros. " << endl;
//		return output_matrix;
//	}
//
//
//	// Variables for indexing our rows, saves a lot of computation
//	int row_index;
//
//
//	// Rows in left operand
//	for (int i = 0; i < this->num_rows; i++) {
//
//		row_index = i * this->num_cols;
//
//		// Collumns in right operand
//		for (int j = 0; j < matrix_RHS.num_cols; j++) {
//			output_matrix.values[row_index + j] = this->values[row_index + j] - matrix_RHS.values[row_index + j];
//		}
//
//	}
//
//
//	return output_matrix;
//
//
//}
