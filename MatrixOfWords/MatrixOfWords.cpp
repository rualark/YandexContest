#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
	int is_word = 0;
	unordered_map<char, shared_ptr<Node>> child;
};

struct Letter {
	char letter;
	shared_ptr<Node> trie_right;
	shared_ptr<Node> trie_down;
};

class Trie {
public:
	friend bool check_letter(vector<string> &words, vector<Trie> &trie, vector<vector<Letter>> &mat, int prev_y, int prev_x);
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

void load_words(const string file_name, vector<string> &words) {
	ifstream ifs(file_name);
	string st;
	while (ifs.good()) {
		getline(ifs, st);
		transform(st.begin(), st.end(), st.begin(), toupper);
		if (st != "")
			words.push_back(st);
	}
}

void build_trie(vector<string> &words, vector<Trie> &trie) {
	int max_length = 0;
	for (const auto &w : words) {
		if (w.size() > max_length) max_length = w.size();
	}
	trie.resize(max_length + 1);
	for (const auto &w : words) {
		int len = w.size();
		trie[len].push(w);
	}
}

void print_matrix(vector<vector<Letter>> &mat) {
	for (int y = 0; y < mat.size(); ++y) {
		for (int x = 0; x < mat[0].size(); ++x) {
			cout << mat[y][x].letter << " ";
		}
		cout << endl;
	}
}

bool check_letter(vector<string> &words, vector<Trie> &trie, vector<vector<Letter>> &mat, int prev_y, int prev_x) {
	// Move to next point
	int x_size = mat[0].size();
	int y_size = mat.size();
	int x, y;
	if (prev_y == y_size - 1) {
		if (prev_x == x_size - 1) {
			print_matrix(mat);
			return true;
		}
		else {
			x = prev_x + 1;
			y = 0;
		}
	}
	else {
		x = prev_x;
		y = prev_y + 1;
	}
	//cout << "Checking point " << y << " x " << x << endl;
	shared_ptr<Node> left_parent;
	shared_ptr<Node> top_parent;
	if (x) {
		left_parent = mat[y][x - 1].trie_right;
	}
	else {
		left_parent = trie[x_size].root;
	}
	if (y) {
		top_parent = mat[y-1][x].trie_down;
	}
	else {
		top_parent = trie[y_size].root;
	}
	for (const auto &node : left_parent->child) {
		char letter = node.first;
		if (top_parent->child.find(letter) == top_parent->child.end()) continue;
		mat[y][x].letter = letter;
		mat[y][x].trie_right = node.second;
		mat[y][x].trie_down = top_parent->child[letter];
		int res = check_letter(words, trie, mat, y, x);
		if (res) return true;
	}
	return false;
}

bool build_matrix(vector<string> &words, vector<Trie> &trie, vector<vector<Letter>> &mat, int rows, int cols) {
	if (!rows || !cols) throw runtime_error("Please specify non-negative matrix dimensions");
	mat.clear();
	mat.resize(rows);
	for (int i = 0; i < rows; ++i) {
		mat[i].resize(cols);
	}
	return check_letter(words, trie, mat, -1, 0);
}

void max_matrix(vector<string> &words, vector<Trie> &trie, vector<vector<Letter>> &mat) {
	int max_size = (trie.size() - 1) * (trie.size() - 1);
	for (int z = max_size; z > 0; z--) {
		for (int x_size = trie.size() - 1; x_size > 2; --x_size) {
			if (z % x_size) continue;
			int y_size = z / x_size;
			if (y_size > trie.size() - 1) continue;
			if (y_size >= x_size) continue;
			cout << "Checking matrix " << y_size << " x " << x_size << endl;
			if (build_matrix(words, trie, mat, y_size, x_size)) return;
		}
	}
}

int main() {
	vector<string> words;
	vector<Trie> trie;
	vector<vector<Letter>> mat;
	//load_words("..\\10000_english_words.txt", words);
	load_words("..\\370100_english_words.txt", words);
	build_trie(words, trie);
	max_matrix(words, trie, mat);
	//build_matrix(words, trie, mat, 5, 4);
}
