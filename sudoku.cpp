#include "sudoku.h"

void Sudoku_grid::read_input_grid(const char *input_file)
{
    fstream fin(input_file, ios::in);
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            fin >> grid[i][j];
        }
    }
    fin.close();
}