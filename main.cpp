#include "sudoku.h"

sui read_size(const char *input_file);
bool is_size_possible(const string &size);

int main(int argc, char **argv)
{
    try
    {
        sui size = read_size(argv[1]);
        Sudoku_grid sdk(size);
        sdk.read_input_grid(argv[1]);
        if (sdk.solve())
            sdk.print_sudoku_grid(argv[1]);
        else
            cout << "This sudoku is unsolvable";
    }
    catch (const exception *exp)
    {
        cout << exp->what() << endl;
        return 0;
    }
}

sui read_size(const char *input_file)
{
    ifstream fin(input_file);
    string num;
    fin >> num;
    if (fin.eof() || !is_size_possible(num))
    {
        throw new Sudoku_exception;
    }
    sui size = stoi(num);
    return size;
}

bool is_size_possible(const string &size)
{
    sui no_of_possible_sizes = sizeof(long long int);
    string possible_sizes[no_of_possible_sizes];
    for (sui i = 0; i < no_of_possible_sizes; i++)
    {
        possible_sizes[i] = to_string((i + 1) * (i + 1));
    }
    return (find(possible_sizes, possible_sizes + sizeof(long long int), size) != (possible_sizes + sizeof(long long int)));
}
