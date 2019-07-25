#include <iostream>

using namespace std;

int main() {
	int n, prev;
	cin >> n >> prev;
	cout << prev << endl;
	for (int i = 1; i < n; ++i) {
		int num;
		cin >> num;
		if (num != prev)
			cout << num << endl;
		prev = num;
	}
}
