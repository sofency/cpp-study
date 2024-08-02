#include <iostream>
using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int height = matrix.size();
    // 水平翻转
    for (int i = 0; i < height / 2; i++) {
      for (int j = 0; j < height; j++) {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[height - i - 1][j];
        matrix[height - i - 1][j] = temp;
      }
    }

    // 对角线翻转
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < i; j++) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }
  }
};