#pragma once
#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <set>
using namespace std;

class Sudoku
{
private:
	array<array<int, 9>, 9> sudoku = { {0} };
	vector<set<int>> row, col, sec;
	bool dfs(int x, int y);
	int _min, _max;
	int count;
public:
	int flag = 0;
	double time;
	Sudoku(int min = 60, int max = 5);
	bool isvalid(int x, int y, int num);
	bool setValid(int x, int y, int num);
	void CreateASudoku();
	bool solvedfs(int x, int y);
	bool solveset(int x, int y);
	void fillSudoku(int, int, int);
	void deleteSudoku(int, int, int);
	void displayBoard();
	bool solve();
};