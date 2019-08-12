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

void buildTree_recur(TreeNode *node, vector<int> &in, vector<int> &post,
	int in1, int in2, int post2)
{
	int in_pos = find(in.begin() + in1, in.begin() + in2, post[post2]) - in.begin();

	if (in_pos + 1 < in2) {
		node->right = new TreeNode(post[post2 - 1]);
		buildTree_recur(node->right, in, post, in_pos + 1, in2, post2 - 1);
	}
	post2 -= in2 - in_pos - 1;

	if (in_pos > in1) {
		node->left = new TreeNode(post[post2 - 1]);
		buildTree_recur(node->left, in, post, in1, in_pos, post2 - 1);
	}
}

TreeNode* buildTree(vector<int> &in, vector<int> &post) {
	if (!in.size() || !post.size() || in.size() != post.size()) return nullptr;
	TreeNode *root = new TreeNode(post.back());
	buildTree_recur(root, in, post, 0, in.size(), post.size() - 1);
	return root;
}

void buildTree_recur2(TreeNode *node, vector<int> &in, vector<int> &pre,
	int in1, int in2, int pre1)
{
	int in_pos = find(in.begin() + in1, in.begin() + in2, pre[pre1]) - in.begin();

	if (in_pos > in1) {
		node->left = new TreeNode(pre[pre1 + 1]);
		buildTree_recur2(node->left, in, pre, in1, in_pos, pre1 + 1);
	}
	pre1 += in_pos - in1;

	if (in_pos + 1 < in2) {
		node->right = new TreeNode(pre[pre1 + 1]);
		buildTree_recur2(node->right, in, pre, in_pos + 1, in2, pre1 + 1);
	}
}

TreeNode* buildTree2(vector<int> &pre, vector<int> &in) {
	if (!in.size() || !pre.size() || in.size() != pre.size()) return nullptr;
	TreeNode *root = new TreeNode(pre[0]);
	buildTree_recur2(root, in, pre, 0, in.size(), 0);
	return root;
}

int main() {
	//vector<int> in = { 2, 1, 3 };
	//vector<int> post = { 2, 3, 1 };
	//vector<int> pre = { 1, 2, 3 };
	vector<int> in = { 3, 2, 4, 1, 5 };
	vector<int> pre = { 1, 2, 3, 4, 5 };
	//buildTree(in, post);
	buildTree2(pre, in);
}