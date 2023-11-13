#include <iostream>
#include <vector>
#include <unordered_map>
#include "common.hpp"

using namespace std;

class Solution {
public:
	// O(n) time, O(1) space
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_idx;
		for (int i = 0; i < nums.size(); i++) {
			auto n_j = num_idx.find(target - nums[i]);
			if (n_j != num_idx.end())
				return {n_j->second, i};
			num_idx[nums[i]] = i;
		}
		return {};
    }
};

int main(){
	int n;
	cin >> n;
	vector<int> nums(n, 0);
	for (int i = 0; i < n; i++) 
		cin >> nums[i];
	int target;
	cin >> target;
	cout << Solution().twoSum(nums, target) << endl;
	return 0;
}
