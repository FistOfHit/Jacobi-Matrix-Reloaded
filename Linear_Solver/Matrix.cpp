#include <iostream>
#include <typeinfo>
#include "Matrix.h"


// Constructor for zero array
template <class T>
Matrix<T>::Matrix(int num_rows, int num_cols, bool self_allocate):  num_rows(num_rows), num_cols(num_cols),
                                                                    num_elements(rows * cols), self_allocate(self_allocate)  {

   if (self_allocate) {    

      // Destructor will handle
      this->elements = new T[num_elements];

      for (int i = 0; i < num_elements; i++) {
         this->elements[i] = 0;
      }

   } 

}


// Constructor for already allocated array
template <class T>
Matrix<T>::Matrix(int num_rows, int num_cols, T *array_ptr): num_rows(num_rows), num_cols(num_cols),
                                                              num_elements(rows * cols), elements(array_ptr) {}


// Destructor - deallocates memory
template <class T>
Matrix<T>::~Matrix() {

   // Delete the array
   if (this->preallocated) {
      delete[] this->elements;
   }

}


// Explicitly print out the values in values array as if they are a matrix
template <class T>
void Matrix<T>::print() { 


   // Size of whats being printed
   std::cout << "Matrix: " << this->num_rows << " X " << this->num_cols << std::endl;
   // Data type of array
   std::cout << "Dtype: " << typeid(this->elements[0].name()) << std::endl;


   int row_number;
   for (int i = 0; i < this->rows; i++) {  

      row_number = i * this->num_cols

      for (int j = 0; j < this->num_cols; j++) {
         std::cout << this->values[row_number + j] << " ";
      }

      std::cout << std::endl;

   }


}

// Do matrix matrix multiplication
// output = this * mat_right
template <class T>
void Matrix<T>::matMatMult(Matrix& mat_right, Matrix& output)
{

   // Check our dimensions match
   if (this->cols != mat_right.rows)
   {
      std::cerr << "Input dimensions for matrices don't match" << std::endl;
      return;
   }

   // Check if our output matrix has had space allocated to it
   if (output.values != nullptr) 
   {
      // Check our dimensions match
      if (this->rows != output.rows || this->cols != output.cols)
      {
         std::cerr << "Input dimensions for matrices don't match" << std::endl;
         return;
      }      
   }
   // The output hasn't been preallocated, so we are going to do that
   else
   {
      output.values = new T[this->rows * mat_right.cols];
   }

   // Set values to zero before hand
   for (int i = 0; i < output.size_of_values; i++)
   {
      output.values[i] = 0;
   }

   // Now we can do our matrix-matrix multiplication
   // CHANGE THIS FOR LOOP ORDERING AROUND
   // AND CHECK THE TIME SPENT
   // Does the ordering matter for performance. Why??
   for(int i = 0; i < this->rows; i++)
   {
      for(int k = 0; k < this->cols; k++)
      {
         for(int j = 0; j < mat_right.cols; j++)
         {            
               output.values[i * output.cols + j] += this->values[i * this->cols + k] * mat_right.values[k * mat_right.cols + j];
         }
      }
   }
}