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

struct Node {
	int is_word = 0;
	unordered_map<char, shared_ptr<Node>> child;
};

class Trie {
public:
	friend vector<string> prefix(vector<string> &A);
	Trie() { root = make_shared<Node>(); }
	void push(const string &st);
private:
	shared_ptr<Node> root;
};

void Trie::push(const string &st) {
	shared_ptr<Node> cur_node = root;
	for (int i = 0; i < st.size(); ++i) {
		if (!cur_node->child[st[i]]) {
			cur_node->child[st[i]] = make_shared<Node>();
		}
		cur_node = cur_node->child[st[i]];
	}
	cur_node->is_word = 1;
}

vector<string> prefix(vector<string> &A) {
	vector<string> result;
	Trie trie;
	for (const auto &st : A) {
		trie.push(st);
	}
	for (const auto &st : A) {
		shared_ptr<Node> node = trie.root;
		int max_level = 0;
		for (int i = 0; i < st.size(); ++i) {
			if (node->child.size() > 1) max_level = i + 1;
			node = node->child[st[i]];
		}
		result.push_back(st.substr(0, max_level));
	}
	return result;
}

int main() {
	vector<string> vs = { "zebra", "dog", "duck", "dove" };
	prefix(vs);
}