#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct NodeLevel {
	NodeLevel(int l, TreeNode* n) : level(l), node(n) {}
	int level;
	TreeNode* node;
};

vector<vector<int> > levelOrder(TreeNode* A) {
	queue<NodeLevel> que;
	que.push(NodeLevel(0, A));
	vector<vector<int>> res;
	while (que.size()) {
		NodeLevel cur_node = que.front();
		que.pop();
		res.resize(cur_node.level + 1);
		res[cur_node.level].push_back(cur_node.node->val);
		if (cur_node.node->left)
			que.push(NodeLevel(cur_node.level + 1, cur_node.node->left));
		if (cur_node.node->right)
			que.push(NodeLevel(cur_node.level + 1, cur_node.node->right));
	}
	return res;
}

int main() {
	TreeNode* A = new TreeNode(5);
	A->left = new TreeNode(3);
	A->right = new TreeNode(4);
	A->left->left = new TreeNode(1);
	A->left->right = new TreeNode(2);
	A->right->left = new TreeNode(7);
	A->right->right = new TreeNode(8);
	vector<vector<int>> res;
	res = levelOrder(A);
}
