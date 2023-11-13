#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {

public:
    bool canConstruct(string ransomNote, string magazine) {
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unordered_map<char, int> rn_char_cnt;
		for (char a : alphabet)
			rn_char_cnt[a] = 0;
		unordered_map<char, int> mag_char_cnt (rn_char_cnt);
		for (char c : ransomNote)
			rn_char_cnt[c]++;
		for (char c : magazine)
			mag_char_cnt[c]++;
		for (char a : alphabet)
			if (rn_char_cnt[a] > mag_char_cnt[a])
				return false;
		return true;
    }

	// Optimized space, one map
	// Note from leetcode comments:
	// For alphabet consisting of only 26 characters, using
	// array instead of unordered map can be faster
	bool canConstruct2(string ransomNote, string magazine) {
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unordered_map<char, int> char_cnt;
		for (char a : alphabet)
			char_cnt[a] = 0;
		for (char c : ransomNote)
			char_cnt[c]++;
		for (char c : magazine)
			char_cnt[c]--;
		for (char a : alphabet)
			if (char_cnt[a] < 0)
				return false;
		return true;
    }
};

int main(){
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string ransomNote, magazine;
	cin >> ransomNote >> magazine;
	cout << Solution().canConstruct(ransomNote, magazine) << endl;
	return 0;
}
