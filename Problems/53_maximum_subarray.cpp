#include <iostream>
#include "common.hpp"

using namespace std;

class Solution {
public:
	// O(n) time complexity, O(1) space
	int maxSubArray(vector<int>& nums) {
		int max_global = nums.front();
		int max_local = max_global;
		int local_sum = 0;
		for (int n : nums) {
			local_sum += n;
			if (local_sum > max_local)
				max_local = local_sum;
			if (local_sum < 0) {
				if (max_local > max_global)
					max_global = max_local;
				local_sum = 0;
				max_local = n;
			}
		}
		if (max_local > max_global)
			max_global = max_local;
		return max_global;
	}

	// O(n^2) time complexity
    int maxSubArray1(vector<int>& nums) {
		nums = optimizeArr(nums);
		int max_sum = nums.front();
		for (int i = 0; i < nums.size(); i++) {
			int subsum = 0;
			for (int j = i; j < nums.size(); j++) {
				subsum += nums[j];
				if (subsum > max_sum)
					max_sum = subsum;
			}
		}
		return max_sum;
    }

	vector<int> optimizeArr(const vector<int> &arr) {
        vector<int> arr_opt;
		int sgn = (arr.front() > 0);
		int tmp_sum = 0;
		int max_el = arr.front();
		for (int n : arr) {
			if (n > max_el)
				max_el = n;
			int sgn_nxt = (n > 0);
			if (sgn_nxt == sgn) {
				tmp_sum += n;
			}
			else {
				arr_opt.push_back(tmp_sum);
				sgn = sgn_nxt;
				tmp_sum = n;
			}
		}
		arr_opt.push_back(tmp_sum);
		if (arr_opt.size() == 1 && arr_opt.front() < 0)
			return {max_el};
		else
			return arr_opt;
	}
};

int main(){
	int n;
	cin >> n;
	vector<int> nums(n, 0);
	for (int i = 0; i < n; i++) 
		cin >> nums[i];
	cout << Solution().maxSubArray(nums) << endl;
	return 0;
}
