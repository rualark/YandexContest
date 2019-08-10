#include <vector>
#include <queue>
#include <memory>
#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int id;
	int in_count = 0;
	int visited = 0;
	int discovery_time = 0;
	int finish_time = 0;
	Node* dfs_parent;
	vector<Node*> child;
};

void tsort(vector<Node> &nodes, queue<Node*> &order) {
	queue<Node*> que;
	for (auto &node : nodes) {
		if (!node.in_count) que.push(&node);
	}
	while (que.size()) {
		Node* pnode = que.front();
		que.pop();
		order.push(pnode);
		for (const auto &child : pnode->child) {
			child->in_count--;
			if (!child->in_count) que.push(child);
		}
	}
	if (order.size() != nodes.size()) throw runtime_error("Some nodes could not be queued");
}

void build_nodes(int node_count, vector<pair<int, int>> &edges, vector<Node> &nodes) {
	nodes.resize(node_count);
	for (int i = 0; i < node_count; ++i) nodes[i].id = i;
	for (const auto &e : edges) {
		nodes[e.second].in_count++;
		nodes[e.first].child.push_back(&nodes[e.second]);
	}
}

void DFS_visit(vector<Node> &nodes, Node* pnode) {
	static int current_time = 0;
	current_time++;
	pnode->discovery_time = current_time;
	pnode->visited = 1;
	for (const auto &child : pnode->child) {
		if (child->visited) continue;
		child->dfs_parent = pnode;
		DFS_visit(nodes, child);
	}
	current_time++;
	pnode->finish_time = current_time;
	pnode->visited = 2;
}

void DFS(vector<Node> &nodes) {
	for (auto &node : nodes) {
		if (!node.visited) 
			DFS_visit(nodes, &node);
	}
}

void tsort_DFS_visit(vector<Node> &nodes, stack<Node*> &nstack, Node* pnode) {
	pnode->visited = 1;
	for (const auto &child : pnode->child) {
		if (child->visited) continue;
		tsort_DFS_visit(nodes, nstack, child);
	}
	nstack.push(pnode);
}

void tsort_DFS(vector<Node> &nodes, queue<Node*> &order) {
	stack<Node*> nstack;
	for (auto &node : nodes) {
		if (!node.visited)
			tsort_DFS_visit(nodes, nstack, &node);
	}
	// Build order
	while (nstack.size()) {
		order.push(nstack.top());
		nstack.pop();
	}
	if (order.size() != nodes.size()) throw runtime_error("Some nodes could not be queued");
}

int main() {
	int node_count = 7;
	vector<pair<int, int>> edges = { {5, 1}, {5, 2}, {5, 0}, {1, 0}, {2, 0}, {0, 4}, {1, 4}, {3, 6} };
	vector<Node> nodes;
	queue<Node*> order;
	build_nodes(node_count, edges, nodes);
	//tsort(nodes, order);
	//DFS(nodes);
	tsort_DFS(nodes, order);
}
