#include <iostream>
#include <vector>
#include "common.hpp"

using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
		int p = m * n;
		if (r * c != p)
			return mat;
		vector<vector<int>> mat_r (r, vector<int>(c, 0));
		for (int i = 0; i < p; i++) {
			mat_r[i / c][i % c] = mat[i / n][i % n];
		}
		return mat_r;
    }
};

int main(){
	vector<vector<int>> mat;
	read2d(mat);
	int r, c;
	cin >> r >> c;
	cout << Solution().matrixReshape(mat, r, c) << endl;
	return 0;
}
