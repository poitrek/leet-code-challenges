#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

using namespace std;

/**
Definition for a binary tree node.
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
 * @brief Analogous to preorder + inorder. We notice that postorder of a tree = preorder of the inverted tree.
 * We use this fact to build the tree similarly to Problem 105. 
 * Time complexity: O(n). 
 * Auxiliary space: O(n), O(log n) if the tree is balanced.
 */
class Solution {
	enum class ChildDirection {
		Left, Right
	};
	static constexpr int GUARD_VALUE = -3001;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		auto postorder_it = postorder.rbegin();
		auto inorder_it = inorder.rbegin();
		stack<TreeNode*> nstack;
		/// root
		TreeNode* n = new TreeNode(*postorder_it);
		TreeNode* root = n;
		ChildDirection nextChildDir = ChildDirection::Right;
		nstack.push(new TreeNode(GUARD_VALUE)); /// guard
		nstack.push(n);
		while (inorder_it != inorder.rend()) {
			if (*inorder_it == nstack.top()->val) {
				n = nstack.top();
				nstack.pop();
				inorder_it++;
				nextChildDir = ChildDirection::Left;
			}
			else {
				int v = *(++postorder_it);
				if (nextChildDir == ChildDirection::Left) {
					n->left = new TreeNode(v);
					n = n->left;
				}
				else {
					n->right = new TreeNode(v);
					n = n->right;
				}
				nstack.push(n);
				nextChildDir = ChildDirection::Right;
			}
		}
		return root;
    }
};



int main() {
	
	return 0;
}
