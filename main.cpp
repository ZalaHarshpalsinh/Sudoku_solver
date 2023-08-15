#include "sudoku.h"

int main(int argc, char **argv)
{
    Sudoku_grid sdk;
    sdk.read_input_grid(argv[1]);
    sdk.solve();
    sdk.print_sudoku_grid(argv[1]);
}