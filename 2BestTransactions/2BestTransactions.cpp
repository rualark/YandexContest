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

int maxProfit(const vector<int> &A) {
	if (A.empty()) return 0;
	int n = A.size();
	vector<int> Amin(A.size());
	vector<int> Amax(A.size());
	vector<int> A1(A.size());
	vector<int> A2(A.size());
	// Get best first transaction
	Amin[0] = A[0];
	A1[0] = 0;
	for (int i = 1; i < n; ++i) {
		Amin[i] = min(Amin[i - 1], A[i]);
		A1[i] = max(A1[i - 1], A[i] - Amin[i - 1]);
	}
	// Get best second transaction
	Amax[n - 1] = A[n - 1];
	A2[n - 1] = 0;
	for (int i = n - 2; i >= 0; --i) {
		Amax[i] = max(Amax[i + 1], A[i]);
		A2[i] = max(A2[i + 1], Amax[i + 1] - A[i]);
	}
	// Get best transactions pair
	int max_profit = 0;
	for (int i = 1; i < n; ++i) {
		max_profit = max(max_profit, A1[i - 1] + A2[i]);
	}
	max_profit = max(max_profit, A1[n - 1]);
	max_profit = max(max_profit, A2[0]);
	return max_profit;
}

int main() {
	vector<int> vi = { 1, 2 };
	maxProfit(vi);
}