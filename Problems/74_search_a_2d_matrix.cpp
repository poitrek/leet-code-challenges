#include <iostream>
#include "common.hpp"

using namespace std;

class Solution {
public:
	// binary search twice (better)
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
		matrix.push_back({INT_LEAST32_MAX});
		int down = 0, up = matrix.size()-1, mid = up / 2;
		while (up - down > 1) {
			int mid_f = matrix[mid].front();
			if (mid_f > target)
				up = mid;
			else if (mid_f < target)
				down = mid;
			else
				return true;
			mid = (up+down)/2;
		}
		// target should be in matrix[down]
		int i = down;
		down = 0, up = matrix.front().size()-1, mid = up / 2;
		while (up - down > 1) {
			int mid_f = matrix[i][mid];
			if (mid_f > target)
				up = mid;
			else if (mid_f < target)
				down = mid;
			else
				return true;
			mid = (up+down)/2;
		}
		return (target == matrix[i][down] || target == matrix[i][up]);

    }
	// linear search twice
    bool searchMatrix_1(vector<vector<int>>& matrix, int target) {
	    int i = 0;
		matrix.push_back({INT_LEAST32_MAX});
		while (matrix[i].front() <= target)
			i++;
		if (i == 0) // target was smaller than the very first element
			return false;
		i--;
		matrix[i].push_back(INT_LEAST32_MAX);
		int j = 0;
		while (matrix[i][j] < target)
			j++;
		return (matrix[i][j] == target);}
};

int main(){

	return 0;
}
