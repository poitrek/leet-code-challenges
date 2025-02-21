#include <iostream>
#include <string>
#include <vector>

#include "vector_print.h"

using namespace std;

/**
 * @brief First, simplest version
 * Runtime: 2ms, beats 75.13%
 * 
 * During the algorithm, solutions are generated as vectors of positions of consequent queens in *their* rows/columns
 * (since in each row/column there is exactly one), e.g. n=4:
 * + - - - - +
 * |   x     |
 * |       x |
 * | x       |
 * |     x   |
 * + - - - - +
 *   2 0 3 1
 * solution format: [2, 0, 3, 1] (position of a queen in each column, counting top->bottom, from 0) 
 * Then it is converted to the "visual" format required in the task.
 */
class Solution {
public:

	vector<vector<string>> solveNQueens(int n) {
		/// n x n vector of values 0 or more
		vector<vector<int>> board(n, vector<int>(n, 0));
		vector<vector<int>> solutions;
		vector<int> positions(n, 0);
		findRec(board, n, 0, positions, solutions);
		/// convert "digital" format of solutions to board representations
		vector<vector<string>> boardSolutions;
		for (const auto& solution : solutions) {
			vector<string> boardSolution (vector<string>(n, string(n, '.')));
			for (int i = 0; i < n; i++) {
				boardSolution[i][solution[i]] = 'Q';
			}
			boardSolutions.push_back(boardSolution);
		}
		return boardSolutions;
	}

	void setPosition(vector<vector<int>>& board, int n, int x, int y, int place_or_remove) {
		/// set all "forward" cells
		for (int i = x+1; i < n; i++)
			board[i][y] += place_or_remove;
		/// set all diagonal "up" cells
		for (int i = x+1, j = y-1; i < n && j >= 0; i++, j--)
			board[i][j] += place_or_remove;
		/// set all diagonal "down" cells
		for (int i = x+1, j = y+1; i < n && j < n; i++, j++)
			board[i][j] += place_or_remove;
	}
	
	void findRec(vector<vector<int>>& board, int n, int k, vector<int>& positions, vector<vector<int>>& solutions) {
		if (k == n) {
			solutions.push_back(positions);
			return;
		}
		for (int i = 0; i < n; i++) {
			if (board[k][i] > 0)
				continue;
			/// place the queen
			setPosition(board, n, k, i, 1);
			positions[k] = i;
			findRec(board, n, k+1, positions, solutions);
			/// remove the queen
			setPosition(board, n, k, i, -1);
		}
	}
};

int main() {
	cout << Solution().solveNQueens(5) << endl;
	return 0;
}
