#include <iostream>

using namespace std;

/**Definition for a binary tree node.*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*Beats 100% on time, 60% on memory*/
class Solution {
public:

    bool isSymmetricR(TreeNode* n, TreeNode* m) {
        if (n == nullptr)
            return m == nullptr;
        if (m == nullptr)
            return n == nullptr;
        return n->val == m->val && 
            isSymmetricR(n->left, m->right) && 
            isSymmetricR(n->right, m->left);
    }

    bool isSymmetric(TreeNode* root) {
        return isSymmetricR(root->left, root->right);
    }
};

int main() {

	return 0;
}
