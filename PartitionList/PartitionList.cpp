#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <memory>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void listInsert(ListNode *before, ListNode *node, ListNode *after) {
	before->next = node;
	node->next = after;
}

void listInsertStart(ListNode *&front, ListNode *node) {
	node->next = front;
	front = node;
}

void listDelete(ListNode *before, ListNode *node, ListNode *after) {
	before->next = after;
}

void listPush(ListNode *&front, ListNode *&back, ListNode *node) {
	if (!front) {
		front = node;
	}
	else {
		back->next = node;
	}
	back = node;
	back->next = nullptr;
}

ListNode* partition(ListNode* A, int B) {
	if (!A) return A;
	if (!A->next) return A;
	ListNode *root = A;
	ListNode *Cfront = nullptr;
	ListNode *Cback = nullptr;
	ListNode *node = nullptr;
	ListNode *node2 = A;
	while (node2) {
		if (node2->val >= B) {
			if (node) {
				node->next = node2->next;
			}
			else {
				root = node2->next;
			}
			ListNode *node_next = node2->next;
			listPush(Cfront, Cback, node2);
			node2 = node_next;
		}
		else {
			node = node2;
			node2 = node2->next;
		}
	}
	if (root) {
		node->next = Cfront;
	}
	else {
		root = Cfront;
	}
	return root;
}

int main() {
	ListNode *root;
	/*
	root = new ListNode(1);
	root->next = new ListNode(2);
	root->next->next = new ListNode(3);
	root->next->next->next = new ListNode(4);
	root->next->next->next->next = new ListNode(5);
	*/
	root = new ListNode(5);
	root->next = new ListNode(2);
	root->next->next = new ListNode(4);
	root->next->next->next = new ListNode(3);
	root->next->next->next->next = new ListNode(1);
	root = partition(root, 3);
}
