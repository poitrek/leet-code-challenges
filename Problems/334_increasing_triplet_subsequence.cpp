#include <iostream>
#include <vector>
#include <climits>
#define FOR(var, start, stop) for (int var = start; var < stop; var++)

using namespace std;

class Solution {
public:
	/* CORRECT
	Iterate through the sequence once. In each step, save two values:
	- the minimum value so far (min_tm)
	- the minimum value so far such that there exists a smaller value before it (min_tj)
	If current value > min_tj - there exists an increasing triplet.

	Proof: (==>) assume i < j < k, and t[i] < t[j] < t[k]. We assume that min_tj correctly stores 
	the minimum value such that there was a smaller one before it. When the iteration 
	reaches t[k] (num == t[k]), by definition min_tj <= t[j], so min_tj < t[k] == num. Hence
	the algorithm returns true as it should.
	(<==) assuming min_tj is computed correctly according to the definition, if at some iteration
	num > min_tj, there is a value smaller than min_tj before it, and a greater value after it (num),
	hence the increasing triplets exists. 
	*/
	bool increasingTriplet(vector<int>& nums) {
		int min_tj = INT_MAX;
		int min_tm = nums.front();
		for (int num : nums) {
			if (num <= min_tm)
				min_tm = num;
			else if (num > min_tj)
				return true;
			else
			/// min_tm < num <= min_tj
				min_tj = num;
		}
		return false;
	}
	/// First try, not working
    bool increasingTriplet_v0(vector<int>& nums) {
        int smaller = INT_MAX;
		int greater = INT_MAX;
		bool found_pair = false;
		FOR(i, 0, nums.size() - 1) {
			int n_i = nums[i];
			int n_i1 = nums[i+1];
			if (found_pair)
				if (n_i1 > greater)
					return true;
			if (n_i1 > n_i) {
				found_pair = true;
				if (n_i1 < greater) {
					smaller = nums[i];
					greater = nums[i+1];
				}
			}
		}
		return false;
    }
	/// Second try, not working
	bool increasingTriplet_v01(vector<int>& nums) {
		int min_first = nums[0];
		FOR(i, 0, nums.size()-2) {
			min_first = min(min_first, nums[i]);
			if (nums[i+1] < nums[i+2] && min_first < nums[i+1])
				return true;
		}
		return false;
	}
};

int main() {
	int n;
	cin >> n;
	// FOR(i, 1, 10)
	// 	cout << i << " ";
	// cout << endl;
	vector<int> v(n);
	FOR(i, 0, n)
		cin >> v[i];
	cout << Solution().increasingTriplet(v) << endl;
	return 0;
}
