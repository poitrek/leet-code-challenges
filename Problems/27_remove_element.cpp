#include <iostream>
#include <vector>

using namespace std;

// accepted
// time 0 ms (beats 100%)
// memory 8.7 MB (beats 87.3%)
// Changes the relative order of the elements kept
// +performs the minimum needed assign operations (?)
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int front_index = 0;
        int back_index = nums.size() - 1;
        while (front_index <= back_index) {
            if (nums[front_index] == val) {
                while (nums[back_index] == val && front_index < back_index) {
                    back_index--;
                }
                nums[front_index] = nums[back_index];
                back_index--;
            }
            front_index++;
        }
        return back_index + 1;
    }
};

// someone else's solution
// +simpler
// +does not change the relative order of the elements kept
// -performs more assign operations than my algorithm
class Solution2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;

        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != val){
                nums[k] = nums[i];
                k = k + 1;
            }
        }
        return k;
    }
};


int main() {
	
	return 0;
}
