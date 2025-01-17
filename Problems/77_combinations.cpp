#include <iostream>
#include <vector>

#include "vector_print.h"

using namespace std;

class Solution {
public:

	/// First solution, recursive. Generate C(n, k-1), for each combination, generate
	/// new ones by adding each number between last (highest) value in the combination
	/// and n.
	/// Time complexity: O(c(n,1) + c(n,2) + c(n,3) + ... + c(n,k)), where c(n,i) is the
	/// number of i-combinations of an n-element set (size of C(n,i)), and we need to generate those
	/// combinations for each i=1,2,...,k.
	/// Beats 19.51% on time :/
    vector<vector<int>> combine(int n, int k) {
        if (k == 1) {
            vector<vector<int>> result;
            for (int i = 1; i <= n; i++)
                result.push_back({i});
            return result;
        }
        vector<vector<int>> result;
        for (auto &c : combine(n, k-1)) {
            for (int i = c.back() + 1; i <= n; i++) {
                c.push_back(i);
                result.push_back(c);
                c.pop_back();
            }
        }
        return result;
    }

	/// First solution, iteratively. Remember only C(n,i-1) when calculating C(n,i)
    vector<vector<int>> combine_ite(int n, int k) {
		vector<vector<int>> combinations;
		for (int i = 1; i <= n; i++)
			combinations.push_back({i});
		for (int i = 2; i <= k; i++) {
			vector<vector<int>> new_combinations;
			for (auto &c : combinations) {
				for (int j = c.back() + 1; j <= n; j++) {
                    c.push_back(j);
                    new_combinations.push_back(c);
                    c.pop_back();
                }
			}
			combinations = std::move(new_combinations);
		}
		return combinations;
    }

	/// Second solution. BEATS 99.96 % on time
	/// Instead of producing combinations for consequent sizes of subsets (i=1,2,...,k), use one
	/// vector of k values and update them. Notice that the problem is equivalent to generating
	/// all strongly increasing sequences of k numbers from 1..n. We start with sequence
	/// 1,2,...,k. We start by incrementing last element till n, leaving all the previous unchanged.
	/// Once last element reaches n, increment the previous element and set the last one to previous+1
	/// (as the sequence has to be increasing). Repeat the procedure until all elements reach their
	/// correct maximum values.
	/// Time complexity: ??
    vector<vector<int>> combine2(int n, int k) {
		vector<vector<int>> combinations;
		vector<int> comb;
		for (int i = 1; i <= k; i++) {
			comb.push_back(i);
		}
		combinations.push_back(comb);
		while (true) {
			int index = k-1;
			/// The highest value this index will reach in a correct combination
			while (index >= 0 && comb[index] == n - (k - 1 - index))
				index--;
			if (index < 0)
				break;
			int next_val = comb[index];
			while (index < k) {
				comb[index++] = ++next_val;
			}
			combinations.push_back(comb);
		}
		return combinations;
    }

};

int main() {
	cout << Solution().combine2(9, 3) << endl;
	int x = 5;
	x = x++;
	cout << x << endl;
	return 0;
}
