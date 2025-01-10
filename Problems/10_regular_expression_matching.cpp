#include <cassert>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


constexpr char EPSILON = '-';
constexpr char NONE = '_';

struct NfaState {
	NfaState() : current(NONE), next(NONE), index(count++), epsilonClosure({index}) {}
	char current;
	char next;
	int index;
	std::unordered_set<int> epsilonClosure;
	static int count;
};

int NfaState::count = 0;


class Solution {
public:

	void set_union(std::unordered_set<int>& s1, std::unordered_set<int>& s2) {
		s1.insert(s2.begin(), s2.end());
	}

    bool isMatch(std::string s, std::string p) {
        if (p.find('*') == std::string::npos) {
			/// No stars nor dots - just compare
			if (p.find('.') == std::string::npos)
				return s == p;
			// No star operators, but dot metacharacters present
			if (s.size() != p.size())
				return false;
			for (int i = 0; i < s.size(); i++)
				if (p[i] != '.' && p[i] != s[i])
					return false;
			return true;
		}
		/// Now assuming p has * operators
		/// Construct NFA states, start with initial state
		NfaState::count = 0;
		std::vector<NfaState> states { NfaState() };
		bool last_is_star = false;
		for (int i = 0; i < p.size(); i++) {
			if (i+1 < p.size() && p[i+1] == '*') {
				if (last_is_star) {
					states.back().next = EPSILON;
					states.push_back(NfaState());
				}
				states.back().current = p[i];
				last_is_star = true;
				i++;
			}
			else {
				states.back().next = p[i];
				states.push_back(NfaState());
				last_is_star = false;
			}
		}
		// Create epsilon-closures
		for (auto it = states.rbegin(); it != states.rend(); ++it) {
			if (it->next == EPSILON) {
				set_union(it->epsilonClosure, (it - 1)->epsilonClosure);
			}
		}
		std::unordered_set<int> alternative_states = states.front().epsilonClosure;
		for (char c : s) {
			std::unordered_set<int> new_alt_states;
			for (int state_idx : alternative_states) {
				NfaState& state = states[state_idx];
				if (state.current == c || state.current == '.')
					set_union(new_alt_states, states[state_idx].epsilonClosure);
				if (state.next == c || state.next == '.')
					set_union(new_alt_states, states[state_idx + 1].epsilonClosure);
			}
			if (new_alt_states.empty())
				return false;
			alternative_states = new_alt_states;
		}
		return (alternative_states.find(NfaState::count - 1) != alternative_states.end());
	}
};


class Solution2 {
public:
    bool isMatch(std::string s, std::string p) {
        if (p.find('*') == std::string::npos) {
			if (p.find('.') == std::string::npos)
				return s == p;
			// No star operators, but dot metacharacters present
			if (s.size() != p.size())
				return false;
			for (int i = 0; i < s.size(); i++)
				if (p[i] != '.' && p[i] != s[i])
					return false;
			return true;
		}
		// Guard character
		p.push_back('_');
		return false;
		/// Construct NFA states, start with initial state
		// std::vector<NfaState> states { NfaState() };
		// for (int i = 0; i < p.size() - 1; i++) {
		// 	if (p[i+1] == '*') {
		// 		states.back().current = p[i];
		// 		i++;
		// 	}
		// 	else {
		// 		states.back().next = p[i];
		// 	}
		// }
    }
};


void assert_match(std::string pattern, const std::vector<std::string>& strs) {
	Solution sol;
	for (const auto& s : strs)
		assert(sol.isMatch(s, pattern));
}

void assert_no_match(std::string pattern, const std::vector<std::string>& strs) {
	Solution sol;
	for (const auto& s : strs)
		assert(!sol.isMatch(s, pattern));
}


void test_is_match() {
	Solution s;
	assert(true);
	assert(s.isMatch("thrillOfGambling", "thrillOfGambling"));
	assert(s.isMatch("a", "a"));
	assert(s.isMatch("thrillOfGambling", "th..llO.Gambl..."));
	assert(s.isMatch("thxxllOfGamblxxx", "th..llO.Gambl..."));
	assert(!s.isMatch("a", "b"));
	assert(!s.isMatch("aaaa", "aa."));
	assert(!s.isMatch("thrillOfgambling", "th..llO.Gambl..."));

	assert(s.isMatch("a", "a*"));
	assert(s.isMatch("aaaaaaaa", "a*"));
	assert(!s.isMatch("aaaab", "a*"));

	assert_match("abc*de", {"abde", "abcde", "abcccccccde"});
	assert_no_match("abc*de", {"abbde", "abdde", "abxde", "abccccxccde", "bde", "abe", "abd"});
	
	assert_match("abc*d*e*fg*", {"abf", "abcdef", "abcdefg", "abccceeefggggg", "abccccddeeeefggg"});
	assert_no_match("abc*d*e*fg*", {"x", "babf", "abff", "abbf", "abdcf", "abx", "abg", "abgf", "abcccddddeeefegg"});

	std::string p;
	p = "abcc*cdd*e*ef";
	assert_match(p, {"abccdef", "abcccccccdef", "abccccddddddddddeeeeeeef"});
	assert_no_match(p, {"abcdef", "abef", "abccef", "abccdf", "abccxdef", "abcccef"});

	p = "a*..";
	assert_match(p, {"Xy", "aXZ", "aaaaaaaaaaXd", "aa", "aaa", "aaaaaaaaa", "aba"});
	assert_no_match(p, {"xbc", "axyz", "axya", "baba"});

	p = ".*";
	assert_match(p, {"a", "B", "Xyz", "ZzpifjdwqlfjeNLKVjklfs"});
	
	p = "ab*.*c*";
	assert_match(p, {"a", "ab", "abc", "abbBBBvJJffff", "aXYQZJOFFDkfjdsles"});
	assert_no_match(p, {"x", "xAyuefw"});

	p = "...*..";
	assert_match(p, {"abcd", "mmmm", "PqafWfsjioefJVEHjgfd"});
	assert_no_match(p, {"abc", "aaa", "x", "yy"});
	std::cout << "test_is_match OK\n";
}


int main() {
	test_is_match();
	return 0;
}
