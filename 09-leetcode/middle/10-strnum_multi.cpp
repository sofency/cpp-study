#include <iostream>
using namespace std;
// 字符串整数相乘

class Solution {
 public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
      return "0";
    }
    // 反转位置
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    // 123 -> 321
    // 456 -> 654
    string result_str = "";
    for (int i = 0; i < num1.size(); i++) {
      // 记录进位位
      int one = 0;
      // 负责填充前面的0
      string temp;
      temp.resize(i, '0');
      for (auto tail = num2.begin(); tail != num2.end(); tail++) {
        int number1 = num1[i] - '0';
        int number2 = *tail - '0';

        int result = number1 * number2 + one;
        one = result / 10;
        result %= 10;
        char result_temp = result + '0';
        temp.push_back(result_temp);
      }
      if (one != 0) {
        temp.push_back(one + '0');
      }

      // 相加
      if (result_str == "") {
        result_str = temp;
      } else {
        result_str = str_add(result_str, temp);
      }
    }
    reverse(result_str.begin(), result_str.end());
    return result_str;
  }

  // 两个字符串相加
  string str_add(string first, string second) {
    // 调整长度顺序
    if (first.size() < second.size()) {
      string temp = second;
      second = first;
      first = temp;
    }

    string result;
    // 记录进位位
    int one = 0;
    for (int i = 0; i < first.size(); i++) {
      int first_num = first[i] - '0';
      int second_num = 0;
      if (i < second.size()) {
        second_num = second[i] - '0';
      }
      int result_num = first_num + second_num + one;
      one = result_num / 10;
      result_num %= 10;
      result.push_back(result_num + '0');
    }
    if (one != 0) {
      result.push_back(one + '0');
    }
    return result;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  cout << solution.multiply("123", "456") << endl;
  return 0;
}
