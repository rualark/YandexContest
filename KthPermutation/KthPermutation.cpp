#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

void recur(vector<int> &processed, set<int> &unprocessed, int &k, int k_need) {
	if (!unprocessed.size()) {
		++k;
		return;
	}
	for (const auto i : unprocessed) {
		unprocessed.erase(i);
		processed.push_back(i);
		recur(processed, unprocessed, k, k_need);
		if (k == k_need) 
			return;
		unprocessed.insert(i);
		processed.pop_back();
	}
}

string getPermutation(int A, int B) {
	vector<int> processed(A);
	set<int> unprocessed;
	int k = 0;
	for (int i = 0; i < A; ++i) {
		unprocessed.insert(i + 1);
		processed[i] = i + 1;
	}
	//for (int i = 0; i < B; ++i) next_permutation(processed.begin(), processed.end());
	recur(processed, unprocessed, k, B);
	if (!processed.size()) return "";
	string st;
	for (int i = 0; i < A; ++i) {
		st += to_string(processed[i]);
	}
	return st;
}

int main() {
	string st = getPermutation(9, 120003);
}
