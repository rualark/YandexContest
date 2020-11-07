#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProductTo(vector<int>& nums, int i, int& minP, int& globalMaxP) {
  int maxP = 1;
  if (i > 0) maxP = maxProductTo(nums, i - 1, minP, globalMaxP);
  int newMinP = min({ nums[i], nums[i] * maxP, nums[i] * minP });
  int newMaxP = max({ nums[i], nums[i] * maxP, nums[i] * minP });
  minP = newMinP;
  globalMaxP = max(globalMaxP, newMaxP);
  return newMaxP;
}

int maxProduct(vector<int>& nums) {
  int minP = 1;
  int globalMaxP = nums[0];
  maxProductTo(nums, nums.size() - 1, minP, globalMaxP);
  return globalMaxP;
}

int main() {
  vector<int> v{ 2, 3, -2, 4 };
  cout << maxProduct(v) << endl;
}
