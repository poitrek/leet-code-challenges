#include <iostream>
#include <vector>
#include <algorithm>
#include "common.hpp"
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		// Idea: sort both arrays first
		// Time: O(mlog(m)+nlog(n)+m+n) = O(mlog(m)+nlog(n))
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		nums1.push_back(INT_LEAST32_MAX);
		nums2.push_back(INT_LEAST32_MAX);
		vector<int> nums_ins;
		nums_ins.push_back(-1);
		int i1 = 0, i2 = 0;
		while (i1 < nums1.size()-1 || i2 < nums2.size()-1) {
			int n1 = nums1[i1], n2 = nums2[i2];
			if (n1 < n2) {
				i1++;
			}
			else if (n1 > n2) {
				i2++;
			}
			else {
				// Use this line in order to keep distinct values
				// in the resulting vector
				// if (nums_ins.back() != n1)
				nums_ins.push_back(n1);
				i1++, i2++;
			}
		}
		nums_ins.erase(nums_ins.begin());
		return nums_ins;
    }
};

int main() {
	int n1, n2;
	cin >> n1;
	vector<int> nums1(n1);
	for (int i = 0; i < n1; i++)
		cin >> nums1[i];
	cin >> n2;
	vector<int> nums2(n2);
	for (int i = 0; i < n2; i++)
		cin >> nums2[i];
	cout << Solution().intersect(nums1, nums2) << endl;
	return 0;
}
