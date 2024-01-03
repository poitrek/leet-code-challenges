#include <iostream>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ls = new ListNode();
        ListNode *head = ls;
        int correction = 0;
        while (l1 || l2 || correction) {
            ls->next = new ListNode();
            ls = ls->next;
            int s = 0;
            if (l1) {
                s += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                s += l2->val;
                l2 = l2->next;
            }
            s += correction;
            if (s >= 10) {
                correction = 1;
                s -= 10;
            }
            else {
                correction = 0;
            }
            ls->val = s;
        }
        ListNode *to_delete = head;
        head = head->next;
        delete to_delete;
        return head;
    }
};

int main() {

	return 0;
}
