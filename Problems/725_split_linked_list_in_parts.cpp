#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

/// Definition for singly-linked list.

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename ContainerType>
ListNode* create_list(const ContainerType &container) {
	ListNode *head = new ListNode;
	ListNode *n = head;
	for (int i : container) {
		n->next = new ListNode(i);
		n = n->next;
	}
	n = head;
	head = head->next;
	delete n;
	return head;
}

std::ostream& operator<<(std::ostream& o, ListNode* ln) {
	o << "list {";
	while (ln) {
		o << ln->val << " ";
		ln = ln->next;
	}
	o << "}";
	return o;
}

vector<int> list_values(ListNode* head) {
	vector<int> values;
	while (head) {
		values.push_back(head->val);
		head = head->next;
	}
	return values;
}


class Solution {
public:

    ListNode* cutListPart(ListNode* n, unsigned int cutSize) {
        if (cutSize == 0)
            return n;
        while (--cutSize) {
            n = n->next;
        }
        ListNode *n_nxt = n->next;
        n->next = nullptr;
        return n_nxt;
    }

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        if (k == 1)
            return { head };
        ListNode *n = head;
        unsigned int size = 1;
        while (n->next) {
            size++;
            n = n->next;
        }

        unsigned int partSize = size / k;
        unsigned int r = size % k;
        /// for (int i = 0; i < r; i++)
        ///     parts.push(partSize + 1);
        /// for (int i = r; i < k; i++)
        ///     parts.push(partSize);
        vector<ListNode*> parts;
		n = head;
		for (int i = 0; i < r; i++) {
			parts.push_back(n);
			n = cutListPart(n, partSize + 1);
		}
		for (int i = r; i < k; i++) {
			parts.push_back(n);
			n = cutListPart(n, partSize);
		}
		return parts;
    }
};

void test_list_values() {
	vector<int> v1 {1, 2, 3, 4};
	ListNode *list1 = create_list(v1);
	assert(list_values(list1) == v1);
	assert(list_values(nullptr) == vector<int>());
	clog << "finish test_list_values\n";
}

void test_split_list_to_parts() {
	ListNode *list1 = create_list(vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
	vector<ListNode*> list1_parts = Solution().splitListToParts(list1, 4);
	assert(list_values(list1_parts[0]) == vector<int>({1, 2, 3}));
	assert(list_values(list1_parts[1]) == vector<int>({4, 5, 6}));
	assert(list_values(list1_parts[2]) == vector<int>({7, 8}));
	assert(list_values(list1_parts[3]) == vector<int>({9, 10}));
	ListNode *list2 = create_list(vector<int>({1, 2, 3}));
	vector<ListNode*> list2_parts = Solution().splitListToParts(list2, 5);
	assert(list_values(list2_parts[0]) == vector<int>({1}));
	assert(list_values(list2_parts[1]) == vector<int>({2}));
	assert(list_values(list2_parts[2]) == vector<int>({3}));
	assert(list_values(list2_parts[3]) == vector<int>());
	assert(list_values(list2_parts[4]) == vector<int>());
	
	clog << "finish test_split_list_to_parts\n";
}

int main() {
	test_list_values();
	test_split_list_to_parts();
	return 0;
}
