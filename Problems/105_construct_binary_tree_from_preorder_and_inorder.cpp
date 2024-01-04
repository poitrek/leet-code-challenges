#include <algorithm>
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

/// @brief First solution. Idea: the first element of preorder is tree's root, and it partitions inorder into elements
/// that belong to the left subtree, and those that belong to the right subtree.
/// Algorithm outline: take first element of preorder, find it in inorder, partition the sequence into elements before
/// and after the root in inorder, repeat the process recursively for both sequences (subtrees).
/// Time complexity: average ~O(n logn), pessimistic O(n^2). Is done faster in Solution3
class Solution1 {
	TreeNode* buildTreeRec(vector<int>& preorder, int pre_start, vector<int>& inorder, int in_start, int in_end) {
		/// empty subtree
		if (in_start == in_end)
			return nullptr;

		int root_value = preorder[pre_start];
		int root_in_pos = distance(
            inorder.begin(),
            find(inorder.begin() + in_start, inorder.begin() + in_end, root_value));
		
		TreeNode* left_root = buildTreeRec(preorder, pre_start + 1, inorder, in_start, root_in_pos);
		int left_subtree_size = root_in_pos - in_start;
		TreeNode* right_root = buildTreeRec(preorder, pre_start + 1 + left_subtree_size, inorder, root_in_pos + 1, in_end);
		
		TreeNode* root = new TreeNode(root_value);
		root->left = left_root;
		root->right = right_root;
		return root;
	}

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreeRec(preorder, 0, inorder, 0, inorder.size());
    }
};

/// @brief Second solution. Same implementation as first one, a little prettier - takes advantage of iterators
class Solution2 {
	using v_iterator = vector<int>::iterator;

	TreeNode* buildTreeRec(v_iterator preorder_start, v_iterator inorder_start, v_iterator inorder_end) {
		/// empty subtree
		if (inorder_start == inorder_end)
			return nullptr;

		int root_value = *preorder_start;
		auto root_in_pos = find(inorder_start, inorder_end, root_value);
		
		TreeNode* left_root = buildTreeRec(next(preorder_start), inorder_start, root_in_pos);
		int left_subtree_size = distance(inorder_start, root_in_pos);
		TreeNode* right_root = buildTreeRec(preorder_start + left_subtree_size + 1, next(root_in_pos), inorder_end);
		
		TreeNode* root = new TreeNode(root_value);
		root->left = left_root;
		root->right = right_root;
		return root;
	}

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreeRec(preorder.begin(), inorder.begin(), inorder.end());
    }
};

/// @brief Third solution. O(n) time complexity, no recursion. Use stack to store nodes for which we are
/// currently traversing their left (first) subtree. When encountering a value in preorder, we enter its
/// left subtree. Once we find that value in inorder, we enter its right subtree. However, we know that
/// the next value to appear in inorder will be on top of the stack, because it is the most recent one we
/// pushed on the stack. Thus, if the value in inorder we currently point at equals the top of the stack,
/// go to its right (second) subtree and pop it from the stack. We then repeat this procedure until we 
/// reach the end of inorder sequence.
class Solution3 {
	enum class ChildDirection {
		Left, Right
	};
	static constexpr int GUARD_VALUE = -3001;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		auto preorder_it = preorder.begin();
		auto inorder_it = inorder.begin();
		stack<TreeNode*> nstack;
		/// root
		TreeNode* n = new TreeNode(*preorder_it);
		TreeNode* root = n;
		ChildDirection nextChildDir = ChildDirection::Left;
		nstack.push(new TreeNode(GUARD_VALUE)); /// guard
		nstack.push(n);
		while (inorder_it != inorder.end()) {
			if (*inorder_it == nstack.top()->val) {
				n = nstack.top();
				nstack.pop();
				inorder_it++;
				nextChildDir = ChildDirection::Right;
			}
			else {
				int v = *(++preorder_it);
				if (nextChildDir == ChildDirection::Left) {
					n->left = new TreeNode(v);
					n = n->left;
				}
				else {
					n->right = new TreeNode(v);
					n = n->right;
				}
				nstack.push(n);
				nextChildDir = ChildDirection::Left;
			}
		}
		return root;
    }

};


int main() {
	return 0;
}
