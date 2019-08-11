#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

void combinationSum_recur(vector<int> &processed, multiset<int> &unprocessed, int target_sum, vector<vector<int>> &result) {
	// Save if target sum
	if (target_sum == accumulate(processed.begin(), processed.end(), 0)) {
		result.push_back(processed);
	}
	if (!unprocessed.size()) {
		return;
	}
	int prev_value;
	int first_value = 1;
	multiset<int> unprocessed_copy = unprocessed;
	for (const auto i : unprocessed) {
		if (first_value) {
			first_value = 0;
		}
		else {
			// Skip duplicates
			if (prev_value == i) continue;
		}
		prev_value = i;
		// Erase one instance
		unprocessed_copy.erase(unprocessed_copy.find(i));
		processed.push_back(i);
		combinationSum_recur(processed, unprocessed_copy, target_sum, result);
		// Erase all instances
		unprocessed_copy.erase(i);
		processed.pop_back();
	}
}

vector<vector<int> > combinationSum(vector<int> &A, int B) {
	vector<vector<int>> result;
	multiset<int> Aset(A.begin(), A.end());
	vector<int> processed;
	combinationSum_recur(processed, Aset, B, result);
	return result;
}

int main() {
	//vector<int> vi{ 1, 2, 3, 3, 4, 5, 1 };
	vector<int> vi{ 8, 10, 6, 11, 1, 16, 8 };
	vector<vector<int>> result;
	result = combinationSum(vi, 28);
}
