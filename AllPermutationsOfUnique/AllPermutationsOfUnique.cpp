#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

void recur(vector<int> &processed, vector<int> &src, int pos, vector<vector<int>> &result) {
	if (pos == src.size()) {
		result.push_back(processed);
		return;
	}
	for (int i = pos; i < src.size(); ++i) {
		processed[pos] = src[i];
		swap(src[pos], src[i]);
		recur(processed, src, pos + 1, result);
		swap(src[pos], src[i]);
	}
}

vector<vector<int> > permute(vector<int> &A) {
	vector<vector<int>> result;
	vector<int> processed(A.size());
	recur(processed, A, 0, result);
	return result;
}

void recur2(vector<int> &src, int pos, vector<vector<int>> &result) {
	if (pos == src.size()) {
		result.push_back(src);
		return;
	}
	for (int i = pos; i < src.size(); ++i) {
		swap(src[pos], src[i]);
		recur2(src, pos + 1, result);
		swap(src[pos], src[i]);
	}
}

vector<vector<int> > permute2(vector<int> &A) {
	vector<vector<int>> result;
	recur2(A, 0, result);
	return result;
}

void recur3(vector<int> &src, int pos, vector<vector<int>> &result) {
	if (pos == src.size()) {
		result.push_back(src);
		return;
	}
	recur3(src, pos + 1, result);
	for (int i = pos + 1; i < src.size(); ++i) {
		swap(src[pos], src[i]);
		recur3(src, pos + 1, result);
		swap(src[pos], src[i]);
	}
}

vector<vector<int> > permute3(vector<int> &A) {
	vector<vector<int>> result;
	recur3(A, 0, result);
	return result;
}

int main() {
	vector<int> vi = { 1, 2, 3 };
	vector<vector<int>> result;
	result = permute3(vi);
}
