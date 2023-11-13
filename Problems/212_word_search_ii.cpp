#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
basic insights:
- if A is in the board and B is a substring of A or A[::-1], B is in the board
- converesely - if B is not in the board and B is a substring of A or A[::-1], A is not in the board
- words create a partial order with the relation X < Y, where X is a substring of Y or Y[::-1]

computer
pace
aput
put
retup
cromp
drill
omp
ill
ace

ace < pace, put < retup < computer, put < aput, ill < drill, omp < cromp
ace !< put, retup !< aput

Depending on the input set of words, the problem might lie in running the word search
as few times as possible, i.e. detecting substring pairs in the set (?)
We might first find the partial order between the words, then run word search using the
first two insights, e.g. if we find word W in the grid, all of its descendants (substrings)
are in it too.

*/

struct WordNode {
	string word;
	vector<WordNode*> children;
	vector<WordNode*> parents;
};

enum SubstringResult {
	FIRST_SUB,
	SECOND_SUB,
	REVERSED,
	EQUAL,
	NONE
};

bool is_substring(string sub, string super) {
	if (sub.size() >= super.size())
		return false;
	if (super.find(sub) != string::npos)
		return true;
	reverse(sub.begin(), sub.end());
	return super.find(sub) != string::npos;
}

bool is_reversed(string first, string second) {
	if (first.size() != second.size())
		return false;
	reverse(first.begin(), first.end());
	return first == second;
}

SubstringResult compare(string first, string second) {
	if (is_substring(first, second))
		return SubstringResult::FIRST_SUB;
	else if (is_substring(second, first))
		return SubstringResult::SECOND_SUB;
	else if (is_reversed(first, second))
		return SubstringResult::REVERSED;
	else if (first == second)
		return SubstringResult::EQUAL;
	else
		return SubstringResult::NONE;
}

class WordSet {
	vector<WordNode> nodes;
public:
	WordSet(const vector<string> &words) {
		for (auto &word : words)
			add(word);
	}

	void add(string word) {
		WordNode new_node = { word };
		nodes.push_back(new_node);
		// for (auto node : nodes) {
		// 	if (is_substring(word, node.word)) {
		// 		if (word.size())
		// 	}
		// 		connect(new_node, node);
		// 	else if (is_substring(node.word, word))
		// 		connect(node, new_node);
		// }
	}

	static void connect(WordNode &child, WordNode &parent) {
		child.parents.push_back(&parent);
		parent.children.push_back(&child);
	}

	// static unordered_set<WordNode*> ancestors(WordNode &node) {
	// 	deque<WordNode*> queue;
	// 	queue.push_back()
	// }
};

class Solution {
public:
    // vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
    // }
};

void test_is_substring() {
	assert(is_substring("put", "computer"));
	assert(is_substring("tup", "computer"));
	assert(is_substring("re", "computer"));
	assert(is_substring("m", "computer"));
	assert(!is_substring("x", "computer"));
	assert(!is_substring("fish", "comp"));
	assert(!is_substring("computer", "comp"));
	cout << "test_is_substring OK" << endl;
}

void test_is_reversed() {
	assert(is_reversed("abcd", "dcba"));
	assert(!is_reversed("abcd", "abc"));
	assert(!is_reversed("abcd", "abcd"));
	assert(!is_reversed("xyza", "abcd"));
	cout << "test_is_reversed OK" << endl;
}

void test_compare() {
	assert(compare("put", "computer") == FIRST_SUB);
	assert(compare("computer", "put") == SECOND_SUB);
	assert(compare("tup", "computer") == FIRST_SUB);
	assert(compare("put", "tup") == REVERSED);
	assert(compare("put", "put") == EQUAL);
	assert(compare("reput", "aput") == NONE);
	cout << "test_compare OK" << endl;
}

int main() {
	test_is_substring();
	test_is_reversed();
	test_compare();
	// int n;
	// cin >> n;
	// vector<string> words(n);
	// for (int i = 0; i < n; i++)
	// 	cin >> words[i];
	
	return 0;
}
