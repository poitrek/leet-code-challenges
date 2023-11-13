#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include "timer.hpp"

using namespace std;

class Solution {
public:
	// Complexity: O(n), providing that insert/erase operations on std::list are
	// constant, and all operations on unordered set/map are constant
    int firstUniqChar(string s) {
		// List of positions of unique characters
        list<int> uniq_positions;
		// Map {character c -> reference in uniq_positions of position of c in s}
		unordered_map<char, list<int>::iterator> unused_chars;
		// Set of not unique characters (seen at least twice)
		unordered_set<char> used_chars;
		for (int i = 0; i < s.size(); i++) {
			char c = s[i];
			if (used_chars.find(c) == used_chars.end()) {
				// If the character hasn't been seen yet
				if (unused_chars.find(c) == unused_chars.end()) {
					// Push back position on the list
					list<int>::iterator up_it = uniq_positions.insert(uniq_positions.end(), i);
					// Char c maps to the iterator of the list
					unused_chars[c] = up_it;
				}
				// If the character is seen for the second time
				else {
					uniq_positions.erase(unused_chars[c]);
					unused_chars.erase(c);
					used_chars.insert(c);
				}
			}
		}
		return uniq_positions.empty() ? -1 : uniq_positions.front();
    }

	// Simpler. Complexity O(n)
	int firstUniqChar2(string s) {
		unordered_map<char, int> uniq_char_idx;
		for (int i = 0; i < s.size(); i++) {
			if (uniq_char_idx.find(s[i]) == uniq_char_idx.end()) {
				uniq_char_idx[s[i]] = i;
			}
			else
				uniq_char_idx[s[i]] = INT_LEAST32_MAX;
		}
		int min_uniq_idx = INT_LEAST32_MAX;
		for (auto it : uniq_char_idx)
			min_uniq_idx = min(min_uniq_idx, it.second);
		return (min_uniq_idx == INT_LEAST32_MAX) ? -1 : min_uniq_idx;
	}
};

int main(){
	// string str (100000000, 'a');
	// Timer::start();
	// for (int i = 0; i < str.size(); i++) {
	// 	char c = str[i];
	// 	if (c == 'b')
	// 		cout << '.';
	// 	char x = c + 10 + c;
	// }
	// cout << "time: " << Timer::get_seconds();
	string s;
	cin >> s;
	cout << Solution().firstUniqChar2(s) << endl;
	return 0;
}
