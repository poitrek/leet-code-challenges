#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        auto it = digits.rbegin();
        while (it != digits.rend() && *it == 9) {
            *it = 0;
            it++;
        }
        if (it == digits.rend()) {
            digits.insert(digits.begin(), 1);
            return digits;
        }
        else {
            (*it)++;
            return digits;
        }
    }
};

int main() {
	return 0;
}
