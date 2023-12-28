/**
 * @file 10-triagnle.cpp
 * @author your name (you@domain.com)
 * @brief 杨辉三角
 * @version 0.1
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;
class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> result;
    for (int i = 1; i <= numRows; i++) {
      vector<int> temp;
      for (int j = 1; j <= i; j++) {
        if (i == 1 || j == 1 || j == i) {
          temp.push_back(1);
        } else {
          temp.push_back(result[i - 2][j - 2] + result[i - 2][j - 1]);
        }
      }
      result.push_back(temp);
    }
    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  auto result = solution.generate(5);
  for_each(result.begin(), result.end(), [](vector<int> temp) {
    for_each(temp.begin(), temp.end(), [](int val) { cout << val << " "; });
    cout << endl;
  });
  cout << endl;
  return 0;
}
