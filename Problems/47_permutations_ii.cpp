#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>

#include "timer.hpp"
#include "vector_print.h"

using namespace std;


class CombinationGenerator{
public:
	/// @brief Generate k-element combinations from set 0,1,...n-1
	static vector<vector<int>> generate(int n, int k) {
		if (n < k)
			throw "Error: combination size: " + to_string(k) + " is greater than n: " + to_string(n);
		vector<vector<int>> combinations;
		vector<int> comb;
		for (int i = 0; i < k; i++) {
			comb.push_back(i);
		}
		combinations.push_back(comb);
		while (true) {
			int index = k-1;
			/// The highest value this index will reach in a correct combination
			while (index >= 0 && comb[index] == n - (k - index))
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

class Solution {
public:
	/// Solution 1.
    vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> perms { {} };
		for (int num : nums) {
			vector<vector<int>> new_perms;
			for (auto &perm : perms) {
				auto it = std::find(perm.begin(), perm.end(), num);
				while (it != perm.begin() - 1) {
					it = perm.insert(it, num);
					new_perms.push_back(perm);
					it = perm.erase(it);
					--it;
				}
			}
			// perms = new_perms;
			/// Faster, for 9 elements 8.27 -> 5.31 s,
			/// for 12 elements 312.5 -> 79.4 s
			perms = std::move(new_perms);
		}
		return perms;
    }

	unordered_map<int, int> countValues(const vector<int>& nums) {
		unordered_map<int, int> c;
		for (int num : nums)
			c[num]++;
		return c;
	}

	/// Solution 2. Group items by the same value and generate consequent sets of permutations by inserting
	/// copies of the next value at unique combination of positions
    vector<vector<int>> permuteUnique2(vector<int>& nums) {
		vector<vector<int>> perm_list { {} };
		int permutation_size = 0;
		for (const auto& [value, count] : countValues(nums)) {
			permutation_size += count;
			/// Generate combinations of positions to insert elements from previous permutations
			/// Insert new value at remaining positions
			auto combinations = CombinationGenerator::generate(permutation_size, permutation_size - count);
			vector<vector<int>> new_perm_list;
			for (const auto &perm : perm_list) {
				for (const auto &comb : combinations) {
					/// New permutation of current size, fill with current value
					vector<int> new_perm(permutation_size, value);
					/// Fill positions of the combination with values of a permutation from previous permutation list
					/// in their order
					for (auto pit = perm.begin(), cit = comb.begin(); pit != perm.end(); ++pit, ++cit) {
						new_perm[*cit] = *pit;
					}
					/// A permutation for new permutation list is ready
					new_perm_list.push_back(new_perm);
				}
			}
			perm_list = move(new_perm_list);
		}		
		return perm_list;
	}
};

void sample_gen_combinations() {
	cout << CombinationGenerator().generate(5, 3) << endl;
	cout << CombinationGenerator::generate(4, 1) << endl;
	cout << CombinationGenerator::generate(4, 0) << endl;
	cout << CombinationGenerator::generate(4, 4) << endl;
	cout << CombinationGenerator::generate(1, 1) << endl;
	cout << CombinationGenerator::generate(1, 0) << endl;
	cout << CombinationGenerator::generate(0, 0) << endl;
	cout << CombinationGenerator::generate(0, 1) << endl;
}

void sample_iterators_find_insert_erase() {
	vector<int> v = { 2, 3, 5, 7, 11 };
	auto it = find(v.begin(), v.end(), 7);
	while (it != v.begin() - 1) {
		it = v.insert(it, 80);
		cout << v << endl;
		it = v.erase(it);
		it--;
	}
	v.insert(v.end(), 99);
	cout << v << endl;
	// auto new_it = v.insert(it, 100);
	// cout << *it << endl;
	// cout << *new_it << endl;
	// cout << v << endl;
	// auto new_it2 = v.erase(new_it);
	// cout << v << endl;
	// cout << *new_it << endl;
	// cout << *new_it2 << endl;
	// while (it != v.rbegin() - 1) {
	// 	v.insert(it, 80);
	// 	cout << *it << " ";
	// 	it--;
	// }
	// cout << distance(find(v.rbegin(), v.rend(), 5), v.rend());
	// cout << distance(find(v.rbegin(), v.rend(), 7), v.rend());
	// cout << distance(find(v.rbegin(), v.rend(), 11), v.rend());

}

void sample_permuteUnique() {
	vector<int> v = { 1, 1, 2, 2, 3 };
	auto p = Solution().permuteUnique(v);
	cout << p.size() << " permutations:\n" << p << endl;
}

void sample_permuteUnique2() {
	vector<int> v = { 1, 1, 2, 2, 3 };
	auto p = Solution().permuteUnique2(v);
	cout << p.size() << " permutations:\n" << p << endl;
}

void sample_std_permutations() {
	std::vector<int> v { 4, 5, 1, 6, 2, 3 };
	cout << (std::next_permutation(v.begin(), v.end()) ? "is not last" : "is last") << "\n";
	cout << v << endl;
	std::prev_permutation(v.begin(), v.end());
	cout << v << endl;
	v = {7, 5, 4, 3};
	cout << (std::ranges::next_permutation(v).found ? "is not last" : "is last") << "\n";
	// std::ranges::next_permutation(v);
	cout << v << endl;
}

int main() {
	sample_std_permutations();
	// sample_permuteUnique();
	// sample_gen_combinations();
	// vector<int> v { 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// cout << Solution().countItems(v) << endl;
	// unordered_map<int, int> m {{1, 2}, {3, 4}, {5, 6}};
	// unordered_map<int, int> m;
	// cout << (m.begin() == m.end()) << endl;
	// cout << m << endl;
	// for (auto it = m.begin(); it != prev(m.end()); ++it)
	// 	cout << it->first << ": " << it->second << ", ";
	// cout << *(prev(v.end())) << endl;
	// Timer::start();
	// auto perms = Solution().permuteUnique(v);
	// cout << "duration: " << Timer::get_seconds() << " s\n";
	// cout << perms.size() << ":\n" << perms << "\n";
	return 0;
}
