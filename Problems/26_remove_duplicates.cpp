#include <iostream>
#include <vector>
using namespace std;

// Remove duplicates from sorted array
// Input: nums = [0,0,1,1,1,2,2,3,3,4]
// Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]


// Finds the position of the first value at least n
int binsearch(const vector<int> &v, int n) {
	int range_low = 1;
	int range_up = v.size() - 1;
	int range_mid ((range_low + range_up) / 2);
	while (!(v[range_mid] >= n && v[range_mid-1] < n)) {
		if (v[range_mid] < n) {
			// border case
			if (range_mid == v.size() - 2) {
				if (v[range_mid+1] == n)
					return range_mid+1;
				else
					return -1;
			}
			range_low = range_mid;
			range_mid = (range_low + range_up) / 2;
		}
		// v[range_mid-1] >= n
		else {
			// border case
			if (range_mid-1 == 0) {
				return 0;
			}
			range_up = range_mid;
			range_mid = (range_low + range_up) / 2;
		}
	}
	return range_mid;
}


// accepted
// Use binary search to find each next greater value in the sequence
// Time complexity: O(log(n)*k), k - number of unique elements
// time: above 97.9%
// memory: above 90.3%
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
		nums.push_back(1000);
		nums.push_back(1000);
        int k = nums.front();
        int k_index = 1;
        int next_index = 1;
        const int max_index = nums.size() - 1;
        k++;
        while (next_index < max_index) {
            // Find the next value at least k
            // int next_value;
            int range_low = next_index;
            int range_up = max_index;
            int range_mid = (range_low + range_up) / 2;
            while (true) {
                if (nums[range_mid] == k) {
                    // next_value = k;
                    next_index = range_mid;
                    break;
                }
                else if (nums[range_mid] < k) {
                    range_low = range_mid;
                    range_mid = (range_low + range_up) / 2;
                }
                else if (nums[range_mid-1] >= k) {
                    range_up = range_mid;
                    range_mid = (range_low + range_up) / 2;
                }
                // nums[range_mid] > k, nums[range_mid-1] < k
                else {
                    k = nums[range_mid];
                    next_index = range_mid;
                    break;
                }
            }
            nums[k_index] = k;
            // k = next_value + 1;
			k++;
            k_index++;
			next_index++;
        }
		nums.pop_back();
		nums.pop_back();
        return k_index-1;
    }
};

void print(vector<int> &v) {
	for (int i : v)
		cout << i << " ";
	cout << endl;
}

int main() {
	vector<int> v1 = {0,0,0,1,1,1,1,3,3,6,7,7,8,8,8,8,10,10,11,15,15,16};
	cout << Solution().removeDuplicates(v1) << ": ";
	print(v1);
	vector<int> v2 = {0, 0, 0, 1, 2, 3, 3, 4, 4};
	cout << Solution().removeDuplicates(v2) << ": ";
	print(v2);
	vector<int> v3 = {0};
	cout << Solution().removeDuplicates(v3) << ": ";
	print(v3);
	vector<int> v4 = {0, 10, 20};
	cout << Solution().removeDuplicates(v4) << ": ";
	print(v4);
	vector<int> v5 = {0, 10, 10, 10, 10, 10, 10};
	cout << Solution().removeDuplicates(v5) << ": ";
	print(v5);
	
	// cout << "2: " <<  binsearch(v1, 2) << endl;
	// cout << "0: " << binsearch(v1, 0) << endl;
	// cout << "-3: " << binsearch(v1, -3) << endl;
	// cout << "16: " << binsearch(v1, 16) << endl;
	// cout << "20: " << binsearch(v1, 20) << endl;
	
	return 0;
}
