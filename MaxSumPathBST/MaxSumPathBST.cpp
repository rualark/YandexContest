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

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int recur(TreeNode* A, int &max_sum) {
	if (!A) return 0;
	int sum1 = recur(A->left, max_sum);
	int sum2 = recur(A->right, max_sum);
	int sum = max(0, sum1) + max(0, sum2) + A->val;
	if (sum > max_sum) max_sum = sum;
	return max(sum1, sum2) + A->val;
}

int maxPathSum(TreeNode* A) {
	int max_sum = numeric_limits<int>::min();
	recur(A, max_sum);
	return max_sum;
}

int main() {
	TreeNode* A = new TreeNode(-100);
	A->left = new TreeNode(-200);
	A->left->left = new TreeNode(-300);
	A->left->right = new TreeNode(-400);
	maxPathSum(A);
}
