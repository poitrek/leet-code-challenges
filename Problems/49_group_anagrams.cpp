#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
	/// Version 1. Use sorted string as the anagram "signature"
	/// Beats 75.53% on time
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		std::unordered_map<string, vector<string>> groups;
		for (const auto &str : strs) {
			std::string sorted(str);
			std::sort(sorted.begin(), sorted.end());
			groups[sorted].push_back(str);
		}
		std::vector<std::vector<std::string>> result;
		for (const auto& [key, value] : groups) {
			result.push_back(value);
		}
		return result;
    }

	/// Version 2. Use map [character]->[count] as the anagram signature
	/// Beats 11.11% on time
    vector<vector<string>> groupAnagrams_2(vector<string>& strs) {
		map<map<char, int>, vector<string>> groups;
		for (const auto &str : strs) {
			map<char, int> count;
			for (char c : str)
				count[c]++;
			groups[count].push_back(str);
		}
		std::vector<std::vector<std::string>> result;
		for (const auto& [key, value] : groups) {
			result.push_back(value);
		}
		return result;
    }

    // vector<vector<string>> groupAnagrams2(vector<string>& strs) {
	// 	// map<unordered_multiset<char>, vector<string>> m;
	// 	std::map<std::unordered_multiset<char>, std::vector<std::string>> groups;
	// 	for (const auto &str : strs) {
	// 		std::unordered_multiset<char> str_charset(str.begin(), str.end());
	// 		if (groups.find(str_charset) == groups.end()) {
	// 			groups[str_charset] = { str };
	// 		}
	// 		else {
	// 			groups[str_charset].push_back(str);
	// 		}
	// 	}
	// 	std::vector<std::vector<std::string>> result;
	// 	for (const auto& [key, value] : groups) {
	// 		result.push_back(value);
	// 	}
	// 	return result;
    // }
};

int main() {

	return 0;
}
