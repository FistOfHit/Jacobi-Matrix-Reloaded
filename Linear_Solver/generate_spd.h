#pragma once
#include "Solvers.h"
#include "Matrix.h"


// Functions to generate random positive definite matrices of a given input
// These functions are quite verbose so a slightly more spacious layout 
// was chosen to allow readers to read through the code more easily
void print_solver_choices();
void generate_solve_spd(int size);