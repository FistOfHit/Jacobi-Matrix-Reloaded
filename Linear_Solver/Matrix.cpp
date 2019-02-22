#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include "Matrix.h"
#include <algorithm>


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


// Print out matrix values in a human readable manner
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


// Loads from a set of predefined matrix examples
template <class T>
void Matrix<T>::mat_load(char name)
{
	if (name == 'A') {		  // LU Decomposition example
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
	else if (name == 'B') {  // B 
		this->values[0] = 3;
		this->values[1] = 2;
		this->values[2] = 1;
	}
	else if (name == 'C') {  // Cholesky example
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
void Matrix<T>::read_LHS(int matrix_size) {

	// Enter matrix element by element
	int row_index;
	double element;
	// Each row
	for (int i = 0; i < matrix_size; i++) {

		// Each column
		row_index = i * matrix_size;
		for (int j = 0; j < matrix_size; j++) {
			
			// Prompt the user for next element
			std::cout << std::endl << "Enter value for A[" << i << ", " << j << "]: ";
			std::cin >> element;
			this->values[row_index + j] = element;
		}
	}
	std::cout << "All values entered. LHS A has been created." << std::endl;
}


template <class T>
void Matrix<T>::read_RHS(int num_rows) {

	// Enter vector element by element
	double element;
	// Each row
	for (int i = 0; i < num_rows; i++) {

		// Prompt the user for next element
		std::cout << std::endl << "Enter value for b[" << i << "]: ";
		std::cin >> element;
		this->values[i] = element;
	}
	std::cout << "All values entered. RHS b has been created." << std::endl;
}



//Fills the whole matrix with zero entries
template <class T>
void Matrix<T>::fill_zeros() {
	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++)
		this->values[i * this->num_rows + j] = 0;
	}
}


// Returns the transpose of the matrix instance
template <class T>
Matrix<T>* Matrix<T>::transpose() {
	auto *A_t = new Matrix<T>(this->num_rows, this->num_cols, true);
	// Iterate through elements, swapping
	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_cols; j++) {
			A_t->values[i * this->num_rows + j] = this->values[j * this->num_rows + i];
		}
	}
	return A_t;
}


// Generates a random Symmetric Positive Definite
// matrix of definited input size
template <class T>
void Matrix<T>::random_pdm(int size) {
	auto *rand_mat = new Matrix<T>(size, size, true);

	// Creates a matrix of pseudo random values
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			rand_mat->values[i * (size) + j] = rand() % 5;
		}
	}

	// Creates the transpose of the pseudo random matrix
	auto *rand_mat_trans = new Matrix<T>(size, size, true);
	rand_mat_trans = rand_mat->transpose();

	// Mutliplies the matrix by its transpose 
	// returning it into this matrix instance
	rand_mat->matMatMult(rand_mat_trans, this);

	// To ensure that the diagonal column is the largest entity
	// and therefore that the matrix is indeed a SPD matrix
	// Takes the largest value in each row and places that in
	// in the diagonal row and add 1
	double max_in_row;
	for (int i = 0; i < size; i++) {
		max_in_row = 0;
		for (int j = 0; j < size; j++) {
			max_in_row = std::max(this->values[i * (size) + j], max_in_row);
		}
		this->values[i * (size)+i] += max_in_row + 1;
	}
}


// Generate random positive integer matrix of definited input size
template <class T>
void Matrix<T>::random_B(int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->values[i * rows + j] = rand() % 9;
		}
	}
}


// Mulitplies two matrices together
template <class T>
void Matrix<T>::matMatMult(Matrix* mat_right, Matrix* output){	
	// Check our dimensions match
	if (this->num_cols != mat_right->num_rows)
	{
		std::cerr << "Input dimensions for matrices don't match" << std::endl;
		return;
	}

	// Check if our output matrix has had space allocated to it
	if (output->values != nullptr)
	{
		// Check our dimensions match
		if (this->num_rows != output->num_rows || this->num_cols != output->num_cols)
		{
			std::cerr << "Input dimensions for matrices don't match" << std::endl;
			return;
		}
	}
	// The output hasn't been preallocated, so we are going to do that
	else
	{
		output->values = new T[this-> num_rows * mat_right->num_cols];
	}

	// Set values to zero before hand
	for (int i = 0; i < output->num_values; i++)
	{
		output->values[i] = 0;
	}

	for (int i = 0; i < this->num_rows; i++)
	{
		for (int k = 0; k < this->num_cols; k++)
		{
			for (int j = 0; j < mat_right->num_cols; j++)
			{
				output->values[i * output->num_cols + j] += this->values[i * this->num_cols + k] * mat_right->values[k * mat_right->num_cols + j];
			}
		}
	}
}

