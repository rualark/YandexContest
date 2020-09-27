#include <iostream>

using namespace std;

bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

int main() {
	int pcount = 0;
	for (int i = 0; i < 300000; ++i) {
		if (isPrime(i)) {
			pcount += 1;
		}
	}
	cout << "Result: " << pcount << endl;
}
