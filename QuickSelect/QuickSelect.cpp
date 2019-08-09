#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

void quick_select(vector<int> &vi, size_t i1, size_t i2, size_t k) {
	int i = rand() * (i2 - i1) / (RAND_MAX + 1) + i1;
	if (i == i2) throw runtime_error("Random index too high");
	int val = vi[i];
	int p1 = 0;
	int p2 = 0;
	for (int x = i1; x < i2; ++x) {
		if (x >= i2 - p2) break;
		if (vi[x] < val) {
			swap(vi[x], vi[i1 + p1++]);
		}
		else if (vi[x] > val) {
			swap(vi[x], vi[i2 - 1 - p2++]);
			--x;
		}
	}
	if (i1 + p1 > k) {
		quick_select(vi, i1, i1 + p1, k);
	}
	else if (i2 - p2 <= k) {
		quick_select(vi, i2 - p2, i2, k);
	}
}

int main() {
	vector<int> vi;
	srand(time(0));
	generate_n(back_inserter(vi), 20, []() -> int { return rand() % 100;  });
	for (size_t i = 0; i < vi.size(); ++i) {
		cout << vi[i] << " ";
	}
	cout << endl;
	cout << "Maximum random: " << RAND_MAX << endl;
	quick_select(vi, 0, vi.size(), 5);
	for (size_t i = 0; i < vi.size(); ++i) {
		cout << vi[i] << " ";
	}
	cout << endl;
	return 0;
}
