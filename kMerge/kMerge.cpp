#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	int total = 0;
	vector<vector<int>> vi(n);
	for (int i = 0; i < n; ++i) {
		int n2 = 0;
		cin >> n2;
		total += n2;
		vi[i].resize(n2);
		for (int x = 0; x < n2; ++x) {
			int num;
			cin >> num;
			vi[i][x] = num;
		}
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> vpos(n);

	for (int i = 0; i < n; ++i) {
		if (vi[i].size())
			pq.push(make_pair(vi[i][0], i));
	}

	vector<int> vres(total);

	for (int i = 0; i < total; ++i) {
		auto pr = pq.top();
		pq.pop();
		vres[i] = pr.first;
		int vid = pr.second;
		if (vi[vid].size() > vpos[vid] + 1) {
			++vpos[vid];
			pr.first = vi[vid][vpos[vid]];
			pq.push(move(pr));
		}
	}

	for (auto i : vres) {
		cout << i << " ";
	}
}
