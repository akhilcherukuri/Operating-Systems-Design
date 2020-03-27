#include <set>
#include <stdbool.h>
#include <iostream>

using namespace std;

bool check_rows(char arr[][9], int row)
{
	set<char> st;

	for (int i = 0; i < 9; i++)
	{
		if (st.find(arr[row][i]) != st.end())
			return false;
	}
	return true;
}

bool check_columns(char arr[][9], int col)
{
	set<char> st;

	for (int i = 0; i < 9; i++)
	{
		if (st.find(arr[i][col]) != st.end())
			return false;
	}
	return true;
}

bool check_boxes(char arr[][9], int startRow, int startCol)
{
	set<char> st;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			char curr = arr[row + startRow][col + startCol];

			if (st.find(curr) != st.end())
				return false;

			if (curr != ' ')
				st.insert(curr);
		}
	}
	return true;
}

bool check_current(char arr[][9], int row, int col)
{
	return check_rows(arr, row) && check_columns(arr, col) &&
		   check_boxes(arr, row - row % 3, col - col % 3);
}

bool check_all(char arr[][9], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!check_current(arr, i, j))
				return false;
		}
	}
	return true;
}

int main()
{
	char sudoku_board[9][9] = {
		{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
		{'6', '7', '2', '1', '9', '5', '3', '4', '8'},
		{'1', '9', '8', '3', '4', '2', '5', '6', '7'},
		{'8', '5', '9', '7', '6', '1', '4', '2', '3'},
		{'4', '2', '6', '8', '5', '3', '7', '9', '1'},
		{'7', '1', '3', '9', '2', '4', '8', '5', '6'},
		{'9', '6', '1', '5', '3', '7', '2', '8', '4'},
		{'2', '8', '7', '4', '1', '9', '6', '3', '5'},
		{'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

	cout << (check_all(sudoku_board, 9) ? "Sudoku is Valid\n" : "Sudoku is not Valid\n");
	return 0;
}