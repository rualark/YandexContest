#include <unordered_map>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

void get_shortest_small_in_big(const vector<int> &big, const vector<int> &small, int &start, int &end) {
	// Initialize
	unordered_map<int, int> posmap;
	set<int> posset;
	int n = big.size();
	for (int i = 0; i < small.size(); ++i) {
		int pos = - n - i;
		posset.insert(pos);
		posmap[small[i]] = pos;
	}
	int min_len = n + 1;
	// Loop
	for (int i = 0; i < big.size(); ++i) {
		int val = big[i];
		if (posmap.find(val) == posmap.end()) continue;
		posset.erase(posmap[val]);
		posmap[val] = i;
		posset.insert(i);
		int min_pos = *(posset.begin());
		int len = i - min_pos;
		if (len < min_len) {
			min_len = len;
			start = min_pos;
			end = i;
		}
		cout << "Loop " << i << " min position is " << min_pos << 
			", length is " << len << endl;
	}
}

int main() {
	vector<int> big = {7,5,9,9,2,1,3,5,7,9,1,1,5,8,8,9,7};
	vector<int> small = { 1, 9, 5 };
	int start = 0;
	int end = 0;
	get_shortest_small_in_big(big, small, start, end);
	cout << "Shortest segment goes from " << start << " to " << end << endl;
}