#include "sudoku.h"

sui read_size(const char *input_file);

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
    ifstream f(input_file);
    string num;
    f >> num;
    if (num == "" || !all_of(num.begin(), num.end(), ::isdigit) || num.size() > 2)
    {
        throw new Sudoku_exception;
    }
    sui size = stoi(num);
    return size;
}