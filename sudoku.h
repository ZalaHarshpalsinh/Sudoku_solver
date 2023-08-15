#include <iostream>
#include <fstream>
#include <cmath>
#define grid_size 9
#define sui short unsigned int
using namespace std;

class Sudoku_grid;

class Sudoku_grid
{
private:
    sui grid[grid_size][grid_size];
    sui row_bits[grid_size];
    sui column_bits[grid_size];
    sui sub_grid_bits[grid_size];
    sui find_sub_grid_index(const sui &row, const sui &col);

public:
    Sudoku_grid() : grid{0}, row_bits{0}, column_bits{0}, sub_grid_bits{0}
    {
    }
    void read_input_grid(const char *input_file);
    void print_sudoku_grid(const char *output_file);
    bool solve();
    void add_num_in_grid(const sui &row, const sui &col, const sui &num);
    void remove_num_from_grid(const sui &row, const sui &col, const sui &num);
    bool find_empty_cell_in_grid(sui &row, sui &col);
    bool is_in_row(const sui &row, const sui &num);
    bool is_in_col(const sui &col, const sui &num);
    bool is_in_sub_grid(const sui &index, const sui &num);
};
