#pragma once
#include "Matrix.h"
#include "Solvers.h"


// Functions related to the solving of a custom
//  input matrix by the user
Solver* create_custom_problem(int size);
void print_custom_solver_choices();
void solve_custom_problem(Solver &loaded_solver);