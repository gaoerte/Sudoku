#include "DancingLinks.h"

int main() {
    cout << "创造一个数独:" << endl;
    CreateASudoku();
    displayBoard();
    cout << "其中一个解为:" << endl;
    SolveByDLXRandom();
    displayBoard();
    return 0;
}


/*
    sudoku[0][2] = 8;
    sudoku[0][6] = 2;
    sudoku[1][1] = 3;
    sudoku[1][3] = 8;
    sudoku[1][5] = 2;
    sudoku[1][7] = 6;
    sudoku[2][0] = 7;
    sudoku[2][4] = 9;
    sudoku[2][8] = 5;
    sudoku[3][1] = 5;
    sudoku[3][7] = 1;
    sudoku[4][2] = 4;
    sudoku[4][6] = 6;
    sudoku[5][1] = 2;
    sudoku[5][7] = 7;
    sudoku[6][0] = 4;
    sudoku[6][4] = 8;
    sudoku[6][8] = 6;
    sudoku[7][1] = 7;
    sudoku[7][3] = 1;
    sudoku[7][5] = 3;
    sudoku[7][7] = 9;
    sudoku[8][2] = 1;
    sudoku[8][6] = 8;
    dfs(0,0);
*/


/*sudoku[0][7] = 9;
    sudoku[1][6] = 5;
    sudoku[1][4] = 7;
    sudoku[3][1] = 5;
    sudoku[4][1] = 7;
    sudoku[5][6] = 3;
    sudoku[5][7] = 7;
    sudoku[6][0] = 2;
    sudoku[6][2] = 7;
    sudoku[6][3] = 4;
    sudoku[6][5] = 9;
    sudoku[6][7] = 6;
    sudoku[6][8] = 5;
    sudoku[7][1] = 6;
    sudoku[7][3] = 3;
    sudoku[7][7] = 1;
    sudoku[7][8] = 4;
    sudoku[8][0] = 1;
    sudoku[8][4] = 8;
    sudoku[8][8] = 9;
    displayBoard();*/