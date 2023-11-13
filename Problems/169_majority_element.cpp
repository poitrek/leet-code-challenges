#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * Took 3-4 mins.
 * Time: beats 54.3%
 * Memory: beats 94%
 */
class Solution2 {
public:
	int majorityElement(vector<int>& nums) {
		unordered_map<int, int> cnt;
		// floor{n/2}
		int half_size = nums.size() / 2;
		for (int i = 0; i < nums.size(); i++) {
			int n_i = nums[i];
			if (cnt.find(n_i) == cnt.end()) {
				cnt[n_i] = 1;
			}
			else {
				cnt[n_i]++;
			}
			if (cnt[n_i] > half_size)
				return n_i;
		}
		return -1;
	}
};

/**
 * Moore Voting Algorithm - probably the best one for this problem. O(n) time and O(1) space. 
 * Extremely simple implementation.
 * 
 */
class Solution3 {
public:
	int majorityElement(vector<int>& nums) {
		int cur_major = 0;
		int cur_major_cnt = 0;
		for (int i : nums) {
			if (cur_major_cnt == 0) {
				cur_major = i;
				cur_major_cnt = 1;
			}
			else if (i == cur_major)
				cur_major_cnt++;
			else
				cur_major_cnt--;
		}
		return cur_major;
	}
};

/**
 * Took ~6h. In theory should have O(n) time and stop iterating
 * through the input vector as soon as it is possible (by checking the minimum
 * sufficient number of values))
 * Time: beats 21.37% :( :O
 * Memory: beats 13% :(
 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
		unordered_map<int, int> cnt;
		vector<int> cnt2 { 0 };
		int second_majorant_idx = 0;
		int majorant_cnt_idx_cutoff = -(ceil(nums.size() * 0.5) - 1);
		int majorant_element;
		for (int i = 0; i < nums.size(); i++) {
			int n_i = nums[i];
			int cnt_i;
			if (cnt.find(n_i) == cnt.end()) {
				cnt[n_i] = 1;
				cnt_i = 0;
			}
			else {
				cnt_i = cnt[n_i]++;
			}
			cnt2[cnt_i]--;
			if (cnt2.size()-1 < cnt_i+1) {
				cnt2.push_back(1);
				majorant_element = n_i;
			}
			else
				cnt2[cnt_i+1]++;
			if (cnt2.size() == 2)
				second_majorant_idx = 1;
			else {
				// If we're updating a count at the 2nd majorant index, possibly change it
				if (cnt_i == second_majorant_idx)
					if (cnt_i <= cnt2.size()-2)
						second_majorant_idx++;
				}
			if (majorant_cnt_idx_cutoff == second_majorant_idx) {
				// the majorant element is known
				return majorant_element;
			}
			majorant_cnt_idx_cutoff++;
		}
		return majorant_element;
    }
};

int main() {
	// unordered_map<int, int> m = {{0, 0}};
	// int y = m[0]++;
	// cout << m[0] << " " << y;
	// vector<int> v = {0, 1, 2, 2, 1, 0, 2, 2, 2, 1, 1, 2, 2};
	// vector<int> v = {0, 1, 0, 1, 0, 1, 1, 0, 0};
	// vector<int> v = {0, 3, 1, 3, 3};
	vector<int> v = {3};
	cout << Solution2().majorityElement(v) << endl;
	return 0;
}
