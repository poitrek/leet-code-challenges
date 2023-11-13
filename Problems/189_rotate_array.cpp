#include <iostream>
#include <vector>
#include "common.hpp"

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
		k %= nums.size();
        nums.insert(nums.begin(), nums.begin()+nums.size()-k, nums.end());
		nums.erase(nums.begin()+nums.size()-k, nums.end());
    }
};


int main() {
	std::vector v = {1, 2, 3};
	Solution().rotate(v, 1);
	cout << v << endl;
	return 0;
}
