#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <cmath>
#define sui short unsigned int
using namespace std;

class Sudoku_grid;
class Sudoku_exception;

class Sudoku_grid
{
private:
    sui *grid;
    long long int *row_bits;
    long long int *column_bits;
    long long int *sub_grid_bits;
    sui size;
    bool my_eof;

public:
    Sudoku_grid(sui size);
    ~Sudoku_grid();
    void read_input_grid(const char *input_file);
    void print_sudoku_grid(const char *output_file);
    bool find_empty_cell_in_grid(sui &row, sui &col);
    bool is_in_row(const sui &row, const sui &num) const;
    bool is_in_col(const sui &col, const sui &num) const;
    bool is_in_sub_grid(const sui &index, const sui &num) const;
    sui find_sub_grid_index(const sui &row, const sui &col) const;
    void add_num_in_grid(const sui &row, const sui &col, const sui &num);
    bool solve();
    void remove_num_from_grid(const sui &row, const sui &col, const sui &num);
};

class Sudoku_exception : public exception
{
public:
    const char *what() const throw();
};