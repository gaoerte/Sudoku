#include "Sudoku.h"

int runMany() {
	int counts[6] = { 0 };
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		Sudoku s;
		if (!s.solve()) {
			//system("pause");
			counts[5]++;
		};
		if (s.time < 0.01) {
			counts[0]++;
		}
		else if (s.time < 0.1) {
			counts[1]++;
		}
		else if (s.time < 1.0) {
			counts[2]++;
		}
		else if (s.time < 5.0) {
			counts[3]++;
		}
		else {
			counts[4]++;
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Total Elapsed time: " << elapsed.count() << " seconds." << endl;
	cout << "Under 0.01s: " << counts[0] << endl;
	cout << "Under 0.1s: " << counts[1] << endl;
	cout << "Under 1s: " << counts[2] << endl;
	cout << "Under 5s: " << counts[3] << endl;
	cout << "Over 5s: " << counts[4] << endl;
	cout << "Unsolved: " << counts[5] << endl;
	return 0;
}

int solveOne() {
	Sudoku s;
	cout << s.solve();
	return 0;
}

int main() {
	solveOne();
	//runMany();
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