#include <iostream>
#include "common.hpp"

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 1)
            return {{1}};
        vector<vector<int>> p {{1}, {1, 1}};
		for (int i = 2; i < numRows; i++) {
			vector<int> pr (i+1, 1);
			for (int j = 1; j < i; j++)
				pr[j] = p.back()[j-1] + p.back()[j];
			p.push_back(pr);
		}
		return p;
    }
};

int main(){
	cout << Solution().generate(7) << endl;
	return 0;
}
