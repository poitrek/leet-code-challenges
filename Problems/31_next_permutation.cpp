#include <algorithm>
#include <vector>

using namespace std;

/**
 * Time complexity: O(N), space complexity: O(1)
 */

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1)
            return;
        /// starting from the back, find the first element that is smaller than its predecessor
		/// (or until we reach the front)
        auto it = nums.rbegin();
		while (it + 1 != nums.rend() && *(it + 1) >= *it)
            ++it;
        if (it + 1 == nums.rend()) {
            std::reverse(nums.begin(), nums.end());
            return;
        }
        /// find the first element from the sequence following it+1 which is greater
        auto first_greater_it = std::upper_bound(nums.rbegin(), it + 1, *(it + 1));
        std::swap(*(it+1), *first_greater_it);
        std::reverse(nums.rbegin(), it+1);
    }
};


int main() {

	return 0;
}
