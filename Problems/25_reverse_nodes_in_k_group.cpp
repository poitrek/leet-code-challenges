#include <cassert>
#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

std::ostream& operator<<(std::ostream& o, ListNode* n) {
    o << '[';
    while (n) {
        o << n->val << ' ';
        n = n->next;
    }
    o << ']';
    return o;
}

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1 || !head || !(head->next))
            return head;
        int n_groups = listSize(head) / k;
        /// Guard node
        ListNode* guard = new ListNode();
        ListNode* prev_group_tail = guard;
        ListNode* n = head;
        for (int i = 0; i < n_groups; i++) {
            ListNode* new_group_tail = n;
            ListNode* g_prev = n;
            n = n->next;
            ListNode* g_next = n;
            for (int j = 0; j < k-1; j++) {
                g_next = n->next;
                n->next = g_prev;
                g_prev = n;
                n = g_next;
            }
            prev_group_tail->next = g_prev;
            prev_group_tail = new_group_tail;
        }
        prev_group_tail->next = n;
        n = guard->next;
        delete guard;
        return n;
    }

    int listSize(ListNode* head) {
        int size = 0;
        while (head) {
            size++;
            head = head->next;
        }
        return size;
    }
};

ListNode* gen_k(int k) {
    if (k == 0)
        return nullptr;
    auto n = new ListNode(1);
    auto head = n;
    for (int i = 1; i < k; i++) {
        n->next = new ListNode(i+1);
        n = n->next;
    }
    return head;
}

void test_print_op() {
    ListNode *n = new ListNode(10, new ListNode(20, new ListNode(30, new ListNode(40))));
    std::cout << n << "\n";
    std::cout << gen_k(10) << "\n";
}

void test_list_size() {
    ListNode *n = new ListNode(10, new ListNode(20, new ListNode(30, new ListNode(40))));
    assert(Solution().listSize(n) == 4);
    assert(Solution().listSize(nullptr) == 0);
    assert(Solution().listSize(new ListNode()) == 1);
    std::clog << "test_list_size OK\n";
}

int main() {
    ListNode *n = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    std::cout << Solution().reverseKGroup(n, 2) << "\n";
    std::cout << Solution().reverseKGroup(gen_k(15), 4) << "\n";
    std::cout << Solution().reverseKGroup(gen_k(24), 8) << "\n";
    test_list_size();
    test_print_op();
    return 0;
}