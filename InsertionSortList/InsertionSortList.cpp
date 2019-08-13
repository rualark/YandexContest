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

ListNode* insertionSortList(ListNode* A) {
	if (!A) return A;
	if (!A->next) return A;
	ListNode* root = A;
	ListNode* node = A;
	ListNode* node2 = A->next;
	while (node2) {
		ListNode* node3 = nullptr;
		ListNode* node4 = root;
		while (node4 != node2) {
			if (node4->val > node2->val) {
				node->next = node2->next;
				node2->next = node4;
				if (node3) node3->next = node2;
				else root = node2;
				node2 = node;
				break;
			}
			node3 = node4;
			node4 = node4->next;
		}
		node = node2;
		node2 = node2->next;
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
	root = insertionSortList(root);
}
