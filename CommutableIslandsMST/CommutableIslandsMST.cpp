#include <vector>
#include <unordered_map>
#include <map>
#include <queue>

using namespace std;

struct NodeWeight {
	NodeWeight(int n, int w, int p) : node(n), weight(w), parent(p) {}
	int node;
	int weight;
	int parent;
	bool operator<(const NodeWeight &rhs) const {
		return weight > rhs.weight;
	}
};

int solve(int A, vector<vector<int> > &B) {
	vector<vector<pair<int, int>>> adj(A);
	for (const auto &b : B) {
		adj[b[0] - 1].push_back(make_pair(b[1] - 1, b[2]));
		adj[b[1] - 1].push_back(make_pair(b[0] - 1, b[2]));
	}
	priority_queue<NodeWeight> que;
	vector<int> node_weight(A);
	unordered_map<int, int> mst_parent;
	int total_weight = 0;
	for (int i = 0; i < A; ++i) {
		//que.push(NodeWeight(i, numerical_limits<int>::max()));
		node_weight[i] = numeric_limits<int>::max();
	}
	que.push(NodeWeight(0, 0, -1));
	node_weight[0] = 0;
	while (que.size()) {
		int min_node = que.top().node;
		int min_parent = que.top().parent;
		int min_weight = que.top().weight;
		que.pop();
		// Skip duplicates
		if (mst_parent.find(min_node) != mst_parent.end()) continue;
		total_weight += min_weight;
		mst_parent[min_node] = min_parent;
		for (const auto &a : adj[min_node]) {
			if (mst_parent.find(a.first) != mst_parent.end()) continue;
			if (a.second < node_weight[a.first]) {
				node_weight[a.first] = a.second;
				que.push(NodeWeight(a.first, a.second, min_node));
			}
		}
	}
	return total_weight;
}

int main() {
	int v_size = 4;
	vector<vector<int>> edges_and_weights = {
		{1, 2, 1}, // v1, v2, weight
		{2, 3, 4},
		{1, 4, 3},
		{4, 3, 2},
		{1, 3, 10},
	};
	solve(v_size, edges_and_weights);
}