#include <cstdlib>
#include <iostream>
using namespace std;

class Solution {
 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    if (intervals.empty()) {
      result.push_back(newInterval);
      return result;
    }

    int length = intervals.size();
    bool flag = false;
    int left = newInterval[0], right = newInterval[1];
    for (int i = 0; i < length; i++) {
      // 左边
      if (intervals[i][1] < left) {
        result.push_back(intervals[i]);
      } else if (right < intervals[i][0]) {
        // 右侧
        if (!flag) {
          result.push_back({left, right});
          flag = true;
        }
        result.push_back(internals[i]);
      } else {
        left = min(intervals[i][0], left);
        right = max(intervals[i][1], right);
      }
    }
    if (!flag) {
      result.push_back({left, right});
    }
    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<vector<int>> array = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
  vector<int> inter = {4, 8};
  vector<vector<int>> result = solution.insert(array, inter);
  return 0;
}
