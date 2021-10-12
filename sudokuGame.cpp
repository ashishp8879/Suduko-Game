#include <iostream>

#include <cstdio>

#include <cstring>

#include <cstdlib>

using namespace std;
#define empty 0
#define N 9
bool isGridSafe(int grid[N][N], int row, int col, int num);
/* assign values to all the zero (not assigned) values for Sudoku solution
 */
bool SolveSudoku(int grid[N][N], int r, int c) {
    int row, col;
    for (int row = r; row < 9; ++row) {
        for(int col = c; col < 9; ++col) {
            for (int num = 1; num <= 9; num++) {
                std::cout << "R: " << row << " C:  " << col << "  N: " << num << "\n";
                if (isGridSafe(grid, row, col, num)) {
                    grid[row][col] = num;
                    if (SolveSudoku(grid, r, c+1))
                        return true;
                    grid[row][col] = empty;
                }
            }
        }
    }
    return false;
}
/* Returns whether the assigned entry n in the particular row matches
   the given number num. */
bool UsedInRow(int grid[N][N], int prow, int number) {
    for (int col = 0; col < N; col++)
        if (grid[prow][col] == number)
            return true;
    return false;
}
/* Returns true if the number num matches any number in the column */
bool UsedInCol(int grid[N][N], int pcol, int number) {
    for (int row = 0; row < N; row++)
        if (grid[row][pcol] == number)
            return true;
    return false;
}
//Check if the entry used already in the grid box
bool UsedInBox(int grid[N][N], int box, int number)
{
    int boxCol = box % 3 * 3;
    int boxRow = box / 3 * 3;
    for (int sq = 0; sq < 9; ++sq)
        if (grid[boxRow + sq / 3][boxCol + sq % 3] == number)
            return true;
    return false;
}
/* Checks if num can be assigned to a given prow,pcol location. */
bool isGridSafe(int grid[N][N], int prow, int pcol, int number) {
    if (grid[prow][pcol] == empty)
        return false;
    return !UsedInRow(grid, prow, number) && !UsedInCol(grid, pcol, number) &&
        !UsedInBox(grid, pcol / 3 + prow / 3 * 3, number);
}
/* print result  */
void printResult(int finalgrid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << finalgrid[row][col] << "  ";
        cout << endl;
    }
}
/* Main */
int main() {
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
    if (SolveSudoku(grid, 0, 0) == true)
        printResult(grid);
    else
        cout << "No solution found" << endl;
    return 0;
}
