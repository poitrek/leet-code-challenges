#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <chrono>

using namespace std;

template<typename T>
std::ostream& operator << (std::ostream& ost, const std::vector<T> v) {
	for (T e : v) ost << e << " ";
	return ost;
}

class Solution {
public:
    bool search(const vector<vector<char>> &board, int x, int y, string word, set<pair<int, int>> visited) {
        // Successful end of search
        if (word == "")
            return true;
        // Current cell not matching or already visited
        if (board[x][y] != word.front() || visited.find(pair(x, y)) != visited.end()) 
            return false;
        else {
            // Search the rest of the word for every direction, excluding this cell
            visited.insert(pair(x, y));
            string subword = word.substr(1, word.size()-1);
            return 
                search(board, x, y+1, subword, visited) ||
                search(board, x, y-1, subword, visited) ||
                search(board, x+1, y, subword, visited) ||
                search(board, x-1, y, subword, visited);
        }
    }

    void update_cnt_map(map<char, int> &count, char c) {
        if (count.count(c))
            count[c]++;
        else
            count[c] = 1;
    }

    /// @brief Reverses the string if there are more repetitions of the same character from its
    /// front than from its back. This shall reduce the search of a word in the grid. Example:
    /// Grid:
    /// AAAAAAAAAA
    /// AAAAAAAAAC
    /// AAAAAAAACA
    /// word: AAAAAAAAAAAACC
    /// The backtracking search imposes a very large number of paths you can make with A's.
    /// If we instead look for the reversed word CCAAAAAAAAAAAA, the search ends quickly.
    void reverse_string_proc(string &s) {
        auto it_front = find_if(s.begin(), s.end(), [&](char c){
            return c != s.front();
        });
        auto front_repetitions = distance(s.begin(), it_front);
        auto it_back = find_if(s.rbegin(), s.rend(), [&](char c){
            return c != s.back();
        });
        auto back_repetitions = distance(s.rbegin(), it_back);
        if (back_repetitions < front_repetitions)
            reverse(s.begin(), s.end());
    }

    bool exist(vector<vector<char>> board, string word) {
        int m = board.size();
        int n = board[0].size();
        // heuristics: false if there aren't enough characters in the board
        map<char, int> count_word;
        for (char c : word)
            update_cnt_map(count_word, c);
        map<char, int> count_board;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                update_cnt_map(count_board, board[i][j]);
        for (pair<char, int> w_key_cnt : count_word)
            if (!count_board.count(w_key_cnt.first) || count_board[w_key_cnt.first] < w_key_cnt.second)
                return false;

        // add safe board "bounds"
        board.insert(board.begin(), vector<char>(n+2, '-'));
        board.push_back(vector<char> (n+2, '-'));
        for (int i = 1; i < m+1; i++) {
            board[i].insert(board[i].begin(), '-');
            board[i].push_back('-');
        }
        /// Reverse the string depending on the front/back repetitions - heuristics
        reverse_string_proc(word);
        // four directions (possible steps)
        vector<pair<int,int>> step = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 1; i < m+1; i++)
            for (int j = 1; j < n+1; j++) {
                if (search(board, i, j, word, set<pair<int, int>>()) == true)
                    return true;
            }
        return false;
    }

    /// first approach, deprecated
    bool exist2(vector<vector<char>> board, string word) {
        int m = board.size();
        int n = board[0].size();
        // add safe board "bounds"
        board.insert(board.begin(), vector<char>(n+2, '-'));
        board.push_back(vector<char> (n+2, '-'));
        for (int i = 1; i < m+1; i++) {
            board[i].insert(board[i].begin(), '-');
            board[i].push_back('-');
        }
        // cout << "modified board:" << endl;
        // cout << board << endl;
        // four directions (possible steps)
        vector<pair<int,int>> step = {pair(0, 1), pair(0, -1), pair(1, 0), pair(-1, 0)};
        for (int i = 0; i < m+2; i++) {
            for (int j = 0; j < n+2; j++) {
                // set of already visited cells
                set<pair<int, int>> visited;
                if (board[i][j] == word.front()) {
                    int x=i, y=j;
                    visited.insert(pair(x, y));
                    string::iterator it;
                    for (it = word.begin()+1; it != word.end(); ++it) {
                        // for each direction, check if adjacent cell contains next
                        // character and hasn't been visited yet
                        bool found_next_char = false;
                        for (pair<int, int> s : step) {
                            int x_nxt = x + s.first, y_nxt = y + s.second;
                            if (board[x_nxt][y_nxt] == *it &&
                                visited.find(pair(x_nxt, y_nxt)) == visited.end()) {
                                // update cursor pos
                                x = x_nxt; y = y_nxt;
                                visited.insert(pair(x, y));
                                found_next_char = true;
                                break;
                            }
                        }
                        if (!found_next_char)
                            break;
                    }
                    if (it == word.end())
                        return true;
                }
            }
        }
        return false;
    }
};

void reverse_string_proc() {
    string s;
    cin >> s;
    auto it_front = find_if(s.begin(), s.end(), [&](char c){
        return c != s.front();
    });
    auto front_repetitions = distance(s.begin(), it_front);
    cout << "front repetitions: " << front_repetitions << endl;
    auto it_back = find_if(s.rbegin(), s.rend(), [&](char c){
        return c != s.back();
    });
    auto back_repetitions = distance(s.rbegin(), it_back);
    cout << "back repetitions: " << back_repetitions << endl;
    if (back_repetitions < front_repetitions)
        reverse(s.begin(), s.end());
    cout << s << endl;
}

int main(int argc, char const *argv[])
{
    // reverse_string_proc();
    Solution sol;
    // int m, n;
    // cin >> m >> n;
    // vector<vector<char>> board (m, vector<char>(n, '-'));
    // for (int i = 0; i < m; i++)
    //     for (int j = 0; j < n; j++)
    //         cin >> board[i][j];
    // string word;
    // cin >> word;
    // vector<vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // vector<vector<char>> board = {{'C', 'A', 'A'}, {'A', 'A', 'A'}, {'B', 'C', 'D'}};
    
    /// Extremely slow if we don't use the reverse_string_proc() method
    vector<vector<char>> board =
        {{'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'C','A','A','A','A','A'},
        {'A','C','A','A','A','A'}};
    string word = "AAAAAAAAAAAAACC";
    auto start = chrono::high_resolution_clock::now();
    cout << sol.exist(board, word) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration_ms = (chrono::duration_cast<chrono::microseconds>(stop-start)).count() / 1000.0;
    cout << "execution: " << duration_ms << " ms" << endl;
    return 0;
}
