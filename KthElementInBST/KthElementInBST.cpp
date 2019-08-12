#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <memory>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* inorder(TreeNode *A, TreeNode *root) {
	if (!A) return nullptr;
	if (A->right) {
		TreeNode* node = A->right;
		while (node->left)
			node = node->left;
		return node;
	}
	else {
		TreeNode *cur_node = root;
		TreeNode *next_parent = nullptr;
		while (cur_node) {
			if (A->val < cur_node->val) {
				next_parent = cur_node;
				cur_node = cur_node->left;
			}
			else if (A->val > cur_node->val) {
				cur_node = cur_node->right;
			}
			// If equals
			else break;
		}
		return next_parent;
	}
}

int kthsmallest(TreeNode* A, int B) {
	if (!A) return -1;
	if (!B) return -1;
	TreeNode* node = A;
	while (node->left)
		node = node->left;
	for (int i = 1; i < B; ++i) {
		if (!node) return -1;
		node = inorder(node, A);
	}
	return node->val;
}

int main() {
	TreeNode* A = new TreeNode(3);
	A->left = new TreeNode(1);
	kthsmallest(A, 1);
}
