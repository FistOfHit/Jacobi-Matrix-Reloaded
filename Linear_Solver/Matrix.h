#pragma once

template <class T>
class Matrix
{
public:

   // Create and allocate the memory, zero array
   Matrix(int num_rows, int num_cols, bool self_allocate);

   // Create and point to memory already allocated before
   Matrix(int num_rows, int num_cols, T *values_ptr);#

   // destructor
   virtual ~Matrix();

   // Print out the values in our matrix
   void printValues();
   virtual void printMatrix();

   // Perform some operations with our matrix
   virtual void matMatMult(Matrix& mat_right, Matrix& output);

   // Initialise matrix attributes
   T *elements= nullptr;
   int num_rows = -1;
   int num_cols = -1;
   int num_elements = -1;

private:

   bool self_allocate
   
};