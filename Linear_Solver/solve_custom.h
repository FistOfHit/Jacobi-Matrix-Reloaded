#pragma once
#include "Matrix.h"
#include "Solvers.h"

void print_custom_solver_choices();
Solver* create_custom_problem(int size);
void solve_custom_problem(Solver &loaded_solver);