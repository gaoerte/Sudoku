#include "Sudoku.h"

Sudoku::Sudoku(int min, int max) : _min(min), _max(max)
{
	row.resize(9);
	col.resize(9);
	sec.resize(9);
	count = 0;
	cout << "创造一个数独：" << endl;
	CreateASudoku();
	/*fillSudoku(0, 7, 9);
	fillSudoku(1, 6, 5);
	fillSudoku(1, 4, 7);
	fillSudoku(3, 1, 5);
	fillSudoku(4, 1, 7);
	fillSudoku(5, 6, 3);
	fillSudoku(5, 7, 7);
	fillSudoku(6, 0, 2);
	fillSudoku(6, 2, 7);
	fillSudoku(6, 3, 4);
	fillSudoku(6, 5, 9);
	fillSudoku(6, 7, 6);
	fillSudoku(6, 8, 5);
	fillSudoku(7, 1, 6);
	fillSudoku(7, 3, 3);
	fillSudoku(7, 7, 1);
	fillSudoku(7, 8, 4);
	fillSudoku(8, 0, 1);
	fillSudoku(8, 4, 8);
	fillSudoku(8, 8, 9);*/
	displayBoard();
}

bool Sudoku::isvalid(int x, int y, int num)
{
	for (int i = 0; i < 9; ++i) {
		if (sudoku[i][y] == num || sudoku[x][i] == num) return false;
	}
	int section_x = x / 3;
	int section_y = y / 3;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (sudoku[i + 3 * section_x][j + 3 * section_y] == num) return false;
		}
	}
	return true;
}

bool Sudoku::setValid(int x, int y, int num) {
	int t = x / 3 * 3 + y / 3;
	return !row[x].count(num) && !col[y].count(num) && !sec[t].count(num);
}

bool Sudoku::dfs(int x, int y)
{
	if (x == 9) {
		return true;
	}
	if (y == 9) return dfs(x + 1, 0);
	if (sudoku[x][y] != 0) return dfs(x, y + 1);

	array<int, 9> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_device rd;
	mt19937 g(rd());
	shuffle(numbers.begin(), numbers.end(), g);

	for (auto num : numbers) {
		if (isvalid(x, y, num)) {
			sudoku[x][y] = num;
			if (dfs(x, y + 1)) return true;
			sudoku[x][y] = 0;
		}
	}
	return false;
}


void Sudoku::CreateASudoku()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib1(1, 9);
	uniform_int_distribution<> distrib2(81 - _min, 81 - _max);
	int x, y;
	auto start = chrono::high_resolution_clock::now();
	dfs(0, 0);
	int lim = distrib2(gen);
	cout << "Sudoku with " << lim << " missing values" << endl;
	for (int i = 0; i < lim; ++i) {
		x = distrib1(gen) - 1;
		y = distrib1(gen) - 1;
		if (sudoku[x][y]) {
			sudoku[x][y] = 0;
		}
		else {
			--i;
			continue;
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Creation Elapsed time: " << elapsed.count() << " seconds." << endl;
}

void Sudoku::displayBoard()
{
	// clear and reset cursor
	//cout << "\033[2J\033[1;1H";

	for (int i = 0; i < 9; ++i) {
		if (!(i % 3)) cout << "-----------------------------------" << endl;
		for (int j = 0; j < 9; ++j) {
			if (!(j % 3)) cout << "| ";
			if (sudoku[i][j] == 0) cout << "_" << "  ";
			else cout << sudoku[i][j] << "  ";
		}
		cout << " |" << endl;
	}
	cout << "-----------------------------------" << endl;
	//cout << "b" << endl;
}

bool Sudoku::solvedfs(int x, int y) {
	if (++count > 1000000) {
		flag = 2;
		return false;
	}
	if (x == 9) {
		return true;
	}
	if (y == 9) return solvedfs(x + 1, 0);
	if (sudoku[x][y] != 0) return solvedfs(x, y + 1);


	for (int i = 1; i < 10; ++i) {
		if (isvalid(x, y, i)) {
			sudoku[x][y] = i;
			if (solvedfs(x, y + 1)) return true;
			--count;
			sudoku[x][y] = 0;
		}
	}
	return false;
}

bool Sudoku::solveset(int x, int y) {
	if (++count > 100000) {
		flag = 2;
		return false;
	}
	//displayBoard();
	if (x == 9) {
		return true;
	}
	if (y == 9) return solveset(x + 1, 0);
	if (sudoku[x][y] != 0) return solveset(x, y + 1);

	for (int i = 1; i < 10; ++i) {
		if (setValid(x, y, i)) {
			fillSudoku(x, y, i);
			if (solveset(x, y + 1)) return true;
			--count;
			deleteSudoku(x, y, i);
		}
	}
	return false;
}

void Sudoku::fillSudoku(int x, int y, int num)
{
	int t = x / 3 * 3 + y / 3;
	sudoku[x][y] = num;
	row[x].insert(num);
	col[y].insert(num);
	sec[t].insert(num);
}

void Sudoku::deleteSudoku(int x, int y, int num) {
	int t = x / 3 * 3 + y / 3;
	sudoku[x][y] = 0;
	row[x].erase(num);
	col[y].erase(num);
	sec[t].erase(num);
}

bool Sudoku::solve()
{
	cout << "其中一个解为：" << endl;
	auto start = chrono::high_resolution_clock::now();
	bool unsolved = !solvedfs(0, 0);
	//bool unsolved = !solveset(0, 0);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Solving Elapsed time: " << elapsed.count() << " seconds." << endl;
	displayBoard();
	time = elapsed.count();
	if (unsolved || flag == 2) {
		return false;
	}
	flag = 1;
	return true;
}


