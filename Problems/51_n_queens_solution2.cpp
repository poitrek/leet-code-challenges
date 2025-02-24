#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "vector_print.h"
#include "timer.hpp"

using namespace std;

/**
 * @brief Second solution, optimized first version
 * Runtime: 0ms, beats 100%
 * Optimization: in first version, looking for solutions we start by placing first queen at each consequent cell of the
 * first row and try to fit all others in further rows. We notice that due to the axial symmetry (there are others) of
 * the problem, we can only search for solutions when the first queen is at any of the first n/2 cells of its row, and
 * mirror the generated solutions to get the other half (i.e. when first queen is placed at any of cells n/2+1...n-1).
 * Therefore, the algorithm is ~2 times faster. 
 */
class Solution {
public:

	int N;

	void setAndFindRec(vector<vector<int>>& board, int n, int x, int y, vector<int>& positions, vector<vector<int>>& solutions) {
		/// place the queen
		setPosition(board, n, x, y, 1);
		positions[x] = y;
		findRec(board, n, x+1, positions, solutions);
		/// remove the queen
		setPosition(board, n, x, y, -1);
	}

	/// Converts "position solutions" format to "board solutions" format
	void positionsToBoards(vector<vector<string>>& boardSolutions, vector<vector<int>>& positionSolutions) {
		for (const auto& posSol : positionSolutions) {
			vector<string> boardSol (vector<string>(N, string(N, '.')));
			for (int i = 0; i < N; i++) {
				boardSol[i][posSol[i]] = 'Q';
			}
			boardSolutions.push_back(boardSol);
		}
	}

	vector<vector<string>> solveNQueens(int n) {
		N = n;
		/// n x n vector of values 0 or more
		vector<vector<int>> board(n, vector<int>(n, 0));
		vector<vector<int>> solutions;
		vector<int> positions(n, 0);
		/// find first half of solutions (for first half positions of first queen)
		for (int i = 0; i < n / 2; i++) {
			setAndFindRec(board, n, 0, i, positions, solutions);
		}		
		/// convert "digital" format of solutions to board representations
		vector<vector<string>> boardSolutions;
		positionsToBoards(boardSolutions, solutions);

		/// mirror first half solutions (except the middle set if n is odd)
		int M = boardSolutions.size();
		for (int i = 0; i < M; i++) {
			vector<string> sol = boardSolutions[i];
			for (string& row : sol)
				ranges::reverse(row);
			boardSolutions.push_back(sol);
		}

		/// find and convert the middle set of solutions if n is odd
		if (n % 2 == 1) {
			vector<vector<int>> middleSolutions;
			setAndFindRec(board, n, 0, (n-1) / 2, positions, middleSolutions);
			positionsToBoards(boardSolutions, middleSolutions);
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
	for (int i = 2; i <= 9; i++) {
		Timer::start();
		auto result = Solution().solveNQueens(i);
		auto duration_seconds = Timer::get_seconds();
		cout << i << "-queens: " << result.size() << " solutions\n";
		cout << "calculation time: " << duration_seconds << "\n";
	}
	return 0;
}
