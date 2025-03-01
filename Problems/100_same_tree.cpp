#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
/**
 * @brief Simple recursive solution. Beats 100% time.
 * Can be done iteratively to reduce the space.
 */
 class Solution {
	public:
		bool isSameTree(TreeNode* p, TreeNode* q) {
			if (p == nullptr)
				return q == nullptr;
			if (q == nullptr)
				return false;
			return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
	};

int main() {

	return 0;
}
