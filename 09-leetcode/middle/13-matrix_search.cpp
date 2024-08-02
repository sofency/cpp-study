#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    for (int i = 0; i < matrix.size(); i++) {
      vector<int> line = matrix[i];
      int line_length = line.size();
      if (target >= line[0] && target <= line[line_length - 1]) {
        if (target == line[0] || target == line[line_length - 1]) {
          return true;
        } else {
          return binarySearch(line, target);
        }
      } else if (target >= line[0] && target > line[line_length - 1]) {
        cout << line[0] << endl;
        continue;
      } else if (target < line[0]) {
        return false;
      }
    }
    return false;
  }

  bool binarySearch(vector<int> array, int target) {
    int length = array.size();
    int left = 0, right = length - 1;
    while (left <= right) {
      int middle = (left + right) / 2;
      if (array[middle] > target) {
        right = middle - 1;
      } else if (array[middle] < target) {
        left = middle + 1;
      } else {
        return true;
      }
    }
    return false;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<vector<int>> array = {{-8, -7, -5, -3, -3, -1, 1}, {2, 2, 2, 3, 3, 5, 7}, {8, 9, 11, 11, 13, 15, 17}};
  cout << solution.searchMatrix(array, -5) << endl;
  return 0;
}
