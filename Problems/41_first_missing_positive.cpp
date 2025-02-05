#include <iostream>
#include <vector>

#include "vector_print.h"

using namespace std;

/**
 * Passes 100% runtime, O(N) time complexity, O(1) space.
 * Solution: transform the input sequence so that for each value x, if 0 < x <= N,
 * nums[x] = x  (technically nums[x-1] = x since vector is 0-indexed).
 * Although we cannot simply iterate over the values and assign nums[x-1] = x for each value x
 * in the sequence, because we may overwrite items we haven't read yet (at index higher than
 * current). Therefore we will repeat this procedure for value under nums[x-1] and so on,
 * until we encounter an item that is already at its proper position or not in the range [1, N].
 */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int start = 0; start < nums.size(); start++) {
            int idx = nums[start];
			while (idx > 0 && idx <= nums.size() && nums[idx - 1] != idx) {
				int new_idx = nums[idx - 1];
				nums[idx - 1] = idx;
				idx = new_idx;
			}
        }
		/// Guard to avoid checking the end of the vector
		nums.push_back(0);
        int idx = 1;
        while (nums[idx - 1] == idx)
            idx++;
        return idx;
    }
};

int main() {
	// vector<int> v {3, 5, 0, 1}; // 0 1 0 3
	vector<int> v {3, 4, -1, 1}; // 1 4 3 4
	cout << Solution().firstMissingPositive(v) << endl;
	cout << v << endl;
	return 0;
}
