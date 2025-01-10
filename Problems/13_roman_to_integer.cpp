#include <iostream>
#include <string>

using namespace std;

/**
 * Idea: assuming the input string is a correct Roman integer, each letter can be mapped to a specific number
 * which will be added to the resulting number, except 'IV', 'IX', 'XL', 'XC', 'CD' and 'CM'.
 * Therefore, if current symbol is 'I', 'X' or 'C', we first check if the following symbol is one of the
 * mentioned, and increment the iterator again. For example, in case of 'CD', add 400 and skip the processing
 * of 'D' as it is already a part of 'CD'. When processing 'D' alone, we add 500 since it is aasured that
 * it wasn't preceded by a 'C'. Identically for other corresponding letters.
 * 
 * Time complexity: O(N), space complexity: O(1)
 */

class Solution {
public:
    int romanToInt(string s) {
        int n = 0;
		/// guard symbol to avoid checking if the "following" is out of range
        s.push_back('.');
        for (auto it = s.begin(); it != s.end() - 1; ++it) {
            if (*it == 'M')
                n += 1000;
            else if (*it == 'D')
                n += 500;
            else if (*it == 'C')
                if (*(it + 1) == 'D') {
                    n += 400;
                    ++it;
                }
                else if (*(it + 1) == 'M') {
                    n += 900;
                    ++it;
                }
                else
                    n += 100;
            else if (*it == 'L')
                n += 50;
            else if (*it == 'X')
                if (*(it + 1) == 'L') {
                    n += 40;
                    ++it;
                }
                else if (*(it + 1) == 'C') {
                    n += 90;
                    ++it;
                }
                else
                    n += 10;
            else if (*it == 'V')
                n += 5;
            else if (*it == 'I')
                if (*(it + 1) == 'V') {
                    n += 4;
                    ++it;
                }
                else if (*(it + 1) == 'X') {
                    n += 9;
                    ++it;
                }
                else
                    n += 1;
            else
                throw "Invalid symbol";
        }
        return n;        
    }
};

int main() {

	return 0;
}
