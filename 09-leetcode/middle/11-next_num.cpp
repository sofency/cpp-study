#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      i--;
    }
    if (i >= 0) {
      int j = nums.size() - 1;
      while (j >= 0 && nums[j] <= nums[i]) {
        j--;
      }
      // Step 3: swap the two elements
      swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> nums = {3, 2, 1, 3, 4};
  solution.nextPermutation(nums);
  return 0;
}
