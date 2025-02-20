#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "timer.hpp"

using namespace std;


/**
 * @brief BEATS 100% on time!!
 * Identical to Solution3, except all member variables, including the regex object, are static.
 * This causes them to initialize on program startup. 
 * (Since it reduced the runtime to 0 ms, that means the code submitted to leetcode is compiled and
 * run only ONCE, but the Solution object is probably instantiated once for each test)
 */
class Solution4 {
public:
    static string signPattern;
    static string exponentPattern;
    static string numberPattern;

	static regex reg;

    bool isNumber(string s) {
		return regex_match(s, reg);
    }
};

string Solution4::signPattern{"(\\-|\\+)?"};
string Solution4::exponentPattern{"(e|E)" + signPattern + "\\d+"};
string Solution4::numberPattern{signPattern + "(\\d+|\\d+\\.\\d*|\\.\\d+)" + "(" + exponentPattern + ")?"};
regex Solution4::reg(numberPattern);


/**
 * @brief Slightly rewritten regex
 * Checked in the tests below, more efficient by ~10%.
 */
class Solution3 {
public:
    string signPattern{"(\\-|\\+)?"};
    // string integerPattern{"\\d+"};
    // string decimalPattern{"(\\d+\\.\\d*|\\.\\d+)"};
    string exponentPattern{"(e|E)" + signPattern + "\\d+"};
    string numberPattern{signPattern + "(\\d+|\\d+\\.\\d*|\\.\\d+)" + "(" + exponentPattern + ")?"};

	regex reg = regex(numberPattern);

    bool isNumber(string s) {
		return regex_match(s, reg);
    }
};


/**
 * A solution using regular expressions. Beats only 5% on time on LC because the regex has to be compiled each 
 * time, which is very time consuming. Typically however, you compile a regex once and reuse it on each string
 * match.
 */
class Solution {
public:
    string signPattern{"(\\-|\\+)"};
    string integerPattern{signPattern + "?\\d+"};
    string decimalPattern{signPattern + "?(\\d+\\.\\d*|\\.\\d+)"};
    string exponentPattern{"(e|E)" + integerPattern};
    string numberPattern{"(" + integerPattern + "|" + decimalPattern + ")" + "(" + exponentPattern + ")?"};

	regex reg = regex(numberPattern);

    bool isNumber(string s) {
		return regex_match(s, reg);
    }
};


/**
 * @brief Someone else's solution provided by LeetCode, for time comparison
 */
class SolutionAlternative {
public:
    bool isNumber(string s) {
        int n = s.length();
        bool hasNum = false, hasDot = false, hasExp = false;
        
        for (int i = 0; i < n; i++) {
            char c = s[i];

            // If the character is a digit, mark that we have seen a number
            if (isdigit(c)) {
                hasNum = true;
            } 
            // If the character is '.', handle decimal rules
            else if (c == '.') {
                if (hasDot || hasExp) return false;  // Can't have multiple dots or a dot after 'e'
                hasDot = true;
            } 
            // If the character is 'e' or 'E', handle exponent rules
            else if (c == 'e' || c == 'E') {
                if (hasExp || !hasNum) return false; // Can't have multiple 'e' or 'e' before a number
                hasExp = true;
                hasNum = false; // Reset hasNum to ensure there's a number after 'e'
            } 
            // If the character is '+' or '-', it must be the first character or right after 'e'
            else if (c == '+' || c == '-') {
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') return false; // Can only be at start or after 'e'
            } 
            // If it's any other character, return false
            else {
                return false;
            }
        }
        
        return hasNum; // Ensure we have seen at least one number
    }
};

template<typename SolutionType>
void test_match_time(SolutionType sol) {
	vector<string> testStrings = {
		"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789",
		"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", "7915508324383.35352"
	};
	Timer::start();
	for (int i = 0; i < 10000; i++) {
		for (auto s : testStrings) {
			sol.isNumber(s);
		}
	}
	cout << Timer::get_seconds() << " s" << endl;
}

int main() {
	Solution mySol;
	SolutionAlternative solAlt;
	Solution3 sol3;
	// test_match_time(solAlt);
	test_match_time(mySol);
	test_match_time(sol3);
	return 0;
}
