#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
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

int t2Sum(TreeNode* A, int B) {
	stack<TreeNode*> ins; // inorder
	stack<TreeNode*> res; // reverse order
	TreeNode* inode = A;
	while (inode->left) {
		ins.push(inode);
		inode = inode->left;
	}
	TreeNode* rnode = A;
	while (rnode->right) {
		res.push(rnode);
		rnode = rnode->right;
	}
	while (1) {
		int val1 = inode->val;
		int val2 = rnode->val;
		if (val1 != val2 && val1 + val2 == B) return 1;
		if (val1 + val2 < B) {
			if (inode->right) {
				ins.push(inode);
				inode = inode->right;
				while (inode->left) {
					ins.push(inode);
					inode = inode->left;
				}
			}
			else {
				if (!ins.size()) break;
				while (ins.size() && inode->val <= val1) {
					inode = ins.top();
					ins.pop();
				}
				if (inode->val <= val1) break;
			}
		}
		else {
			if (rnode->left) {
				res.push(rnode);
				rnode = rnode->left;
				while (rnode->right) {
					res.push(rnode);
					rnode = rnode->right;
				}
			}
			else {
				if (!res.size()) break;
				while (res.size() && rnode->val >= val2) {
					rnode = res.top();
					res.pop();
				}
				if (rnode->val >= val2) break;
			}
		}
	}
	return 0;
}

int main() {
	/*
	TreeNode* A = new TreeNode(100);
	A->left = new TreeNode(50);
	A->right = new TreeNode(150);
	A->left->left = new TreeNode(25);
	A->left->right = new TreeNode(75);
	A->right->left = new TreeNode(125);
	A->right->right = new TreeNode(175);
	*/
	TreeNode* A = new TreeNode(10);
	A->left = new TreeNode(9);
	A->right = new TreeNode(20);
	int res = t2Sum(A, 19);
	cout << res;
}