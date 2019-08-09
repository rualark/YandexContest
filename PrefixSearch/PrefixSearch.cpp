#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

struct Node {
	int word_id = 0;
	unordered_map<char, shared_ptr<Node>> child;
};

class Trie {
public:
	Trie() { root = make_shared<Node>(); }
	void push(const string &st, int word_id);
	void count_words(const string &st, int pos, vector<int> &wcount);
private:
	shared_ptr<Node> root;
};

void Trie::push(const string &st, int word_id) {
	shared_ptr<Node> cur_node = root;
	for (int i = 0; i < st.size(); ++i) {
		if (!cur_node->child[st[i]]) {
			cur_node->child[st[i]] = make_shared<Node>();
		}
		cur_node = cur_node->child[st[i]];
	}
	cur_node->word_id = word_id;
}

void Trie::count_words(const string &st, int pos, vector<int> &wcount) {
	shared_ptr<Node> cur_node = root;
	for (int i = pos; i < st.size(); ++i) {
		int level = i - pos;
		if (!cur_node->child[st[i]]) {
			return;
		}
		cur_node = cur_node->child[st[i]];
		if (cur_node->word_id) {
			++wcount[cur_node->word_id];
		}
	}
}

int main() {
	string text = "oh my god, how difficult it is to go home after you travelled around the world so many times that the world became your home";
	vector<int> wcount(7);
	Trie trie;
	trie.push("hello", 1);
	trie.push("how", 2);
	trie.push("hell", 3);
	trie.push("wow", 4);
	trie.push("world", 5);
	trie.push("home", 6);
	for (int i = 0; i < text.size(); ++i) {
		trie.count_words(text, i, wcount);
	}
}
