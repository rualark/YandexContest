#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class BigNum {
public:
	BigNum(long long base) : base(base) { }
	void set(long long x) {
		numa.resize(1);
		numa[0] = x;
		mul(1);
	}
	void mul(long long x) {
		long long left = 0;
		for (int i = 0; i < numa.size(); ++i) {
			numa[i] = (numa[i] * x) + left;
			if (numa[i] / base) {
				left = numa[i] / base;
				numa[i] = numa[i] % base;
			}
			else {
				left = 0;
			}
		}
		if (left) {
			numa.push_back(left);
		}
	}
	inline bool operator<(const BigNum& rhs) const {
		assert(rhs.base == base);
		if (rhs.numa.size() == numa.size()) {
			for (int i = numa.size() - 1; i >= 0; --i) {
				if (numa[i] < rhs.numa[i]) return true;
				else if (numa[i] > rhs.numa[i]) return false;
			}
			// If all match
			return false;
		}
		else if (numa.size() < rhs.numa.size()) return true;
		else return false;
	}
	inline bool operator>(const BigNum& rhs) const {
		assert(rhs.base == base);
		if (rhs.numa.size() == numa.size()) {
			for (int i = numa.size() - 1; i >= 0; --i) {
				if (numa[i] > rhs.numa[i]) return true;
				else if (numa[i] < rhs.numa[i]) return false;
			}
			// If all match
			return false;
		}
		else if (numa.size() > rhs.numa.size()) return true;
		else return false;
	}
	long long get_low() const { 
		return numa[0]; 
	}

private:
	long long base;
	vector<long long> numa;
};

long long get_max_mul(int sum, int prohibited) {
	cout << "Sum: " << sum << endl;
	cout << "Prohibited: " << prohibited << endl;
	vector<long double> mr(sum + 1);
	vector<long long> debug_mr(sum + 1);
	long long cycle = 0;
	for (int i = 1; i <= sum; ++i) {
		mr[i] = i;
		for (int j = 2; j < i; ++j) {
			if (j == prohibited) continue;
			if (j > 5)  break;
			long double new_mul = mr[i - j] * j;
			if (new_mul > mr[i]) {
				mr[i] = new_mul;
				debug_mr[i] = j;
			}
			++cycle;
			//cout << "Cycle " << cycle << " for sum " << i << ", depth " << j << endl;
		}
	}
	cout << "Solutions:   ";
	for (int i = 1; i <= sum; ++i) {
		cout << mr[i] << " ";
	}
	cout << endl;
	cout << "Multipliers: ";
	for (int i = 1; i <= sum; ++i) {
		cout << debug_mr[i] << " ";
	}
	cout << endl;
	cout << "Cycles: " << cycle << endl;
	return mr[sum];
}

long long get_max_mul2(int sum, int prohibited) {
	cout << "Sum: " << sum << endl;
	cout << "Prohibited: " << prohibited << endl;
	vector<BigNum> mr(sum + 1, BigNum(1000000007));
	vector<int> debug_mr(sum + 1);
	long long cycle = 0;
	for (int i = 1; i <= sum; ++i) {
		mr[i].set(i);
		for (int j = 2; j < i; ++j) {
			if (j == prohibited) continue;
			if (j > 5)  break;
			BigNum new_mul = mr[i - j];
			new_mul.mul(j);
			if (new_mul > mr[i]) {
				mr[i] = new_mul;
				debug_mr[i] = j;
			}
			++cycle;
			//cout << "Cycle " << cycle << " for sum " << i << ", depth " << j << endl;
		}
	}
	cout << "Solutions:   ";
	for (int i = 1; i <= sum; ++i) {
		cout << mr[i].get_low() << " ";
	}
	cout << endl;
	cout << "Multipliers: ";
	for (int i = 1; i <= sum; ++i) {
		cout << debug_mr[i] << " ";
	}
	cout << endl;
	cout << "Cycles: " << cycle << endl;
	return mr[sum].get_low();
}

int main() {
	//BigNum bn(1000000007);
	//bn.set(10000000000);
	get_max_mul2(1000000, 6);
}
