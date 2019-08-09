#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<size_t>> stv;

int main() {
	vector<string> sv = { "Hello", "world", "message", "this", "is", "you", "my", "first", "is", "message", "to", "you" };
	for (int i = 0; i < sv.size(); ++i) {
		stv[sv[i]].push_back(i);
	}
	return 0;
}