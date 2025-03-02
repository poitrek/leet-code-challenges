#include <iostream>
#include <vector>

#include "timer.hpp"

using namespace std;

class Solution {
public:

	int totalNQueens(int n) {
		/// n x n vector of values 0 or more
		vector<vector<int>> board(n, vector<int>(n, 0));
		int n_solutions;
		for (int i = 0; i < n / 2; i++) {
			n_solutions += setAndFindRec(board, n, 0, i);
		}
		n_solutions *= 2;
		if (n % 2 == 0) {
			n_solutions += setAndFindRec(board, n, 0, (n-1)/2);
		}
		return n_solutions;
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

	int setAndFindRec(vector<vector<int>>& board, int n, int k, int i) {
		/// place the queen
		setPosition(board, n, k, i, 1);
		int n_solutions = findRec(board, n, k+1);
		/// remove the queen
		setPosition(board, n, k, i, -1);
		return n_solutions;		
	}
	
	int findRec(vector<vector<int>>& board, int n, int k) {
		if (k == n) {
			return 1;
		}
		int n_solutions = 0;
		for (int i = 0; i < n; i++) {
			if (board[k][i] > 0)
				continue;
			/// place the queen
			setPosition(board, n, k, i, 1);
			n_solutions += findRec(board, n, k+1);
			/// remove the queen
			setPosition(board, n, k, i, -1);
		}
		return n_solutions;
	}
};


/**
 * @brief Another solution from LC, modified.
 * Key: simpler elimination of unsafe postions in each iteration.
 * Instead of using a 2D array corresponding to safety of board cells
 * notice that simplify the information we save about the taken cells
 * by identifying the *lines* occupied. 
 */
class AlternativeSolution1 {
public:
	int count = 0;
    int totalNQueens(int n) {
		vector<int> rows(n, 0);
		vector<int> d_down(2*n, 0);
		vector<int> d_up(2*n, 0);
        backtracking(0, rows, d_down, d_up, n);
        return count;
    }
    
    void backtracking(int col, vector<int>& rows, vector<int>& d_down, vector<int>& d_up, int n) {
        if (col == n) {
			count++;
			return;
		}

        for (int row = 0; row < n; row++) {
            int id_down = row - col + n;
            int id_up = row + col;
            if (rows[row] || d_down[id_down] || d_up[id_up])
				continue;
            rows[row] = 1; d_down[id_down] = 1; d_up[id_up] = 1;
            backtracking(col + 1, rows, d_down, d_up, n);
            rows[row] = 0; d_down[id_down] = 0; d_up[id_up] = 0;
        }
    }
};

int main() {
	for (int i = 8; i <= 15; i++) {
		Timer::start();
		auto result = AlternativeSolution1().totalNQueens(i);
		auto duration_seconds = Timer::get_seconds();
		cout << i << "-queens: " << result << "\n";
		cout << "calculation time: " << duration_seconds << "\n";
	}
	return 0;
}
