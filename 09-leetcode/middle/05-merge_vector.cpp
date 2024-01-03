/**
 * @file 05-merge_vector.cpp
 * @author your name (you@domain.com)
 * @brief 合并区间
 * @version 0.1
 * @date 2024-01-03
 *
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
using namespace std;
class Solution {
 public:
  /**
   * @brief 先左端点排序
   *
   * @param intervals
   * @return vector<vector<int>>
   */
  static bool compare(vector<int> first, vector<int> second) { return first[0] < second[0]; }
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) {
      return {};
    } else if (intervals.size() == 1) {
      return intervals;
    }
    vector<vector<int>> result;
    sort(intervals.begin(), intervals.end(), this->compare);
    vector<int> temp = intervals[0];
    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i][0] <= temp[1]) {
        // 避免出现 [1,4] [2,3]
        temp = {min(temp[0], intervals[i][0]), max(temp[1], intervals[i][1])};
      } else {
        result.push_back(temp);
        temp = intervals[i];
      }
    }
    result.push_back(temp);
    return result;
  }
};