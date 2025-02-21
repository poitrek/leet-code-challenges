#include <iostream>
#include <string>

using namespace std;

/**
 * Beats 100% on time. Can be optimized to not add the leading zeros to the lesser number, will
 * be slightly more complicated to implement but a lot more efficient when the input is one 
 * very large and one very small number.
 */
class Solution {
public:
    string addBinary(string a, string b) {
		cout << a << endl << b << endl;
        /// Make sure a is longer or equal to b
        if (a.size() < b.size())
            swap(a, b);
        /// Guard digit to avoid checking the beginning of the string
        a.insert(a.begin(), '0');
        /// Add leading zeros to b for easier computation
        b.insert(b.begin(), a.size() - b.size(), '0');
        bool carry = false;
        for (auto a_it = a.rbegin(), b_it = b.rbegin(); a_it != a.rend(); ++a_it, ++b_it) {
            int digit_sum = carry + (*a_it - '0') + (*b_it - '0');
			carry = (digit_sum >= 2);
			int new_digit = digit_sum % 2;
			*a_it = new_digit + '0';
        }
		if (a.front() == '0')
			a.erase(a.begin());
		return a;
    }
};

int main() {
	cout << Solution().addBinary("1", "1") << endl;
	return 0;
}
