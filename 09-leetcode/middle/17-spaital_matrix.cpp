#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    int length = rows * columns;
    // 初始化访问列表为false
    int left = 0;
    int right = matrix[0].size() - 1;
    int top = 0;
    int bottom = matrix.size() - 1;

    vector<int> result;
    while (true) {
      // 向右
      for (int j = left; j <= right; j++) {
        result.push_back(matrix[top][j]);
        cout << "right current push :" << matrix[top][j] << endl;
      }
      top++;
      if (top > bottom)
        break;

      // 向下
      for (int i = top; i <= bottom; i++) {
        result.push_back(matrix[i][right]);
        cout << "bottom current push :" << matrix[i][right] << endl;
      }
      right--;
      if (right < left)
        break;

      // 向左
      for (int j = right; j >= left; j--) {
        result.push_back(matrix[bottom][j]);
        cout << "left current push :" << matrix[bottom][j] << endl;
      }
      bottom--;
      if (bottom < top)
        break;
      // 向上
      for (int i = bottom; i >= top; i--) {
        result.push_back(matrix[i][left]);
        cout << "top current push :" << matrix[i][left] << endl;
      }
      left++;
      if (left > right)
        break;
    }
    return result;
  }
};

int main(int argc, char const* argv[]) {
  vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  Solution solution;
  vector<int> result = solution.spiralOrder(matrix);
  for_each(result.begin(), result.end(), [](int val) { cout << val << " "; });
  cout << endl;
  return 0;
}
