#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_permutation_inversions(vector<int> &vi) {
	int icount = 0;
	for (int i = 0; i < vi.size() - 1; ++i) {
		for (int j = i + 1; j < vi.size(); ++j) {
			if (vi[i] > vi[j]) ++icount;
		}
	}
	return icount;
}

int main() {
	vector<int> vi(10);
	generate(vi.begin(), vi.end(), []() {
		static int count = 0;
		return ++count;
	});
	for (int i = 0; i < 100; ++i) {
		cout << "Inversions: " << get_permutation_inversions(vi) << endl;
		next_permutation(vi.begin(), vi.end());
	}
}
