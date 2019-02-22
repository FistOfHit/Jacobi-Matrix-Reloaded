#pragma once
#include <iostream>
#include "Matrix.h"
#include "Solvers.h"


// Tests for integral parts of the codebase
void creation_tests();
void iterative_solver_tests();
void direct_solver_tests();

// Wrapper to run certain tests
void run_tests();