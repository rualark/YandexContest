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

void recur(TreeNode *node, TreeNode *&list) {
	if (!node) return;
	TreeNode *old_l = node->left;
	TreeNode *old_r = node->right;
	if (list) list->right = node;
	node->left = nullptr; // or list, if double linked list is needed
	list = node;
	recur(old_l, list);
	recur(old_r, list);
}

TreeNode* flatten(TreeNode* A) {
	if (!A) return A;
	TreeNode *list = nullptr;
	recur(A, list);
	return A;
}

// Variant 2
void recur2(TreeNode *node, TreeNode *&list) {
	if (!node) return;
	TreeNode *old_l = node->left;
	TreeNode *old_r = node->right;
	if (list) list->right = node;
	node->left = nullptr; // or list, if double linked list is needed
	list = node;
	recur2(old_l, list);
	recur2(old_r, list);
}

TreeNode* flatten2(TreeNode* A) {
	if (!A) return A;
	TreeNode *list = nullptr;
	recur2(A, list);
	return A;
}

int main() {
	TreeNode* A = new TreeNode(5);
	A->left = new TreeNode(3);
	A->right = new TreeNode(4);
	A->left->left = new TreeNode(1);
	A->left->right = new TreeNode(2);
	A->right->left = new TreeNode(7);
	A->right->right = new TreeNode(8);
	flatten(A);
}