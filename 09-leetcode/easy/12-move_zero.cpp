#include <iostream>
using namespace std;

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    if (nums.size() <= 1) {
      return;
    }
    int start = 0;
    int begin = 0;
    while (start < nums.size()) {
      if (nums[start] != 0) {
        int temp = nums[start];
        nums[start] = nums[begin];
        nums[begin] = temp;
        begin++;
      }
      start++;
    }
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {0, 1, 0, 3, 12};
  solution.moveZeroes(temp);
  for_each(temp.begin(), temp.end(), [](int val) { cout << val << " "; });
  cout << endl;
  return 0;
}
