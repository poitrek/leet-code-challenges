#include <iostream>

using namespace std;

class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;
        int tn_3 = 0, tn_2 = 1, tn_1 = 1, tn;
        for (int i = 0; i <= n - 3; i++) {
            tn = tn_1 + tn_2 + tn_3;
            tn_3 = tn_2;
            tn_2 = tn_1;
            tn_1 = tn;
        }
        return tn;
    }
};

int main() {

	return 0;
}
