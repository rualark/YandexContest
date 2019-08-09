#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> mergei(vector<Interval> &A) {
	vector<Interval> B = A;
	vector<Interval> C;
	sort(B.begin(), B.end(), [](const Interval &lhv, const Interval &rhv) -> bool
	{return lhv.start < rhv.start; });
	for (int i = 0; i < B.size(); ++i) {
		int last = i;
		for (int x = i + 1; x < B.size(); ++x) {
			if (B[x].start > B[i].end) {
				break;
			}
			B[i].end = max(B[i].end, B[x].end);
			last = x;
		}
		C.push_back(B[i]);
		i = last;
	}
	sort(C.begin(), C.end(), [](const Interval &lhv, const Interval &rhv) -> bool
	{return lhv.start < rhv.start; });
	return C;
	// Do not write main() function.
	// Do not read input, instead use the arguments to the function.
	// Do not print the output, instead return values as specified
	// Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
}

int main() {
	vector<Interval> A = { {18, 58}, {36, 68}, {12, 85}, {30, 74}, {54, 76}, {31, 75}, {14, 86}, {10, 23}, {7, 79}, {1, 3}, {25, 47}, {6, 24}, {16, 50}, {20, 39}, {60, 94}, {49, 51} };
	vector<Interval> B = mergei(A);
}
