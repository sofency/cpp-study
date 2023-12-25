/**
 * @file 00-kuohao.cpp
 * @author your name (you@domain.com)
 * @brief 括号生成
 * @version 0.1
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<string> result;
    generate(result, "", 0, 0, n);
    return result;
  }

  void generate(vector<string>& result, string cur, int open, int close, int n) {
    if (cur.length() == 2 * n) {
      result.push_back(cur);
      return;
    }
    if (open < n) {
      generate(result, cur + "(", open + 1, close, n);
    }
    if (close < open) {
      generate(result, cur + ")", open, close + 1, n);
    }
  }

  void generate_from_max(vector<string>& result, string cur, int open, int close) {
    if (open == 0 && close == 0) {
      result.push_back(cur);
      return;
    }
    if (open > 0) {
      generate_from_max(result, cur + "(", open - 1, close);
    }
    if (close > open) {
      generate_from_max(result, cur + ")", open, close - 1);
    }
  }
};