#include <iostream>
#include <vector>

using namespace std;

int getLongest(vector<int> v) {
  int ones = 0;
  int zeros = 0;
  int prev_ones = 0;
  int add_ones = 0;
  int max = 0;
  bool has_zero = false;
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == 1) {
      if (zeros) {
        if (zeros == 1) {
          add_ones = prev_ones;
          zeros = 0;
        }
        else {
          add_ones = 0;
        }
        zeros = 0;
      }
      ++ones;
    }
    else {
      has_zero = true;
      if (ones) {
        int local_max = ones + add_ones;
        if (local_max > max) max = local_max;
        prev_ones = ones;
        ones = 0;
      }
      ++zeros;
    }
  }
  if (ones) {
    int local_max = ones + add_ones;
    if (local_max > max) max = local_max;
  }
  if (!has_zero) return max - 1;
  else return max;
}

int main() {
  vector<int> v{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 };
  cout << getLongest(v) << endl;
}
