#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double median(const vector<int>& n) {
  if (!n.size()) return 0;
  if (n.size() % 2) {
    return n[n.size() / 2];
  }
  else {
    return (n[n.size() / 2 - 1] + n[n.size() / 2]) / 2.0;
  }
}

double findMedianSortedArrays(vector<int>& n1, vector<int>& n2) {
  if (n1.size() > n2.size()) return findMedianSortedArrays(n2, n1);
  if (!n1.size()) return median(n2);
  int left = 0;
  int right = n1.size();
  while (true) {
    int p1 = (left + right) / 2;
    int p2 = (n1.size() + n2.size()) / 2 - p1;
    if (p1 < n1.size() && p2 && n2[p2 - 1] > n1[p1]) {
      left = p1 + 1;
    }
    else if (p2 < n2.size() && p1 && n1[p1 - 1] > n2[p2]) {
      right = p1 - 1;
    }
    else {
      if ((n1.size() + n2.size()) % 2) {
        if (p1 == n1.size()) return n2[p2];
        if (p2 == n2.size()) return n1[p1];
        return min(n1[p1], n2[p2]);
      }
      else {
        int max1;
        if (!p1) max1 = n2[p2 - 1];
        else if (!p2) max1 = n1[p1 - 1];
        else max1 = max(n1[p1 - 1], n2[p2 - 1]);
        int min2;
        if (p1 == n1.size()) min2 = n2[p2];
        else if (p2 == n2.size()) min2 = n1[p1];
        else min2 = min(n1[p1], n2[p2]);
        return (max1 + min2) / 2.0;
      }
    }
  }
}

int main() {
  vector<int> v1{ 1 };
  vector<int> v2{ 2,3,4,5 };
  cout << findMedianSortedArrays(v1, v2) << endl;
}
