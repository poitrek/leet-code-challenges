#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
		if (n == -2147483648)
            return 1 / x * myPow(x, n+1);
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
		double result = 1;
		while (n > 0) {
			/// test if n is odd
			if (n & 1 == 1)
				result *= x;
			x = x*x;
			/// multiply by 2
			n >>= 1;
		}
		return result;
    }

    double myPow2(double x, int n) {
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        vector<double> powers { x };
		for (int k = 2; k <= n; k <<= 1) {
			x = x * x;
			powers.push_back(x);
		}
		return 0;
    }
};

void print_bin(int n) {
	while (n > 0) {
		cout << n % 2;
		n >>= 1;
	}
	cout << endl;
}

int main() {
	cout << Solution().myPow(2, 0) << endl;
	cout << Solution().myPow(2, 1) << endl;
	cout << Solution().myPow(2, 2) << endl;
	cout << Solution().myPow(2.0, 11) << endl;
	cout << Solution().myPow(1.5, 3) << endl;
	cout << Solution().myPow(1.1415, 19) << endl;
	cout << Solution().myPow(2.14, -7) << endl;

	cout << (-11 << 1) << endl;
	cout << (-11 >> 1) << endl;

	cout << (11 << 1) << endl;
	cout << (11 >> 1) << endl;

	int x = -123;
	for (int i = 0; i < 10; i++) {
		cout << x << " ";
		x >>= 1;
	}

	// int k = 5;
	// for (int i = 1; i <= 0b1000000; i <<= 1) {
	// 	cout << i << " ";
	// }
	// cout << endl;
	// cout << (k << 1) << endl;
	// cout << (k << 2) << endl;
	// cout << (k << 3) << endl;
	// cout << (k >> 1) << endl;
	// print_bin(30);
	// print_bin(5);
	// print_bin(11);
	return 0;
}
