#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * Beats 100% on time, 86.10% on memory
 * Time complexity: O(N)
 * Space complexity: O(N) (auxiliary space O(1))
 */
class Solution {
public:
    string getHappyString(int n, int k) {
		int _2n1 = 1 << (n-1);
        if (k > 3 * _2n1)
			return "";
		unordered_map<char, array<char, 2>> other_symbol = {
			{'a', {'b', 'c'}},
			{'b', {'a', 'c'}},
			{'c', {'a', 'b'}}
		};
		// Convert to 0-indexed sequence
		k--;
		string result (n, ' ');
		result[0] = 'a' + (k / _2n1);
		k %= _2n1;
		for (int i = 1; i < n; i++) {
			result[i] = other_symbol[result[i-1]][k >> (n - 1 - i)];
			k %= (1 << (n - 1 - i));
		}
		return result;
    }
};

int main() {
	cout << Solution().getHappyString(4, 1) << endl;
	cout << Solution().getHappyString(4, 1) << endl;
	cout << Solution().getHappyString(4, 1) << endl;
	cout << Solution().getHappyString(4, 1) << endl;
	cout << Solution().getHappyString(4, 24) << endl;
	return 0;
}
