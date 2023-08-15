#include "sudoku.h"

Sudoku_grid::Sudoku_grid(sui size) : size(size), my_eof(false)
{
    grid = new sui[size * size]{0};
    row_bits = new long long int[size]{0};
    column_bits = new long long int[size]{0};
    sub_grid_bits = new long long int[size]{0};
}

void Sudoku_grid::read_input_grid(const char *input_file)
{
    ifstream fin(input_file);
    string num;
    fin >> num;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fin >> num;
            if ((fin.eof() && my_eof) || num == "" || !all_of(num.begin(), num.end(), ::isdigit) || num.size() > 2)
            {
                throw new Sudoku_exception;
            }
            else if (fin.eof())
            {
                my_eof = true;
            }
            sui tmp = stoi(num);
            if (tmp)
            {
                add_num_in_grid(i, j, tmp);
            }
        }
    }
    fin.close();
}

void Sudoku_grid::print_sudoku_grid(const char *output_file)
{
    sui sub_size = sqrt(size);
    ofstream fout(output_file, ios::app);
    fout << "\n\n\n---------------------------------------------------------------\n\n\n"
         << "The solved sudoku:\n\n\n";

    for (int i = 0; i < size; i++)
    {
        if (i % sub_size == 0 && i != 0)
        {
            for (sui i = 0; i < size; i++)
            {
                fout << "__ ";
            }
            fout << "\n";
        }
        for (int j = 0; j < size; j++)
        {
            if (j % sub_size == 0 && j != 0)
            {
                fout << "| ";
            }
            fout << grid[(i * size) + j] << " ";
        }
        fout << "\n";
    }
    fout.close();
}

bool Sudoku_grid::find_empty_cell_in_grid(sui &row, sui &col)
{
    for (sui i = 0; i < size; i++)
    {
        for (sui j = 0; j < size; j++)
        {
            if (grid[i * size + j] == 0)
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}
sui Sudoku_grid::find_sub_grid_index(const sui &row, const sui &col) const
{
    sui sub_size = sqrt(size);
    return (row / sub_size) + (sub_size * (col / sub_size));
}

void Sudoku_grid::add_num_in_grid(const sui &row, const sui &col, const sui &num)
{
    grid[row * size + col] = num;

    sui sub_grid_index = find_sub_grid_index(row, col);

    long long int adding_oprand = (1 << (num - 1));

    row_bits[row] |= adding_oprand;

    column_bits[col] |= adding_oprand;

    sub_grid_bits[sub_grid_index] |= adding_oprand;
}

void Sudoku_grid::remove_num_from_grid(const sui &row, const sui &col, const sui &num)
{
    grid[row * size + col] = 0;

    sui sub_grid_index = find_sub_grid_index(row, col);

    long long int removing_oprand = ~(1 << (num - 1));

    row_bits[row] &= removing_oprand;

    column_bits[col] &= removing_oprand;

    sub_grid_bits[sub_grid_index] &= removing_oprand;
}

bool Sudoku_grid::is_in_row(const sui &row, const sui &num) const
{
    return (row_bits[row] & (1 << (num - 1)));
}
bool Sudoku_grid::is_in_col(const sui &col, const sui &num) const
{
    return (column_bits[col] & (1 << (num - 1)));
}

bool Sudoku_grid::is_in_sub_grid(const sui &index, const sui &num) const
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
        for (sui num = 1; num <= size; num++)
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

const char *Sudoku_exception::what() const throw()
{
    return "Input file is not in the correct format.\nPlease read the readme file to understand the format of input.";
}