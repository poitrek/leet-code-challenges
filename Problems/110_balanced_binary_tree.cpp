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

// accepted
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return heightIsBalanced(root).first;
    }
	// checks if the tree is balanced and calculates its height
	// returns pair (<is_balanced>, <height>)
    pair<bool, int> heightIsBalanced(TreeNode* node) {
        if (!node)
            return {true, -1};
        auto hib_left = heightIsBalanced(node->left);
        auto hib_right = heightIsBalanced(node->right);
        int skew = hib_left.second - hib_right.second;
        bool is_balanced = hib_left.first && hib_right.first && abs(skew) <= 1;
        int height = max(hib_left.second, hib_right.second) + 1;
        return {is_balanced, height};
    }
};

int main() {

	return 0;
}
