#include <iostream>
#include <vector>

#include "vector_print.h"

using namespace std;

class Solution {
public:

	/// Recursive, first solution idea (remove last element, generate permutations for the remaining,
	/// for each permutation new permutations by adding removed element at each position)
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 1)
            return {nums};
        int last = nums.back();
        nums.pop_back();
        auto perm_previous = permute(nums);
        vector<vector<int>> result;
        for (auto &perm : perm_previous) {
            for (auto it = perm.begin(); it != perm.end(); ++it) {
				it = perm.insert(it, last);
				count++;
				result.push_back(perm);
				it = perm.erase(it);
			}
			perm.push_back(last);
			count++;
			result.push_back(perm);
			perm.pop_back();
        }
        return result;
    }

	/// Same solution but iterative. Save only permutations for previous sequence (without last element)
    vector<vector<int>> permute_iterative(vector<int>& nums) {
		vector<vector<int>> perm { { nums.front() }};
		for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
    		vector<vector<int>> perm_next;
			for (auto &p : perm) {
				for (auto pit = p.begin(); pit != p.end(); ++pit) {
					pit = p.insert(pit, *it);
					perm_next.push_back(p);
					pit = p.erase(pit);
				}
				p.push_back(*it);
				perm_next.push_back(p);
				p.pop_back();
			}
			perm = perm_next;
		}
		return perm;
	}

	int count = 0;

	/// Generate in lexicographical order - assuming the input is *sorted* ascendingly
    vector<vector<int>> permute_lexicographical(vector<int>& nums) {
		if (nums.size() == 1)
			return {{ nums.front() }};
		vector<vector<int>> perms;
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			int value = *it;
			it = nums.erase(it);
			auto perms_removed = permute_lexicographical(nums);
			for (auto &pr : perms_removed) {
				pr.insert(pr.begin(), value);
				perms.push_back(pr);
				count++;
			}
			nums.insert(it, value);
		}
		return perms;
	}

};

int main() {
	vector<int> v {1, 2, 3, 4, 5};
	Solution sol;
	cout << sol.permute(v) << endl;
	cout << sol.count << endl;
	// std:vector<int> v = { 2, 3, 5 };
	// auto p = Solution().permute(v);
	// cout << p.size() << ": " << p << endl;
	// for (auto it = v.begin(); it != v.end(); ++it) {
	// 	// cout << "1: " << v << endl;
	// 	it = v.insert(it, 10);
	// 	cout << "2: " << v << endl;
	// 	it = v.erase(it);
	// 	// cout << "3: " << v << endl;
	// }
	return 0;
}
