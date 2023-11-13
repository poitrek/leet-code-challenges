#include <iostream>
#include <vector>
#include "common.hpp"

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_e = prices.front();
		int max_dif = 0;
		for (int p : prices) {
			if (p < min_e)
				min_e = p;
			else if (p - min_e > max_dif) {
				max_dif = p - min_e;
			}
		}
		return max_dif;
    }
};

int main(){
	vector<int> prices;
	read<int>(prices);
	cout << Solution().maxProfit(prices);
	return 0;
}
