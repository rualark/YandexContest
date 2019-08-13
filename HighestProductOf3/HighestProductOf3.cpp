#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <memory>

using namespace std;

int maxp3(vector<int> &A) {
	if (A.size() < 3) return 0;
	if (A.size() == 3) return A[0] * A[1] * A[2];
	sort(A.begin(), A.end());
	int n = A.size();
	if (A[n - 1] * A[n - 2] * A[n - 3] > A[n - 1] * A[0] * A[1]) {
		return A[n - 1] * A[n - 2] * A[n - 3];
	}
	else {
		return A[0] * A[1] * A[n-1];
	}
}

int main() {
	//vector<int> A = { 0, -1, 3, 100, -70, -50 };
	vector<int> A = { -1, -2, -3, -4, -5 };
	int n = maxp3(A);
	cout << n;
}
