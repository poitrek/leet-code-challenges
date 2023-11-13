#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root)
            return vector<int>();
        vector<int> out;
        stack<TreeNode*> half_visited;
        half_visited.push(root);
        TreeNode *n = root;
        while (!half_visited.empty()) {
            while (n) {
                half_visited.push(n);
                out.push_back(n->val);
                n = n->left;
            }
            n = half_visited.top();
            half_visited.pop();
            n = n->right;
        }
        return out;
    }
};

int main(){

	return 0;
}
