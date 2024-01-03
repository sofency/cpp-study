#include <iostream>
#include <map>
using namespace std;

class Solution {
 public:
  /**
   * @brief 超出时间限制
   *
   * @param nums
   * @param k
   * @return int
   */
  int subarraySumLongTime(vector<int>& nums, int k) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
      int sum = 0;
      for (int start = i; start >= 0; start--) {
        sum += nums[start];
        if (sum == k) {
          count++;
        }
      }
    }
    return count;
  }

  /**
   * @brief
   * prev[0...i-1] + nums[i] = prev[i];
   * // 子数组中存在 i <= j-1
   * prev[j-1] = prev[i] + k;
   *
   * prev[j-1] - k = prev[i];
   *
   *
   * @param nums
   * @param k
   * @return int
   */
  int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    unordered_map<int, int> hashmap;
    hashmap[0] = 1;
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      if (hashmap.find(sum - k) != hashmap.end()) {
        count += hashmap[sum - k];
      }
      hashmap[sum]++;
    }
    return count;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {1, 1, 1};
  cout << solution.subarraySum(temp, 2) << endl;
  return 0;
}
