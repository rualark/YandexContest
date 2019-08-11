#include <vector>
#include <unordered_map>
#include <map>
#include <queue>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
	if (!node) return nullptr;
	UndirectedGraphNode *root = new UndirectedGraphNode(node->label);
	unordered_map<uintptr_t, UndirectedGraphNode*> src_to_tgt;
	queue<UndirectedGraphNode*> src_que;
	src_to_tgt[reinterpret_cast<uintptr_t>(node)] = root;
	src_que.push(node);
	while (src_que.size()) {
		UndirectedGraphNode* src = src_que.front();
		UndirectedGraphNode* tgt = src_to_tgt[reinterpret_cast<uintptr_t>(src)];
		src_que.pop();
		// Copy neighbors
		for (const auto n : src->neighbors) {
			// Check if this is link to existing node in tgt
			uintptr_t nip = reinterpret_cast<uintptr_t>(n);
			if (src_to_tgt.find(nip) != src_to_tgt.end()) {
				tgt->neighbors.push_back(src_to_tgt[nip]);
				continue;
			}
			// Create empty node
			UndirectedGraphNode* neighbor = new UndirectedGraphNode(n->label);
			// Add empty node to graph
			tgt->neighbors.push_back(neighbor);
			// Queue copying this node
			src_que.push(n);
			// Pair src and tgt
			src_to_tgt[nip] = neighbor;
		}
	}
	return root;
}

int main() {
	UndirectedGraphNode *src = new UndirectedGraphNode(1);
	src->neighbors.push_back(new UndirectedGraphNode(2));
	src->neighbors.push_back(new UndirectedGraphNode(3));
	src->neighbors.push_back(new UndirectedGraphNode(4));
	src->neighbors[0]->neighbors.push_back(new UndirectedGraphNode(5));
	src->neighbors[0]->neighbors.push_back(new UndirectedGraphNode(6));
	src->neighbors[1]->neighbors.push_back(new UndirectedGraphNode(7));
	src->neighbors[1]->neighbors.push_back(new UndirectedGraphNode(8));
	src->neighbors[1]->neighbors[0]->neighbors.push_back(src);
	UndirectedGraphNode *tgt = cloneGraph(src);
}
