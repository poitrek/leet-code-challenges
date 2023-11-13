#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> numset;
        for (int n : nums) {
			if (numset.find(n) == numset.end()) {
				numset.insert(n);
			}
			else {
				return true;
			}
		}
		return false;
    }

	bool containsNearbyDuplicate(vector<int> &nums, int k) {
		if (k >= nums.size())
			k = nums.size() - 1;
		unordered_set<int> numset (nums.begin(), nums.begin() + k);
		if (numset.size() < k)
			return true;
		for (int i = 0; i < nums.size() - k; i++) {
			if (numset.find(nums[i+k]) != numset.end())
				return true;
			else {
				numset.insert(nums[i+k]);
				numset.erase(nums[i]);
			}
		}
		return false;
	}

	bool containsNearbyDuplicate_2(vector<int> &nums, int k) {
		if (k >= nums.size())
			k = nums.size() - 1;
		unordered_map<int, int> numset;
		for (int i = 0; i < k; i++)
			numset[nums[i]] = 1;
		if (numset.size() < k)
			return true;
		for (int i = 0; i < nums.size() - k; i++) {
			int num = nums[i+k];
			if (numset.find(num) != numset.end() && numset[num] > 0)
				return true;
			else {
				numset[num] = 1;
				numset[nums[i]] = 0;
			}
		}
		return false;
	}

	// bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        
    // }
};

int main(){
	// int n;
	// cin >> n;
	// vector<int> v(n, 0);
	// for (int i = 0; i < n; i++)
	// 	cin >> v[i];
	// int k;
	// cin >> k;
	vector<int> v;
	for (int i = 0; i < 1000*10000; i++)
		v.push_back(i);
	int k = 20;
	auto start = high_resolution_clock::now();
	cout << Solution().containsNearbyDuplicate_2(v, k) << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start).count();
	cout << "Calculation time: " << duration << " ms" << endl;
	// cout << Solution().containsDuplicate(v) << endl;
	return 0;
}
