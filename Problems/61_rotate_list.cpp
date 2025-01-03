#include <iostream>
#include <initializer_list>
#include <vector>
#include <cassert>

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


ListNode* kth_element(ListNode* head, int k) {
	if (!head)
		return head;
	ListNode *n = head;
	unsigned int i = 0;
	while (i < k) {
		i++;
		n = n->next;
		/// exceeded the list - k > list_size
		if (!n) {
			/// i - list size
			k %= i;
			/// start again
			i = 0;
			n = head;
		}
	}
	return n;
}

class Solution {
public:

	unsigned int getSize(ListNode* head) {
		unsigned int size = 0;
		while (head) {
			head = head->next;
			size++;
		}
		return size;
	}

	ListNode* rotateRight(ListNode* head, int k) {
		if (!head || !head->next || k == 0)
			return head;
		auto size = getSize(head);
		k %= size;
        if (k == 0)
            return head;
		ListNode* n = head;
		/// point n at (size-k-1)-th element
		for (int i = 0; i < size - k - 1; i++)
			n = n->next;
		ListNode* n_tmp = n;
		n = n->next;
		/// make (size-k-1)-th element tail
		n_tmp->next = nullptr;
		n_tmp = n;
		/// find old tail and connect it to the head
		while (n->next)
			n = n->next;
		n->next = head;
		return n_tmp;
	}

    /// First attempt - mistakenly implemented left rotate instead of right
    ListNode* rotateLeft(ListNode* head, int k) {
        if (!head || k == 0)
            return head;
        ListNode *n = head;
        unsigned int i = 0;
        while (i < k - 1) {
            i++;
            /// exceeded the list - k > list_size
            if (!n) {
                /// i - list size
                k %= i;
                /// start again
                i = 0;
                n = head;
            }
            n = n->next;
        }
		/// n points at (k-1)-th element
		ListNode* n_tmp = n;
		n = n->next;
		/// make (k-1)-th element the tail
		n_tmp->next = nullptr;
		/// point n_tmp to the k-th element
		n_tmp = n;
		/// connect old tail to the old head
		while (n->next)
			n = n->next;
		n->next = head;
		/// return k-th element as the head
        return n_tmp;
    }
};

void test_get_size() {
	auto mylist1 = create_list(vector<int>({2, 3, 5, 7, 11}));
	ListNode* mylist2 = new ListNode(13);
	Solution s;
	assert(s.getSize(mylist1) == 5);
	assert(s.getSize(nullptr) == 0);
	assert(s.getSize(mylist2) == 1);
	mylist2->next = new ListNode(29);
	assert(s.getSize(mylist2) == 2);
}

void test_kth_element() {
	auto mylist1 = create_list(vector<int>({2, 3, 5, 7, 11}));
	assert(kth_element(mylist1, 0)->val == 2);
	assert(kth_element(mylist1, 3)->val == 7);
	assert(kth_element(mylist1, 4)->val == 11);
	assert(kth_element(mylist1, 5)->val == 2);
	assert(kth_element(mylist1, 7)->val == 5);
	assert(kth_element(mylist1, 101)->val == 3);
}

int main() {
	test_kth_element();
	test_get_size();
	auto mylist1 = create_list(vector<int>({2, 3, 5, 7, 11}));
	cout << mylist1 << endl;
	// cout << kth_element(mylist1, 3)->val << endl;
	mylist1 = Solution().rotateRight(mylist1, 2);
	cout << mylist1 << endl;
	return 0;
}
