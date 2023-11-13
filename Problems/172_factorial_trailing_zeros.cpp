#include <iostream>

using namespace std;

// Complexity: log5(n)
// In the product 1*2*...*n we count how many pairs of prime factors 2 and 5 are included - each of
// them (and only such pairs) produces a leading '0' in the product. Since there are always more
// 2s then 5s, we only count the 5s. Each multiple of 5 introduces a 5-factor, but also every multiple
// of 25 introduces two 5-factors, every multiple of 5^3 introduces three 5-factors, and so on. Alternatively,
// for each 5 consecutive multiples of 5^k, a 5^(k+1) multiple appears. Thus dividing n by 5 without
// remainder, we get the number of multiples of 5 less or equal n, dividing by 25, we get the number of
// multiples of 25 less or equal n, and so on.
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        while (n > 0) {
            n /= 5;
            res += n;
        }
        return res;
    }
};

int main() {

	return 0;
}
