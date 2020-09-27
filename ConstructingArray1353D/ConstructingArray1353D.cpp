#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Interval {
  Interval(int x_, int y_) : x(x_), y(y_) {}
  int x, y;
  bool operator<(const Interval& other) const {
    if (y - x == other.y - other.x) {
      cout << x << " " << y << " " << other.x << " " << other.y << endl;
      return x > other.x;
    }
    return y - x < other.y - other.x;
  }
};

void fill(vector<int>& a, int x, int y) {
  priority_queue<Interval> s;
  s.emplace(x, y);
  int i = 1;
  while (!s.empty()) {
    auto [x1, y1] = s.top();
    s.pop();
    if (x1 > y1) continue;
    const int mid = floor((x1 + y1) / 2.0);
    cout << x1 << " " << y1 << " " << mid << endl;
    a[mid] = i;
    ++i;
    s.emplace(x1, mid - 1);
    s.emplace(mid + 1, y1);
  }
  for (int i = 0; i < a.size(); ++i) {
    cout << a[i] << " ";
  }
  cout << endl;
}

void solve(int n) {
  vector<int> a;
  a.resize(n);
  fill(a, 0, n - 1);
}

int main() {
  solve(20);
}

