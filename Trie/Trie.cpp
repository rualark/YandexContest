#include <iostream>
#include <unordered_map>

using namespace std;

struct TrieNode {
  unordered_map<char, TrieNode*> child;
  bool isLast = false;
};

class Trie {
public:
  /** Initialize your data structure here. */
  Trie() {

  }

  /** Inserts a word into the trie. */
  void insert(string word) {
    TrieNode* node = &root;
    for (const char& c : word) {
      if (node->child.find(c) == node->child.end()) {
        node->child.insert({ c, new TrieNode() });
      }
      node = node->child[c];
    }
    node->isLast = true;
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
    TrieNode* node = &root;
    for (const char& c : word) {
      if (node->child.find(c) == node->child.end()) return false;
      node = node->child[c];
    }
    if (!node->isLast) return false;
    return true;
  }

  /** Returns if there is any word in the trie that starts with the given prefix. */
  bool startsWith(string prefix) {
    TrieNode* node = &root;
    for (const char& c : prefix) {
      if (node->child.find(c) == node->child.end()) return false;
      node = node->child[c];
    }
    return true;
  }

private:
  TrieNode root;

};

int main() {
  Trie trie = Trie();

  trie.insert("apple");
  cout << trie.search("apple");   // returns true
  cout << trie.search("app");     // returns false
  cout << trie.startsWith("app"); // returns true
  trie.insert("app");
  cout << trie.search("app");     // returns true
}
