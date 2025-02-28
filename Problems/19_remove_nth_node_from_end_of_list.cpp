#include <iostream>

#include "timer.hpp"

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/// @brief Simplest solution. Pass through the list once and count the elements (X),
/// then pass the second time X-n times and perform node removal
/// 2M+2M-2n-2=4M-2n
class Solution {
public:
	Solution() {
		cout << "Solution\n";
	}
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int n_elements = 0;
		ListNode* e = head;
		/// 2M
		while(e) {
			n_elements++;
			e = e->next;
		}
		e = head;
		int k = n_elements - n;
		if (k == 0) {
			ListNode* new_head = head->next;
			delete head;
			return new_head;
		}
		/// 2(M-n-1)
		for (int i = 0; i < k - 1; i++)
			e = e->next;
		ListNode* to_delete = e->next;
		e->next = to_delete->next;
		delete to_delete;
		return head;
	}
};

/// @brief Optimized solution to avoid passing through the entire list "twice"
/// 3M-3n+2n = 3M-n
class Solution2 {
public:
	Solution2() {
		cout << "Solution2\n";
	}
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int n_elements = 0;
		ListNode* e = head;
		/// 2n
		for (int i = 0; i < n; i++) {
			e = e->next;
		}
		if (!e) {
			ListNode* new_head = head->next;
			delete head;
			return new_head;
		}
		ListNode* e_delayed = head;
		/// 3(M-n)
		while (e->next) {
			e = e->next;
			e_delayed = e_delayed->next;			
		}
		ListNode* to_delete = e_delayed->next;
		e_delayed->next = to_delete->next;
		delete to_delete;
		return head;
	}
};

/// Generates a list containing n_elements elements
ListNode* make_list(int n_elements) {
	if (!n_elements)
		return nullptr;
	ListNode* h = new ListNode(0);
	ListNode* n = h;
	for (int i = 1; i < n_elements; i++) {
		n->next = new ListNode(i);
		n = n->next;
	}
	return h;
}

void print_list(ListNode* head) {
	cout << '[';
	while (head) {
		cout << head->val << ' ';
		head = head->next;
	}
	cout << "]\n";
}

template<typename SolutionType>
void test(SolutionType sol) {
	auto l1 = make_list(100000000);
	Timer::start();
	sol.removeNthFromEnd(l1, 113);
	cout << "small n: " << Timer::get_seconds() << " s\n";

	Timer::start();
	sol.removeNthFromEnd(l1, 5000);
	cout << "middle n: " << Timer::get_seconds() << " s\n";

	Timer::start();
	sol.removeNthFromEnd(l1, 9855);
	cout << "large n: " << Timer::get_seconds() << " s\n";
}

int main() {
	test(Solution2());
	return 0;
}
