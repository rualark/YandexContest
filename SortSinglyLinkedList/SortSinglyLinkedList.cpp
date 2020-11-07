#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int listLen(ListNode* node) {
  int len = 0;
  while (node) {
    ++len;
    node = node->next;
  }
  return len;
}

ListNode* skipList(ListNode* node, int len) {
  while (node && len > 0) {
    --len;
    // Do not return nullptr if reached end of list
    if (!node->next) return node;
    node = node->next;
  }
  return node;
}

tuple<ListNode*, ListNode*> mergeTwoLists(ListNode* node, int len) {
  ListNode* first = nullptr;
  ListNode* last = nullptr;
  ListNode* list1 = node;
  ListNode* list1end = skipList(list1, len - 1);
  ListNode* list2 = list1end->next;
  if (!list2) return { list1, list1end };
  ListNode* list2end = skipList(list2, len - 1);
  ListNode* next = list2end->next;
  list1end->next = nullptr;
  list2end->next = nullptr;
  while (list1 || list2) {
    ListNode* cur = nullptr;
    if (!list1) cur = list2;
    else if (!list2) cur = list1;
    else if (list1->val < list2->val) cur = list1;
    else cur = list2;
    if (cur == list1) {
      list1 = list1->next;
    }
    else {
      list2 = list2->next;
    }
    if (!first) {
      first = cur;
    }
    else {
      last->next = cur;
    }
    last = cur;
  }
  last->next = next;
  return { first, last };
}

ListNode* sortList(ListNode* head) {
  int size = listLen(head);
  int len = 1;
  while (len < size) {
    ListNode* node = head;
    ListNode* prev = nullptr;
    while (node) {
      auto [first, last] = mergeTwoLists(node, len);
      if (node == head) {
        head = first;
      }
      else {
        prev->next = first;
      }
      prev = last;
      node = last->next;
    }
    len += len;
  }
  return head;
}

ListNode* vector2list(vector<int> v) {
  ListNode* head = nullptr;
  for (int i = v.size() - 1; i >= 0; --i) {
    ListNode* node = new ListNode(v[i]);
    node->next = head;
    head = node;
  }
  return head;
}

int main() {
  vector<int> v{ -1, 5, 3, 4, 0 };
  ListNode* list1 = vector2list(v);
  ListNode* list2 = sortList(list1);
  cout << list2 << endl;
}
