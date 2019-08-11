#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>

using namespace std;

void load_words(const string file_name, vector<string> &words) {
	ifstream ifs(file_name);
	string st;
	while (ifs.good()) {
		getline(ifs, st);
		words.push_back(st);
	}
}

struct WordInfo {
	WordInfo(string st) : word(st) {}
	string word;
	vector<string> parent;
};

void transform_words(const string w1, const string w2, const vector<string> &words) {
	if (w1.size() != w2.size()) throw runtime_error("Strings should have same length");
	queue<WordInfo> que;
	unordered_map<string, int> visited_level;
	int cycle = 0;
	que.push(WordInfo(w1));
	visited_level[w1] = 1;
	int found_at_level = numeric_limits<int>::max();
	while (que.size()) {
		WordInfo wi = que.front();
		string st = wi.word;
		int level = wi.parent.size() + 1;
		if (level >= found_at_level) return;
		que.pop();
		for (int i = 0; i < words.size(); ++i) {
			if (words[i].size() != st.size()) continue;
			int changes = 0;
			for (int c = 0; c < st.size(); ++c) {
				if (words[i][c] != st[c]) ++changes;
				if (changes > 1) break;
			}
			if (changes > 1) continue;
			if (visited_level.find(words[i]) != visited_level.end() &&
				visited_level[words[i]] <= level) continue;
			que.push(WordInfo(words[i]));
			que.back().parent = wi.parent;
			que.back().parent.push_back(st);
			visited_level[words[i]] = level + 1;
			if (words[i] == w2) {
				found_at_level = level + 1;
				cout << "Found path after " << cycle << " cycles" << endl;
				//cout << w1 << " -> ";
				for (int i = 0; i < que.back().parent.size(); ++i) {
					cout << que.back().parent[i] << " -> ";
				}
				cout << w2;
				cout << endl;
			}
		}
		cycle++;
	}
	cout << "Not found path from " << w2 << " to " << w1 << " in cycles: " << cycle << endl;
}

void BFS(queue<string> &que, unordered_set<string> &visited, unordered_map<string, string> &parent, const vector<string> &words) {
	string st = que.front();
	que.pop();
	for (int i = 0; i < words.size(); ++i) {
		if (words[i].size() != st.size()) continue;
		int changes = 0;
		for (int c = 0; c < st.size(); ++c) {
			if (words[i][c] != st[c]) ++changes;
			if (changes > 1) break;
		}
		if (changes > 1) continue;
		if (visited.find(words[i]) != visited.end()) continue;
		que.push(words[i]);
		parent[words[i]] = st;
		visited.insert(words[i]);
	}
}

string isIntersecting(unordered_set<string> &svisited, unordered_set<string> &tvisited, const vector<string> &words) {
	for (int i = 0; i < words.size(); ++i) {
		if (svisited.find(words[i]) != svisited.end() &&
			tvisited.find(words[i]) != tvisited.end()) {
			return words[i];
		}
	}
	return "";
}

void transform_words_bidirectional(const string &w1, const string &w2, const vector<string> &words) {
	if (w1.size() != w2.size()) throw runtime_error("Strings should have same length");
	queue<string> sque, tque;
	unordered_set<string> svisited, tvisited;
	unordered_map<string, string> sparent, tparent;
	int cycle = 0;
	sque.push(w1);
	tque.push(w2);
	svisited.insert(w1);
	tvisited.insert(w2);
	while (sque.size() && tque.size()) {
		BFS(sque, svisited, sparent, words);
		BFS(tque, tvisited, tparent, words);
		string intersecting_st = isIntersecting(svisited, tvisited, words);
		if (intersecting_st.size()) {
			cout << "Found path after " << cycle << " cycles" << endl;
			string out_st;
			string cur_word = intersecting_st;
			while (cur_word != w1) {
				if (intersecting_st != cur_word)
					out_st = cur_word + " -> " + out_st;
				cur_word = sparent[cur_word];
			}
			cur_word = intersecting_st;
			while (cur_word != w2) {
				if (intersecting_st != cur_word)
					out_st = out_st + " -> ";
				out_st = out_st + cur_word;
				cur_word = tparent[cur_word];
			}
			cout << w1 << " -> " << out_st << " -> " << w2;
			cout << endl;
			return;
		}
		cycle++;
	}
	cout << "Not found path from " << w1 << " to " << w2 << " in cycles: " << cycle << endl;
}

int main() {
	vector<string> dict;
	load_words("..\\10000_english_words.txt", dict);
	//load_words("..\\370100_english_words.txt", dict);
	dict.push_back("spize");
	dict.push_back("smize");
	transform_words("rift", "rend", dict);
	//transform_words_bidirectional("rift", "rend", dict);
	transform_words("build", "smile", dict);
	//transform_words_bidirectional("build", "smile", dict);
	//transform_words_bidirectional("chicken", "reading", dict);
}
