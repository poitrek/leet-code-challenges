#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class WildcardCompare {
public:
    bool operator()(char c1, char c2) {
        return c1 == c2 || c2 == '?';
    }
};

/**
 * Idea: split the pattern by "*" symbols into "words". The words (sequences between stars) must 
 * appear in the string being matched in their order in the pattern, with additional character
 * sequences between them. For each next word from the pattern, find its first appearance in the
 * string. Despite there might be many occurrences of a word in the string, choosing the first
 * one guarantees correct result.
 * 
 * Submission runtime: 3ms (beats 95.14%)
 * Memory: 9.72MB (beats 95.58%)
 * 
 * Time complexity: O(|s|*|p|)
 */
class Solution {
public:

    bool isMatch(string s, string p) {
		WildcardCompare wildcard_compare;
		auto first_star_pos = std::find(p.begin(), p.end(), '*');
		/// if the pattern has no star and sizes are different
        if (first_star_pos == p.end() && s.size() != p.size())
			return false;
		auto p_it = p.begin();
		auto s_it = s.begin();
		/// for pattern characters before the first star 
		while (p_it != first_star_pos) {
			if (s_it == s.end() || !wildcard_compare(*s_it, *p_it))
				return false;
			++p_it, ++s_it;
		}
		if (p_it == p.end())
			return true;
		p_it++;
		while (true) {
	        auto new_p_it = std::find(p_it, p.end(), '*');
			if (new_p_it == p.end())
				break;
			if (new_p_it == p_it) {
				p_it++;
				continue;
			}
			/// from (p_it --- new_pit) - next word between stars in pattern to find in s
			auto found_pos = std::search(s_it, s.end(), p_it, new_p_it, wildcard_compare);
			if (found_pos == s.end())
				return false;
			/// set s_it to the first character after the found word
			s_it = found_pos + distance(p_it, new_p_it);
			/// set p_it to the first character after the star
			p_it = new_p_it + 1;
		}
		/// if p_it points at the end, the last pattern character was star and we can finish
		if (p_it == p.end())
			return true;
		/// if the remaining s is shorter than the remaining pattern, impossible to match
		auto remaining_p_dist = std::distance(p_it, p.end());
		if (std::distance(s_it, s.end()) < remaining_p_dist)
			return false;
		s_it = s.end() - remaining_p_dist;
		/// last N chars of s must match last N chars of pattern
		return std::equal(s_it, s.end(), p_it, wildcard_compare);	
    }
};

void assert_match(std::string p, std::vector<std::string> vs) {
	Solution sol;
	for (const auto& s : vs) {
		if (!sol.isMatch(s, p)) {
			std::cerr << "Match failed for p='" + p + "', s='" + s + "'\n";
			exit(1);
		}
	}
}

void assert_no_match(std::string p, std::vector<std::string> vs) {
	Solution sol;
	for (const auto& s : vs) {
		if (sol.isMatch(s, p)) {
			std::cerr << "Match incorrectly true for p='" + p + "', s='" + s + "'\n";
			exit(1);
		}
	}
}

void test_is_match() {
	Solution s;
	assert(s.isMatch("abcd", "ab*cd"));
	assert(s.isMatch("abXYYZZWcd", "ab*cd"));
	assert_no_match("ab*cd", {"a", "abed", "abd", "abc", "abec", "abcc", "bcd", "ebcd", "abcda", "abcdd", "abxxxcad"});
	assert_match("one*two*three***four", {"onetwothreefour", "one  xx two three dude four", "one two one three three two one three four"});
	assert_no_match("one*two*three***four", {" onetwothreefour", " one two three four", "onetwothreefour ", "on two three four", "ontwothreefour", 
			"one two thre e four", "onetwothreefou", "one three two four", "oen two three four"});
	assert_match("aaa*", {"aaa", "aaab", "aaaa", "aaaaaaaa", "aaaRandomWordSequence"});
	assert_no_match("aaa*", {"aa", "a", "aaz", "aaya", "baaa", "baaajdfslkfsaas"});
	assert_match("bb**", {"bb", "bbb", "bba", "bbbb", "bbxyzwtxyz"});
	assert_no_match("bb**", {"b", "ab", "ba", "abb", "abba", "bab", "babb"});
	assert_match("**xy****z*w****", {"xyzw", " xyzw ", " xy z w ", " one xy two z three w five"});
	assert_no_match("**xy****z*w****", {"x yzw", "x y z w", "a", "xy", "xyw", "xyz", "zw", "xywz", "AAAxyAAAzAAAz"});

	assert_match("*", {"a", "aa", "ab", "abc", "onedoesnotsimplywalkintomordor"});
	assert_match("fl?ck", {"flock", "fleck", "fluck", "flick"});
	assert_no_match("fl?ck", {"flck", "flickr", "frock", "f", "floock"});
	std::string p = "*t?r??l*g??bling*h?st?r?*";
	assert_match(p, {"the thrill of gambling has existed in the entire history of mankind", "thrillgamblinghistory"});
	assert_no_match(p, {"grill gambling history", "gambling thrill history"});

	assert_match("?", {"a", "b", "x"});
	assert_no_match("?", {"aa", "xy", "qwerty"});
	assert_match("?*?", {"ab", "xyz", "petrichor"});
	assert_no_match("?*?", {"a", "P"});
	std::cout << "test_is_match OK\n";
}

int main() {
	test_is_match();
	return 0;
}
