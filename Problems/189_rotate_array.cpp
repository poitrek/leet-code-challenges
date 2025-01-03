#include <algorithm>
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

class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        unsigned int n_front_move = nums.size() - (k % nums.size());
        std::vector<int> nums_rot (nums.begin() + n_front_move, nums.end());
        std::move(nums.begin(), nums.begin() + n_front_move, std::back_inserter(nums_rot));
        nums = std::move(nums_rot);
    }
};

/// rotate using reversing
class Solution3 {
public:
    void rotate(vector<int>& nums, int k) {
		k %= nums.size();
		std::reverse(nums.begin(), nums.end());
		std::reverse(nums.begin(), nums.begin() + k);
		std::reverse(nums.begin() + k, nums.end());
    }
};



int main() {
	std::vector v = {1, 2, 3};
	Solution().rotate(v, 1);
	cout << v << endl;
	return 0;
}
