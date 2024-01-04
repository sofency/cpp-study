/**
 * @file 06-reverse_array.cpp
 * @author your name (you@domain.com)
 * @brief 数组轮转
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
using namespace std;

class Solution {
 public:
  /**
   * @brief
   * 0 1 2 3 4 5 6 7 8 9    k = 2  从nums.size() - k 位置开始各自翻转
   * 6 5 4 3 2 1 0 9 8      reverse整个数组
   * 8 9 0 1 2 3 4 5 6
   *
   * @param nums
   * @param k
   */
  void rotate(vector<int>& nums, int k) {
    if (nums.size() > k) {
      k = nums.size() - k;
    } else {
      // 避免出现比较大的k
      while (k > nums.size()) {
        k -= nums.size();
      }
      k = nums.size() - k;
    }
    for (int i = 0; i < k / 2; i++) {
      int temp = nums[i];
      nums[i] = nums[k - i - 1];
      nums[k - i - 1] = temp;
    }

    for (int i = k; i < (nums.size() + k) / 2; i++) {
      int temp = nums[i];
      nums[i] = nums[nums.size() + k - i - 1];
      nums[nums.size() + k - i - 1] = temp;
    }
    reverse(nums.begin(), nums.end());
  }
};