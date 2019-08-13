#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <memory>

using namespace std;

void floodFill(vector<vector<char> > &A, int y, int x, char c) {
	if (y < 0 || y >= A.size()) return;
	if (x < 0 || x >= A[0].size()) return;
	if (A[y][x] == 'X' || A[y][x] == c) return;
	A[y][x] = c;
	floodFill(A, y - 1, x, c);
	floodFill(A, y + 1, x, c);
	floodFill(A, y, x - 1, c);
	floodFill(A, y, x + 1, c);
}

void solve(vector<vector<char> > &A) {
	for (int y = 0; y < A.size(); ++y) {
		int x;
		x = 0;
		if (A[y][x] == 'O') floodFill(A, y, x, 'A');
		x = A[y].size() - 1;
		if (A[y][x] == 'O') floodFill(A, y, x, 'A');
	}
	for (int x = 0; x < A[0].size(); ++x) {
		int y;
		y = 0;
		if (A[y][x] == 'O') floodFill(A, y, x, 'A');
		y = A.size() - 1;
		if (A[y][x] == 'O') floodFill(A, y, x, 'A');
	}
	for (int y = 0; y < A.size(); ++y) {
		for (int x = 0; x < A[y].size(); ++x) {
			if (A[y][x] == 'O') {
				floodFill(A, y, x, 'X');
			}
		}
	}
	for (int y = 0; y < A.size(); ++y) {
		for (int x = 0; x < A[y].size(); ++x) {
			if (A[y][x] == 'A') A[y][x] = 'O';
		}
	}
}

int main() {
	//vector<string> sboard = { "XOXXXXOOXX", "XOOOOXOOXX", "OXXOOXXXOO", "OXOXOOOXXO", "OXOOXXOOXX", "OXXXOXXOXO", "OOXXXXOXOO" };
	//vector<string> sboard = { "XXXXOOOX", "XXOOXOOX", "OXXXXOXX" };
	vector<string> sboard = { "XOOOOOOX", "XXOOXOOX", "OXXOXOXX" };
	vector<vector<char> > board(sboard.size());
	for (int y = 0; y < sboard.size(); ++y) {
		for (int x = 0; x < sboard[y].size(); ++x) {
			board[y].push_back(sboard[y][x]);
		}
	}
	solve(board);
}
