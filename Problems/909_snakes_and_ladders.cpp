#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "common.hpp"


using namespace std;

constexpr int MAX_JUMP = 6;


template<typename T>
class MySet {
	unordered_set<T> uset;
public:
	bool has(T element) {
		return uset.find(element) != uset.end();
	}
	void add(T element) {
		uset.insert(element);
	}
};

class Solution {
	/**
	 * 1. convert the board to straight sequence
	 */
public:

	vector<int> boardToSequence(const vector<vector<int>>& board) {
		/// initialize size (to avoid memory reallocation while expanding)
		// vector<int> sequence(board.size() * board.size());
		vector<int> sequence;
		bool odd_row = true;
		for (auto row_it = board.rbegin(); row_it != board.rend(); ++row_it) {
			if (odd_row) {
				copy(row_it->begin(), row_it->end(), back_inserter(sequence));
			}
			else {
				copy(row_it->rbegin(), row_it->rend(), back_inserter(sequence));
			}
			odd_row = 1 - odd_row;
		}
		return sequence;
	}

	int snakesNLaddersSequence(const vector<int> &seq) {
		if (seq.size() == 1)
			return 0;
		int final_node = seq.size() - 1;
		vector<int> to_visit = {0};
		vector<int> to_visit_next;
		MySet<int> seen;
		seen.add(0);
		int n_moves = 0;
		while (!to_visit.empty()) {
			for (int node : to_visit) {
				int max_empty_node = -1;
				/// for each node among all jump-available near nodes
				for (int next_node = node + 1; next_node <= node + MAX_JUMP; next_node++) {
					/// if we reached the final node, return
					if (next_node == final_node)
						return n_moves + 1;
					/// if the node hasn't been visited yet
					if (!seen.has(next_node)) {
						seen.add(next_node);
						int seq_value = seq[next_node];
						/// the value is -1 (simple node)
						if (seq_value == -1)
							max_empty_node = next_node;
						/// if it transfers to another node
						else if (!seen.has(seq_value)) {
							if (seq_value == final_node)
								return n_moves + 1;
							// seen.add(seq_value);
							to_visit_next.push_back(seq_value);
						}
					}
				}
				/// add the furthest simple node to the queue
				if (max_empty_node != -1)
					to_visit_next.push_back(max_empty_node);
			}
			/// next queue of nodes to visit becomes current queue
			to_visit = std::move(to_visit_next);
			n_moves++;
		}
		return -1;
	}

    int snakesAndLadders(vector<vector<int>>& board) {
		auto sequence = boardToSequence(board);
		for_each(sequence.begin(), sequence.end(), [](int& x) { if (x != -1) x--; });
        return snakesNLaddersSequence(sequence);
    }
};

void test_boardToSequence() {
	vector<vector<int>> m1 = {
		{7, 8, 9},
		{6, 5, 4},
		{1, 2, 3}
	};
	vector<vector<int>> m2 = {
		{4, 3},
		{1, 2}
	};
	vector<vector<int>> m3 = {
		{16, 15, 14, 13},
		{9,  10, 11, 12},
		{8,  7,  6,  5},
		{1,  2,  3,  4}
	};
	assert(Solution().boardToSequence(m1) == vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
	assert(Solution().boardToSequence(m2) == vector<int>({1, 2, 3, 4}));
	assert(Solution().boardToSequence(m3) == vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
	assert(Solution().boardToSequence(vector<vector<int>>({{1}})) == vector<int>({1}));
	assert(Solution().boardToSequence(vector<vector<int>>()) == vector<int>());
	clog << "test_boardToSequence passed\n";
}

void test_snakesNLaddersSequence() {
	assert(Solution().snakesNLaddersSequence(vector<int>(1, -1)) == 0);
	assert(Solution().snakesNLaddersSequence(vector<int>(2, -1)) == 1);
	assert(Solution().snakesNLaddersSequence(vector<int>(3, -1)) == 1);
	assert(Solution().snakesNLaddersSequence(vector<int>(7, -1)) == 1);
	assert(Solution().snakesNLaddersSequence(vector<int>(8, -1)) == 2);
	assert(Solution().snakesNLaddersSequence(vector<int>(19, -1)) == 3);
	assert(Solution().snakesNLaddersSequence(vector<int>(20, -1)) == 4);
	assert(Solution().snakesNLaddersSequence(vector<int>(601, -1)) == 100);
	clog << "test_snakesNLaddersSequence passed\n";
}

void sample1() {
	vector<vector<int>> b1 = {
		{-1,-1,-1,46,47,-1,-1,-1},
		{51,-1,-1,63,-1,31,21,-1},
		{-1,-1,26,-1,-1,38,-1,-1},
		{-1,-1,11,-1,14,23,56,57},
		{11,-1,-1,-1,49,36,-1,48},
		{-1,-1,-1,33,56,-1,57,21},
		{-1,-1,-1,-1,-1,-1,2,-1},
		{-1,-1,-1,8,3,-1,6,56}
	};
	// cout << Solution().boardToSequence(b1) << endl;
	cout << Solution().snakesAndLadders(b1) << endl;
}

int main() {
	sample1();
	test_snakesNLaddersSequence();
	test_boardToSequence();
	vector<int> s (30, -1);
	s[3] = 20;
	s[5] = 18;
	s[22] = 16;
	s[27] = 1;
	cout << Solution().snakesNLaddersSequence(s) << endl;
	vector<vector<int>> board = {
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,35,-1,-1,13,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,15,-1,-1,-1,-1}
	};
	vector<vector<int>> b2 = {
		{-1, -1},
		{-1, 3}
	};
	vector<vector<int>> b3 = {
		{-1, -1, -1},
		{-1, -1, -1},
		{-1, -1, -1},
	};
	cout << Solution().snakesAndLadders(board) << endl;
	cout << Solution().snakesAndLadders(b3) << endl;
	return 0;
}
