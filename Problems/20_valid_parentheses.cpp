#include <iostream>
#include <stack>
#include <map>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        map<char, char> par {{']', '[' }, {'}', '{'}, {')', '('}};
        stack<char> stck;
        for (char c : s) {
			// c is an opening bracket 
            if (par.find(c) == par.end())
                stck.push(c);
			// c is a closing bracket
            else {
				// c must have its corresponding opening bracket on
				// the top of the stack
                if (!stck.empty() && par[c] == stck.top())
                    stck.pop();
                else
                    return false;
            }
        }
        return stck.empty();
    }
};

int main(){
	string s;
	cin >> s;
	cout << Solution().isValid(s) << endl;
	return 0;
}
