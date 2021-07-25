#include "sudoku_solver.h"
#include <iostream>

int main()
{
	sudoku_solver s({ {
			{4,0,0, 0,0,0, 0,1,0},
			{0,0,0, 4,0,2, 3,0,0},
			{8,3,6, 0,1,0, 0,0,0},

			{2,0,0, 0,6,0, 0,5,7},
			{0,9,0, 5,0,0, 6,0,1},
			{0,0,7, 1,0,0, 0,0,0},

			{0,0,0, 0,8,6, 0,0,3},
			{7,0,0, 0,0,0, 0,0,0},
			{6,4,0, 0,7,0, 0,0,2},
		} });
	if (s.solve())
		std::cout << s;
	else
		std::cout << "no solution found\n";
}
