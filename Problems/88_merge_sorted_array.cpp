#include <iostream>
#include <vector>
#include "common.hpp"

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i1 = m-1;
		int i2 = n-1;
		for (int k = m+n-1; k > -1; k--) {
			if (i1 < 0) {
				nums1[k] = nums2[i2];
				i2--;
			}
			else if (i2 < 0 || nums1[i1] > nums2[i2]) {
				nums1[k] = nums1[i1];
				i1--;
			}
			else {
				nums1[k] = nums2[i2];
				i2--;
			}
		}
    }
};

int main(){
	int n1, n2;
	cin >> n1 >> n2;
	vector<int> nums1(n1+n2, 0);
	vector<int> nums2(n2, 0);
	for (int i = 0; i < n1; i++)
		cin >> nums1[i];
	for (int i = 0; i < n2; i++)
		cin >> nums2[i];
	Solution().merge(nums1, n1, nums2, n2);
	cout << nums1 << endl;
	return 0;
}
