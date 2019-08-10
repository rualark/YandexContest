#include <vector>
#include <queue>

using namespace std;

struct Node {
	Node(int v) : val(v) {}
	int val;
	vector<Node*> child;
};

int get_depth(Node* node, int &max_dist) {
	priority_queue<int> depth_heap;
	for (int i = 0; i < node->child.size(); ++i) {
		depth_heap.push(get_depth(node->child[i], max_dist));
	}
	int depth1 = 0;
	int depth2 = 0;
	if (depth_heap.size()) {
		depth1 = depth_heap.top();
		depth_heap.pop();
	}
	if (depth_heap.size()) {
		depth2 = depth_heap.top();
		depth_heap.pop();
	}
	if (depth1 + depth2 > max_dist) {
		max_dist = depth1 + depth2;
	}
	return max(depth1, depth2) + 1;
}

int solve(vector<int> &A) {
	vector<vector<int>> links(A.size());
	if (!A.size()) return 0;
	Node root(0);
	// Build links
	for (int i = 0; i < A.size(); ++i) {
		if (A[i] == -1) {
			root.val = i;
		}
		else {
			links[A[i]].push_back(i);
		}
	}
	// Build tree
	queue<Node*> que;
	que.push(&root);
	while (que.size()) {
		Node* node = que.front();
		que.pop();
		int val = node->val;
		for (int i = 0; i < links[val].size(); ++i) {
			node->child.push_back(new Node(links[val][i]));
			que.push(node->child.back());
		}
	}
	int max_dist = 0;
	get_depth(&root, max_dist);
}

int main() {
	vector<int> vi = { -1, 0, 0, 0, 3 };
	solve(vi);
}
