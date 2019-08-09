#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

const int SIZE = 31;
vector<int> memo(SIZE);

// Simple recursive dynamic programming variant
int max_minutes(const vector<int> &vi, size_t first) {
	if (first >= vi.size()) return 0;
	int res1 = max_minutes(vi, first + 1);
	int res2 = max_minutes(vi, first + 2) + vi[first];
	return max(res1, res2);
}

// Recursive dynamic programming variant with memo
int max_minutes_memo(const vector<int> &vi, size_t first) {
	if (first >= vi.size()) return 0;
	if (memo[first]) return memo[first];
	int res1 = max_minutes_memo(vi, first + 1);
	int res2 = max_minutes_memo(vi, first + 2) + vi[first];
	memo[first] = max(res1, res2);
	return memo[first];
}

// Iterative dynamic programming variant
int max_minutes_build(vector<int> &vi) {
	vector<int> res(SIZE);
	res[0] = vi[0];
	res[1] = max(vi[0], vi[1]);
	for (int i = 2; i < vi.size(); ++i) {
  	res[i] = max(res[i - 2] + vi[i], res[i - 1]);
	}
	return res.back();
}

// Iterative dynamic programming variant with circular queue
int max_minutes_build_queue(vector<int> &vi) {
	int a = vi[0];
	int b = max(vi[0], vi[1]);
	for (int i = 2; i < vi.size(); ++i) {
		int c = max(a + vi[i], b);
		a = b;
		b = c;
	}
	return b;
}

int main() {
	vector<int> vi;
	srand(time(0));
	generate_n(back_inserter(vi), SIZE, []() -> int {
		return (rand() % 10 + 1) * 15;
	});
	for (int i = vi.size() - 1; i >=0 ; --i) {
		cout << " " << vi[i];
	}
	cout << endl;
	cout << "Best result: " << max_minutes_build_queue(vi) << endl;
	cout << "Best result: " << max_minutes_build(vi) << endl;
	cout << "Best result: " << max_minutes_memo(vi, 0) << endl;
	cout << "Best result: " << max_minutes(vi, 0) << endl;
	return 0;
}
