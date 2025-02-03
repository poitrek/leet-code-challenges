#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	/// Beats 100% on time
	/// Construct a reversed int by continually removing the last digit from the input value and appending
	/// it to the output variable. Then check if the original and reversed values are equal.
	bool isPalindrome(int x) {
		if (x < 0)
			return false;
		long x2 = x;
		long xrev = 0;
		while (x > 0) {
			xrev = (xrev * 10 + (x % 10));
			x /= 10;
		}
		return x2 == xrev;
	}

	/// Alternative, beats 16.35%
    bool isPalindrome2(int x) {
        if (x < 0)
            return false;
        vector<int> digits;
        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }
		const int n = digits.size();
		for (int i = 0; i < n * 0.5; i++) {
			if (digits[i] != digits[n - 1 - i])
				return false;
		}
		return true;
    }
};

/// 7
/// 3
/// 0,6 1,5 2,4 3,3

int main() {
	
	return 0;
}
