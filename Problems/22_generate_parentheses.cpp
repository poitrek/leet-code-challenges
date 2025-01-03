#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

#include "vector_print.h"


using namespace std;


/**
 * Solution: well-formed parentheses can be generated using formal grammar
 * concept/terminology. The grammar can be defined using an additional 
 * "non-terminal" symbol V, and rewriting rules:
 * V -> VV
 * V -> (V)
 * V -> ()
 * To generate any of the desired strings, we start with a single symbol V
 * and apply any of the defined rules to current string, until the string
 * consists only of terminal symbols '(' and ')', for example:
 * V -> VV -> (V)V -> (())V -> (())(V) -> (())(VV) -> (())(()V) -> (())(()())
 * It can be proven that any string of correctly formed parentheses can be 
 * generated using these rules.
 * 
 * To generate all n-pair parentheses strings, we notice the following:
 * any n-pair string is of form: 
 * - (X), where X is an (n-1)-pair string;
 * - XY, where X is a i-pair string and Y is a (n-i)-pair string.
 * 
 * This is a recursive formula which can be implemented with dynamic programming
 * by remembering all i-pair strings in a container (parset[i]).
 */

class Solution {
public:
    vector<string> generateParenthesis(int n) {
		vector<unordered_set<string>> parset(n);
		parset[0] = { "()" };
		for (int i = 1; i < n; i++) {
			for (auto &par : parset[i-1]) {
				parset[i].insert("(" + par + ")");
			}
			for (int j = 0; j < i; j++)
				/// Num. of pairs in par1 and par2 should add up to i+1
				for (auto &par1 : parset[j])
					for (auto &par2 : parset[i-1-j])
						parset[i].insert(par1 + par2);
		}
		return vector<string>(parset[n-1].begin(), parset[n-1].end());
    }
};

int main() {
	std::cout << Solution().generateParenthesis(3) << "\n";
	std::cout << Solution().generateParenthesis(5) << "\n";
	return 0;
}
