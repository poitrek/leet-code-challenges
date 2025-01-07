#include <iostream>
#include <string>
#include <vector>

#include "common.hpp"

using namespace std;

class Solution {
public:
    const vector<string> letters = {
        "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    vector<string> letterCombinations(string digits) {
		if (digits.size() == 0)
			return vector<string>();
		vector<int> i_digits;
		for (char c : digits)
			i_digits.push_back(int(c - '0') - 2);
		i_digits.push_back(2);
        int n_digits = digits.size();
        vector<int> index (n_digits+1, 0);
        vector<string> words;
        while (index.back() == 0) {
            string word;
            // make the word from the letter indexes
            for (int i = 0; i < n_digits; i++) {
                word.push_back(letters[i_digits[i]][index[i]]);
            }
            words.push_back(word);
            // increment the index
            int i = 0;
            while (index[i] == letters[i_digits[i]].size()-1) {
                index[i] = 0;
                i++;
            }
			index[i]++;
        }
		return words;
    }
};

int main() {
	cout << "hello" << endl;
	cout << Solution().letterCombinations("") << endl;
	cout << Solution().letterCombinations("33") << endl;
	cout << Solution().letterCombinations("734") << endl;
	cout << "done" << endl;
	return 0;
}
