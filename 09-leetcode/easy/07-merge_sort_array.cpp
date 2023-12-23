/**
 * @file 07-merge_sort_array.cpp
 * @author your name (you@domain.com)
 * @brief 合并两个有序数组
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (m == 0) {
      nums1 = nums2;
      return;
    } else if (n == 0) {
      return;
    }
    // 位置填充
    nums1.resize(m);
    for (int i = 0; i < n; i++) {
      auto index = find_if(nums1.begin(), nums1.end(), [=](int val) { return val >= nums2[i]; });
      if (index != nums1.end()) {
        int location = distance(nums1.begin(), index);
        nums1.insert(index, nums2[i]);
      } else {
        nums1.push_back(nums2[i]);
      }
    }
  }
};

int main(int argc, char const* argv[]) {
  vector<int> list = {1, 2, 7, 8, 10, 12, 0, 0, 0};
  vector<int> list1 = {1, 2, 3, 5, 5, 11, 0, 0, 0};
  Solution solution;
  solution.merge(list, 6, list1, 6);

  for_each(list.begin(), list.end(), [](int val) { cout << val << " "; });
  cout << endl;

  return 0;
}
