/**
 * @file 03-max_sub_length.cpp
 * @author your name (you@domain.com)
 * @brief 最长连续序列
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;
class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    if (nums.size() == 1) {
      return 1;
    } else if (nums.size() == 0) {
      return 0;
    }
    sort(nums.begin(), nums.end());
    int current_length = 1;
    int max_length = 1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] - nums[i - 1] == 1) {
        current_length += 1;
        max_length = max(max_length, current_length);
      } else if (nums[i] == nums[i - 1]) {
        // 0 1 1 2 这样的长度为 0 1 2 即3 所以要跳过
        continue;
      } else {
        max_length = max(max_length, current_length);
        current_length = 1;
      }
    }
    return max_length;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  cout << solution.longestConsecutive(temp) << endl;

  return 0;
}
