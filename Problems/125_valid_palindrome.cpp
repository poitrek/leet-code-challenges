#include <iostream>
#include <string>

using namespace std;


/**
 * @brief Idea: solution could be brokedn down into 2 stages: removing irrelevant (non-alphanumeric)
 * characters from the string, then checking palindrome validity by comparing s[i] == s[n-1-i]. (n - size of s)
 * However, erasing from string is costly. Instead, ignore non-alphanumeric characters simultaneously with
 * comparing corresponding alphanumeric characters.
 */
class Solution {
	public:
		static constexpr int case_diff = 'A' - 'a';
		bool isAlphanumeric(char c) {
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
		}
		char toLower(char c) {
			if (c >= 'A' && c <= 'Z')
				return c - case_diff;
			else return c;
		}
	
		bool isPalindrome(string s) {
			int i = 0, j = s.size() - 1;
			while (i < j) {
				if (!isAlphanumeric(s[i])) {
					i++;
					continue;
				}
				if (!isAlphanumeric(s[j])) {
					j--;
					continue;
				}
				if (toLower(s[i]) != toLower(s[j]))
					return false;
				else {
					i++;
					j--;
				}
			}
			return true;
		}
	};

int main() {

	return 0;
}
