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

ListNode* reorderList(ListNode* A) {
	if (!A) return A;
	if (!A->next) return A;
	if (!A->next->next) return A;
	// Find middle
	ListNode *node = A;
	ListNode *node2 = A;
	while (node2->next) {
		node2 = node2->next;
		if (node2->next) {
			node2 = node2->next;
			node = node->next;
		}
	}
	// Remove link from last node in first half
	node2 = node->next;
	node->next = nullptr;
	// Remove link from last node in second half
	node = node2;
	node2 = node->next;
	node->next = nullptr;
	// Reverse second half
	while (node2) {
		ListNode *node3 = node2->next;
		node2->next = node;
		node = node2;
		node2 = node3;
	}
	// Merge two halves (node points to new mid node)
	ListNode *node3 = node;
	ListNode *node4 = node3->next;
	node = A;
	node2 = node->next;
	// Now node and node2 point to first half, node3 and node4 point to second half
	while (node3) {
		node->next = node3;
		node3->next = node2;
		node = node2;
		node3 = node4;
		if (node4) node4 = node4->next;
		if (node2) node2 = node2->next;
	}
	return A;
}

int main() {
	ListNode *root = new ListNode(1);
	root->next = new ListNode(2);
	root->next->next = new ListNode(3);
	root->next->next->next = new ListNode(4);
	root->next->next->next->next = new ListNode(5);
	reorderList(root);
}