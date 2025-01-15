#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class IsTrueChar {
public:
	bool operator()(char a) {
		return a == 't';
	}
};

class Solution {
public:
    bool parseBoolExpr(string expression) {
		IsTrueChar isTrueChar;
        std::stack<char> s;
		for (char c : expression) {
			if (c != ',' && c != ')') {
				s.push(c);
				continue;
			}
			if (c == ')') {
				std::vector<char> arguments;
				while (s.top() != '(') {
					arguments.push_back(s.top());
					s.pop();
				}
				s.pop();
				bool result;
				switch(s.top()) {
					case '&':
						result = std::all_of(arguments.begin(), arguments.end(), isTrueChar);
						break;
					case '|':
						result = std::any_of(arguments.begin(), arguments.end(), isTrueChar);
						break;
					case '!':
						result = !isTrueChar(arguments[0]);
						break;
					default:
						throw "Error parsing, unexpected token '" + std::string({ s.top() }) + "' !!!";
						break;
				}
				s.pop();
				s.push(result ? 't' : 'f');
			}
		}
		if (s.size() != 1)
			throw "Error parsing, stack size is not 1!!";
		if (s.top() == 't')
			return true;
		else if (s.top() == 'f')
			return false;
		else
			throw "Error parsing!!";
    }
};

int main() {
	cout << "happy world!\n";
	Solution sol;
	// cout << sol.parseBoolExpr("|(t,f,t)") << endl;
	// cout << sol.parseBoolExpr("&(t,f,t)") << endl;
	// cout << sol.parseBoolExpr("&(t,f,!(t))") << endl;
	cout << sol.parseBoolExpr("!(&(f,t))") << endl;
	return 0;
}
