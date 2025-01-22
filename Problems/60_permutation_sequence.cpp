#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "timer.hpp"
#include "vector_print.h"

using namespace std;

using ull = unsigned long long;

class Solution {
public:
    string getPermutation(int n, int k) {
		vector<int> factorial {1};
		/// compute the factorials up to n-1
		for (int i = 1; i <= n-1; i++) {
			factorial.push_back(factorial.back() * i);
		}
		k--;
		vector<int> permutation_items;
		for (int i = 1; i <= n; i++)
			permutation_items.push_back(i);
		string permutation;
		for (int i = n-1; i >= 0; i--) {
			int item_index = k / factorial[i];
			auto next_to_perm = permutation_items.begin() + item_index;
			permutation.push_back('0' + *next_to_perm);
			permutation_items.erase(next_to_perm);
			k %= factorial[i];
		}
		return permutation;
    }

	vector<int> getPermutationL(int n, ull k) {
		vector<ull> factorial {1};
		/// compute the factorials up to n-1
		for (ull i = 1; i <= n-1; i++) {
			factorial.push_back(factorial.back() * i);
		}
		list<int> permutation_items;
		for (int i = 1; i <= n; i++)
			permutation_items.push_back(i);
		vector<int> permutation;
		for (int i = n-1; i >= 0; i--) {
			int item_index = k / factorial[i];
			auto next_to_perm = next(permutation_items.begin(), item_index);
			permutation.push_back(*next_to_perm);
			permutation_items.erase(next_to_perm);
			k %= factorial[i];
		}
		return permutation;
    }

	vector<int> getPermutationV(int n, ull k) {
		vector<ull> factorial {1};
		/// compute the factorials up to n-1
		for (ull i = 1; i <= n-1; i++) {
			factorial.push_back(factorial.back() * i);
		}
		vector<int> permutation_items;
		for (int i = 1; i <= n; i++)
			permutation_items.push_back(i);
		vector<int> permutation;
		for (int i = n-1; i >= 0; i--) {
			int item_index = k / factorial[i];
			auto next_to_perm = permutation_items.begin() + item_index;
			permutation.push_back(*next_to_perm);
			permutation_items.erase(next_to_perm);
			k %= factorial[i];
		}
		return permutation;
    }
};

void test_time() {
	Solution s;
	Timer::start();
	const int n_iterations = 1;
	for (int it = 0; it < n_iterations; it++) {
		for (ull k = 0; k < 1000000; k++) {
			s.getPermutationL(15, k);
		}
	}
	cout << Timer::get_seconds() << endl;
}

int main() {
	test_time();
	// Solution sol;
	// cout << sol.getPermutationV(10, 20000) << endl;
	// for (int k = 1; k <= 24; k++)
	// 	cout << sol.getPermutationV(4, k) << endl;
	return 0;
}
