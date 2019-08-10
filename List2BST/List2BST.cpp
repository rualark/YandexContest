#include <vector>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

 struct ListNode {
	    int val;
	    ListNode *next;
	    ListNode(int x) : val(x), next(NULL) {}
	};
	

void vec2bst(const vector<int> &vi, int x, int y, TreeNode* node) {
	int mid = (x + y) / 2;
	node->val = vi[mid];
	if (mid > x) {
		node->left = new TreeNode(0);
		vec2bst(vi, x, mid, node->left);
	}
	if (y > mid + 1) {
		node->right = new TreeNode(0);
		vec2bst(vi, mid + 1, y, node->right);
	}
}

TreeNode* sortedListToBST(ListNode* A) {
	if (!A) return nullptr;
	vector<int> temp;
	TreeNode* root = new TreeNode(0);
	ListNode* cur_node = A;
	while (cur_node) {
		temp.push_back(cur_node->val);
		cur_node = cur_node->next;
	}
	vec2bst(temp, 0, temp.size(), root);
	return root;
	// Do not write main() function.
	// Do not read input, instead use the arguments to the function.
	// Do not print the output, instead return values as specified
	// Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
}

int main() {
	ListNode *node = new ListNode(1);
	TreeNode *root = sortedListToBST(node);
}
