#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int empty = 0;
const int N = 9;

int grid[N][N] = {
        { 0, 0, 0, /**/ 0, 0, 0, /**/ 0, 0, 0 }, // 123456789
        { 0, 0, 0, /**/ 0, 0, 3, /**/ 0, 8, 5 }, // 12 4 67 9
        { 0, 0, 1, /**/ 0, 2, 0, /**/ 0, 0, 0 }, //   3456789
       /*-------------------------------------*/
        { 0, 0, 0, /**/ 5, 0, 7, /**/ 0, 0, 0 }, // 1234 6 89
        { 0, 0, 4, /**/ 0, 0, 0, /**/ 1, 0, 0 }, //  23 56789
        { 0, 9, 0, /**/ 0, 0, 0, /**/ 0, 0, 0 }, // 12345678
       /*-------------------------------------*/
        { 5, 0, 0, /**/ 0, 0, 0, /**/ 0, 7, 3 }, // 12 4 6 89
        { 0, 0, 2, /**/ 0, 1, 0, /**/ 0, 0, 0 }, //   3456789
        { 0, 0, 0, /**/ 0, 4, 0, /**/ 0, 0, 9 }  // 123 5678
       // 1  1          1     1          1  1
       // 2  2          2     2       2  2  2
       // 3  3  3       3  3          3  3
       // 4  4          4  4  4       4  4  4
       //    5  5          5  5       5  5
       // 6  6  6       6  6  6       6  6  6
       // 7  7  7       7  7          7     7
       // 8  8  8       8  8  8       8     8
       // 9     9       9  9  9       9  9  9
    };

bool isGridSafe(int row, int col, int num);
/* assign values to all the zero (not assigned) values for Sudoku solution */
bool SolveSudoku(int r, int c)
{
    int row, col;
    for (int row = r; row < N; ++row) {
        for(int col = c, c = 0; col < N; ++col) {
            if (grid[row][col] != empty) {
                continue;
            }
            for (int num = 1; num <= N; num++) {
                if (isGridSafe(row, col, num)) {
                    grid[row][col] = num;
                    if (SolveSudoku(r, c+1)) {
                        return true;
                    }
                    grid[row][col] = empty;
                }
            }
            return false;
        }
    }
    return false;
}

/* Checks if num can be assigned to a given prow,pcol location. */
bool isGridSafe(int prow, int pcol, int number)
{
    int boxRow = prow / 3 * 3;
    int boxCol = pcol / 3 * 3;
    for (int loop = 0; loop < N; loop++) {

        // Check this row
        if (grid[prow][loop] == number) {
            return false;
        }
        // Check this col
        if (grid[loop][pcol] == number) {
            return false;
        }
        // Check this box
        if (grid[boxRow + loop / 3][boxCol + loop % 3] == number) {
            return false;
        }
    }
    return true;
}

/* print result  */
void printResult()
{
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << grid[row][col] << "  ";
        }
        std::cout << "\n";
    }
}

/* Main */
int main()
{
    if (SolveSudoku(0, 0) == true) {
        printResult();
    } else {
        std::cout << "No solution found" << "\n";
    }
    return 0;
}
