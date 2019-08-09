#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check_purses_valid(vector<int> &pa, int sum) 
{
	sort(begin(pa), end(pa));
	if (pa.back() > sum) return false;
	if (pa.back() == sum) return true;
	int left = sum - pa.back();
	vector<vector<int>> A;
	A.resize(pa.size());
	for (int i = 0; i < pa.size(); ++i) {
		A[i].resize(left + 1);
		A[i][0] = 0;
	}
	for (int j = 0; j <= left; ++j) {
		A[0][j] = 0;
	}
	for (int i = 1; i < pa.size(); ++i) {
		int k = i - 1;
		for (int j = 1; j <= left; ++j) {
			if (j >= pa[k]) {
				A[i][j] = max(A[i - 1][j], A[i - 1][j - pa[k]] + pa[k]);
				if (A[i][j] == left) 
					return true;
			}
			else {
				A[i][j] = A[i - 1][j];
			}
		}
	}
	return false;
}

int main()
{
	//vector<int> pa{ 3, 2 };
	//int sum = 3;
	vector<int> pa{ 7, 3, 4, 5, 6, 7, 8 };
	int sum = 17;
	bool res = check_purses_valid(pa, sum);
	cout << res;
}
