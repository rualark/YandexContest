#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

struct Node {
	Node(int v) : value(v) {}
	int value;
	shared_ptr<Node> l;
	shared_ptr<Node> r;
};

class BSTree {
public:
	friend int main();
	void push(int value) {
		++size;
		shared_ptr<Node> new_node = make_shared<Node>(value);
		if (!root) {
			root = new_node;
			return;
		}
		shared_ptr<Node> cur_node = root;
		shared_ptr<Node> parent_node;
		while (cur_node) {
			parent_node = cur_node;
			if (value < cur_node->value) {
				cur_node = cur_node->l;
			}
			else {
				cur_node = cur_node->r;
			}
		}
		if (value < parent_node->value) {
			parent_node->l = new_node;
		}
		else {
			parent_node->r = new_node;
		}
	}
	int get_min() {
		if (!root) throw runtime_error("Tree is empty");
		shared_ptr<Node> cur_node = root;
		while (cur_node->l) cur_node = cur_node->l;
		return cur_node->value;
	}
	int get_max() {
		if (!root) throw runtime_error("Tree is empty");
		shared_ptr<Node> cur_node = root;
		while (cur_node->r) cur_node = cur_node->r;
		return cur_node->value;
	}
	void print() {
		print_subtree(root, 0, 0);
	}
private:
	void print_subtree(shared_ptr<Node> node, int level, int side) {
		if (!node) return;
		for (int i=0; i<level - 1; ++i) cout << "  ";
		if (level) cout << (side == 1 ? "L " : "") << (side == 2 ? "R " : "");
		cout << node->value << endl;
		print_subtree(node->l, level + 1, 1);
		print_subtree(node->r, level + 1, 2);
	}
	shared_ptr<Node> root;
	int size = 0;
};

struct List {
	shared_ptr<Node> first;
	shared_ptr<Node> last;
};

void tree_to_list_recur(shared_ptr<Node> node, List &lst) {
	if (!node) return;
	tree_to_list_recur(node->l, lst);
	// Link prev node and node
	node->l = lst.last;
	if (lst.last) {
		node->l->r = node;
	}
	else {
		lst.first = node;
	}
	// Move to next node
	lst.last = node;
	tree_to_list_recur(node->r, lst);
}

List tree_to_list(shared_ptr<Node> node) {
	List lst;
	tree_to_list_recur(node, lst);
	return lst; 
}

int main() {
	BSTree bst;
	vector<int> vi;
	std::srand(unsigned(std::time(0)));
	generate_n(back_inserter(vi), 20, []() -> int { return rand() % 100; });
	for (const auto i : vi) {
		bst.push(i);
	}
	bst.print();
	cout << "Min value: " << bst.get_min() << endl;
	cout << "Max value: " << bst.get_max() << endl;
	List lst = tree_to_list(bst.root);
	shared_ptr<Node> node = lst.first;
	while (node) {
		cout << node->value << " ";
		node = node->r;
	}
	return 0;
}
