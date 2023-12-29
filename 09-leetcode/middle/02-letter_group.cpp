/**
 * @file 02-letter_group.cpp
 * @author your name (you@domain.com)
 * @brief 字母异位词分组  字母异位词 是由重新排列源单词的所有字母得到的一个新单词。

 * @version 0.1
 * @date 2023-12-29
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
   * @brief 算法思路 每个单词排序后得到唯一一个序列，并根据该序列设置map的key,自身作为map的value中的一员
   *
   * @param strs
   * @return vector<vector<string>>
   */
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    map<string, vector<string>> result;
    for (auto start = strs.begin(); start != strs.end(); start++) {
      string temp = *start;
      string str = temp;
      sort(str.begin(), str.end());
      result[str].push_back(temp);
    }
    vector<vector<string>> list;
    for (auto begin : result) {
      list.push_back(begin.second);
    }
    return list;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<string> arg = {"a"};
  auto result = solution.groupAnagrams(arg);
  for (auto begin : result) {
    for (auto first : begin) {
      cout << first << " ";
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}
