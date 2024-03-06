#include <iostream>
using namespace std;

class Solution {
 public:
  vector<vector<int>> permute(vector<int> num) {
    vector<bool> used;
    used.resize(num.size(), false);

    vector<vector<int>> result;
    vector<int> temp;
    generate(num, used, 0, result, temp);
    return result;
  }

  void generate(vector<int> num, vector<bool> used, int cur, vector<vector<int>>& result, vector<int> temp) {
    if (cur == num.size()) {
      result.push_back(temp);
      return;
    }
    for (int i = 0; i < num.size(); i++) {
      if (!used[i]) {
        temp.push_back(num[i]);
        used[i] = true;
        generate(num, used, cur + 1, result, temp);
        used[i] = false;
        temp.pop_back();
      }
    }
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {1, 2, 3};
  vector<vector<int>> result = solution.permute(temp);
  for_each(result.begin(), result.end(), [](vector<int> middle) {
    for_each(middle.begin(), middle.end(), [](int val) { cout << val << " "; });
    cout << endl;
  });
  return 0;
}
