#include <string>
#include <iostream>

using namespace std;

int s_in_j(string &s, string &j) {
	int cnt = 0;
	for (const auto sc : s) {
		for (const auto sj : j) {
			if (sc == sj) {
				++cnt;
				break;
			}
		}
	}
	return cnt;
}

int main() {
	string s, j;
	cin >> j;
	cin >> s;
	cout << s_in_j(s, j);
}
