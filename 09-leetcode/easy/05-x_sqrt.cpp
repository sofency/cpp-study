/**
 * @file 05-x_sqrt.cpp
 * @author your name (you@domain.com)
 * @brief x的平方根
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
  int mySqrt(int x) {
    if (x == 1)
      return 1;

    int left = 0;
    int right = x;
    while (left + 1 < right) {
      int middle = (left + right) / 2;
      if (x / middle < middle) {
        right = middle;
      } else {
        left = middle;
      }
    }
    return left;
  }
};
int main(int argc, char const* argv[]) {
  Solution solution;
  cout << solution.mySqrt(1) << endl;
  return 0;
}
