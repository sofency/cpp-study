#include <iostream>
#include <queue>
using namespace std;

class Solution {
 public:
  /**
   * @brief
   * 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
     输出：[3,3,5,5,6,7]
     解释：
     滑动窗口的位置                最大值
      ---------------               -----
      [1  3  -1] -3  5  3  6  7      3
      1 [3  -1  -3] 5  3  6  7       3
      1  3 [-1  -3  5] 3  6  7       5
      1  3  -1 [-3  5  3] 6  7       5
      1  3  -1  -3 [5  3  6] 7       6
      1  3  -1  -3  5 [3  6  7]      7
   *
   * @param nums
   * @param k
   * @return vector<int>
   * 时间复杂度必须控制在o(n)
   * 可以让队列维持一个有序的序列 这样可以达到O(n)的复杂度
   *
   */
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> queues;
    vector<int> result;
    for (int i = 0; i < k; i++) {
      // 这样维护的队列是 降序队列
      while (!queues.empty() && nums[i] >= nums[queues.back()]) {
        queues.pop_back();
      }
      queues.push_back(i);
    }
    result.push_back(nums[queues.front()]);

    for (int i = k; i < nums.size(); i++) {
      while (!queues.empty() && nums[i] >= nums[queues.back()]) {
        queues.pop_back();
      }
      queues.push_back(i);
      // 确保在该窗口内
      while (queues.front() <= i - k) {
        queues.pop_front();
      }
      result.push_back(nums[queues.front()]);
    }

    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {1, -1};
  auto result = solution.maxSlidingWindow(temp, 1);
  for_each(result.begin(), result.end(), [](int val) { cout << val << " "; });
  cout << endl;
  return 0;
}
