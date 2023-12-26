/**
 * @file 01-devide.cpp
 * @author your name (you@domain.com)
 * @brief 回溯算法
 * @version 0.1
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <map>

using namespace std;
class Solution {
 public:
  /**
   * @brief 组合总和 39 40
   *
   * @param candidates
   * @param target
   * @return vector<vector<int>>
   */
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> temp;
    sort(candidates.begin(), candidates.end());
    backtrack(result, temp, candidates, target, 0);
    return result;
  }

  void backtrack(vector<vector<int>>& result, vector<int> temp, vector<int>& candidates, int target, int id) {
    if (target < 0 || (target != 0 && target < candidates[0])) {
      return;
    }
    // 收集结果
    if (target == 0) {
      result.push_back(temp);
      return;
    }
    for (int i = id; i < candidates.size(); i++) {
      // 过滤掉重复元素
      if (i > id && candidates[i] == candidates[i - 1]) {
        continue;
      }
      temp.push_back(candidates[i]);
      backtrack(result, temp, candidates, target - candidates[i], i + 1);
      temp.pop_back();
    }
  }

  /**
   * @brief 用于判断temp是否为二维数组中的元素
   *
   * @param result
   * @param temp
   * @return true
   * @return false
   */
  bool validate(vector<vector<int>>& result, vector<int> temp) {
    for (auto start = result.begin(); start != result.end(); start++) {
      vector<int> current = *start;
      if (current == temp) {
        return false;
      }
    }
    return true;
  }
  /**
   * @brief leetcode 77组合
   *
   * @param n
   * @param k
   * @return vector<vector<int>>
   */
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> temp;
    combine_list(result, temp, n, k, 1);
    return result;
  }

  void combine_list(vector<vector<int>>& result, vector<int> temp, int n, int k, int start) {
    if (temp.size() == k) {
      result.push_back(temp);
      return;
    }

    for (int i = start; i <= n; i++) {
      temp.push_back(i);
      // 控制向下一层开始搜索
      combine_list(result, temp, n, k, i + 1);
      temp.pop_back();
    }
  }

  /**
   * @brief 电话号码的排列
   *
   * @param digits
   * @return List<String>
   */
  vector<string> letterCombinations(string digits) {
    vector<string> result;

    if (digits.length() == 0) {
      return result;
    }
    map<char, string> mapping = {{'1', ""},    {'2', "abc"},  {'3', "def"}, {'4', "ghi"},  {'5', "jkl"},
                                 {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}, {'0', ""}};
    backtrack_letter(result, "", digits, mapping, 0);
    return result;
  }

  void backtrack_letter(vector<string>& result, string temp, string digits, map<char, string> mapping, int index) {
    // 确定回溯退出条件
    if (index == digits.length()) {
      result.push_back(temp);
      return;
    }
    int length = mapping[digits[index]].length();
    string current = mapping[digits[index]];
    for (int i = 0; i < length; i++) {
      temp.push_back(current[i]);
      backtrack_letter(result, temp, digits, mapping, index + 1);
      temp.pop_back();
    }
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
  auto result = solution.combinationSum(candidates, 8);
  // auto result = solution.combine(4, 2);
  for_each(result.begin(), result.end(), [](vector<int> single) {
    for_each(single.begin(), single.end(), [](int val) { cout << val << " "; });
    cout << endl;
  });
  cout << endl;

  // auto letters = solution.letterCombinations("23");
  // for_each(letters.begin(), letters.end(), [](string str) { cout << str << " "; });
  // cout << endl;
  return 0;
}
