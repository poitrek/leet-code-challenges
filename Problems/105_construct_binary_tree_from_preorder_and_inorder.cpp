#include <algorithm>
#include <iostream>
#include <iterator>
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
/// Time complexity: average ~O(n logn), pessimistic O(n^2). Likely can be done faster.
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

int main() {

	return 0;
}
