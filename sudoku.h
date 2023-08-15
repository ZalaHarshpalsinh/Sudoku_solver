#include <iostream>
#include <fstream>
#define grid_size 9

class Sudoku_grid;

class Sudoku_grid
{
private:
    short unsigned int grid[grid_size][grid_size];
    short int row_bits[grid_size];
    short int column_bits[grid_size];
    short int sub_grid_bits[grid_size];

public:
    Sudoku_grid() : row_bits({0}), column_bits({0}), sub_grid_bits({0}) {}
    void read_input_grid(const char *input_file);
};
