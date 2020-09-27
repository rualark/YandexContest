#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Dot {
  int x, y;
};

int getMinX(const vector<Dot>& dots) {
  int minX = dots[0].x;
  for (auto const& dot : dots) {
    if (dot.x < minX) minX = dot.x;
  }
  return minX;
}

int getMaxX(const vector<Dot>& dots) {
  int maxX = dots[0].x;
  for (auto const& dot : dots) {
    if (dot.x > maxX) maxX = dot.x;
  }
  return maxX;
}

bool checkDotsAreVerticallySymmetric(const vector<Dot>& dots) {
  if (dots.empty()) return false;
  const int minX = getMinX(dots);
  const int maxX = getMaxX(dots);
  const bool cenXisInt = !((minX + maxX) % 2);
  const int cenX2 = minX + maxX;
  unordered_map<int, unordered_map<int, int>> mp;
  for (auto const& dot : dots) {
    if (cenXisInt && 2 * dot.x == cenX2) continue;
    if (mp.find(dot.x) != mp.end()) {
      if (mp[dot.x].find(dot.y) != mp[dot.x].end()) {
        mp[dot.x][dot.y] ++;
      }
      else {
        mp[dot.x].try_emplace(dot.y, 1);
      }
    }
    else {
      mp[dot.x][dot.y] = 1;
    }
  }
  for (auto const& dot : dots) {
    if (cenXisInt && 2 * dot.x == cenX2) continue;
    const int mirX = minX + maxX - dot.x;
    if (mp.find(mirX) == mp.end()) return false;
    if (mp[mirX].find(dot.y) == mp[mirX].end()) return false;
    if (!mp[mirX][dot.y]) return false;
    mp[mirX][dot.y]--;
  }
  return true;
}

int main() {
  vector<Dot> dots;
  dots.push_back({ 1, 2 });
  dots.push_back({ 2, 3 });
  dots.push_back({ 3, 2 });
  cout << checkDotsAreVerticallySymmetric(dots) << endl;
}
