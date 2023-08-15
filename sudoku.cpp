#include "sudoku.h"

void Sudoku_grid::read_input_grid(const char *input_file)
{
    ifstream fin(input_file);
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            sui num;
            fin >> num;
            if (num)
            {
                add_num_in_grid(i, j, num);
            }
        }
    }
    fin.close();
}

void Sudoku_grid::print_sudoku_grid(const char *output_file)
{
    sui sub_grid_size = sqrt(grid_size);
    ofstream fout(output_file, ios::app);
    fout << "\n\n\n---------------------------------------------------------------\n\n\n"
         << "The solved sudoku:\n\n\n";

    for (int i = 0; i < grid_size; i++)
    {
        if (i % sub_grid_size == 0 && i != 0)
        {
            fout << "__ __ __ __ __ __ __ __\n";
        }
        for (int j = 0; j < grid_size; j++)
        {
            if (j % sub_grid_size == 0 && j != 0)
            {
                fout << "| ";
            }
            fout << grid[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
}

bool Sudoku_grid::find_empty_cell_in_grid(sui &row, sui &col)
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}
sui Sudoku_grid::find_sub_grid_index(const sui &row, const sui &col)
{
    sui sub_grid_size = sqrt(grid_size);
    return (row / sub_grid_size) + (sub_grid_size * (col / sub_grid_size));
}

void Sudoku_grid::add_num_in_grid(const sui &row, const sui &col, const sui &num)
{
    grid[row][col] = num;

    sui sub_grid_index = find_sub_grid_index(row, col);

    sui adding_oprand = (1 << (num - 1));

    row_bits[row] |= adding_oprand;

    column_bits[col] |= adding_oprand;

    sub_grid_bits[sub_grid_index] |= adding_oprand;
}

void Sudoku_grid::remove_num_from_grid(const sui &row, const sui &col, const sui &num)
{
    grid[row][col] = 0;

    sui sub_grid_index = find_sub_grid_index(row, col);

    sui removing_oprand = ~(1 << (num - 1));

    row_bits[row] &= removing_oprand;

    column_bits[col] &= removing_oprand;

    sub_grid_bits[sub_grid_index] &= removing_oprand;
}

bool Sudoku_grid::is_in_row(const sui &row, const sui &num)
{
    return (row_bits[row] & (1 << (num - 1)));
}
bool Sudoku_grid::is_in_col(const sui &col, const sui &num)
{
    return (column_bits[col] & (1 << (num - 1)));
}

bool Sudoku_grid::is_in_sub_grid(const sui &index, const sui &num)
{
    return (sub_grid_bits[index] & (1 << (num - 1)));
}

bool Sudoku_grid::solve()
{
    sui row, col;
    sui sun_grid_index = (row / 3) + (3 * (col / 3));
    if (find_empty_cell_in_grid(row, col))
    {
        sui sub_grid_index = find_sub_grid_index(row, col);
        for (sui num = 1; num <= grid_size; num++)
        {
            if (!(is_in_row(row, num)) && !(is_in_col(col, num)) && !(is_in_sub_grid(sub_grid_index, num)))
            {
                add_num_in_grid(row, col, num);
                if (solve())
                {
                    return true;
                }
                remove_num_from_grid(row, col, num);
            }
        }
        return false;
    }
    else
    {
        return true;
    }
}