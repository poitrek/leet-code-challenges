#include <iostream>

using namespace std;

/* Idea: find such n that n*n == x. Use binary search.
*/
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0)
            return 0;
        long low = 0;
        long up = long(x) + 1;
        while (up - low > 1) {
            long mid = (low + up) * 0.5;
            long mid2 = mid * mid;
            if (mid2 > x) {
                up = mid;
            }
            else if (mid2 == x)
                return mid;
            else
                low = mid;
        }
        return low;
    }
};

int main() {
	return 0;
}
