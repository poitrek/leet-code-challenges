#include <iostream>
#include <unordered_set>
#include "common.hpp"

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (vector<char> row : board) {
            unordered_set<char> s;
            for (char c : row)
                if (!add_check(s, c))
                    return false;
        }
        for (int i = 0; i < board.size(); i++) {            
            unordered_set<char> s;
            for (int j = 0; j < board.size(); j++) {
                if (!add_check(s, board[j][i]))
                    return false;
            }
        }
        for (int i = 0; i < 9; i+=3)
            for (int j = 0; j < 9; j+=3) {
                unordered_set<char> s;
                for (int k = i; k < i+3; k++)
                    for (int l = j; l < j+3; l++)
                        if (!add_check(s, board[k][l]))
                            return false;
            }
        return true;
    }
    
    bool add_check(unordered_set<char> &s, char c) {
        if (c != '.')
            if (s.find(c) != s.end())
                return false;
            else
                s.insert(c);
        return true;
    }
};

int main(){
	// read sudoku board and stuff
	return 0;
}
