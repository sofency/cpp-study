#include <iostream>
#include <stack>
using namespace std;

class Solution {
 public:
  string stackToString(const std::stack<char>& s) {
    string result = "";
    stack<char> tempStack = s;  // 创建一个临时栈来避免修改原始栈

    while (!tempStack.empty()) {
      char topChar = tempStack.top();  // 获取栈顶元素
      tempStack.pop();                 // 弹出栈顶元素
      result += topChar;               // 将栈顶元素添加到结果字符串
    }

    reverse(result.begin(), result.end());
    return result;
  };
  string simplifyPath(string path) {
    stack<char> result;
    if (!path.empty() && path.back() == '/') {
      path.pop_back();
    }
    const char* cstr = path.c_str();
    for (int i = 0; i < path.size(); i++) {
      if (cstr[i] == '/' && (result.empty() || result.top() != '/')) {
        result.push(cstr[i]);
      } else if (i + 1 < path.size() && cstr[i] == '.' && cstr[i + 1] == '/' &&
                 (!result.empty() && result.top() == '/')) {
        i += 1;  // 跳过当前位置
      } else if (i + 1 < path.size() && cstr[i] == '.' && cstr[i + 1] == '.') {
        result.pop();  // 弹出顶部的/
        while (!result.empty() && result.top() != '/') {
          result.pop();
        }
        if (!result.empty()) {
          result.pop();
        }
        i += 1;
      } else if (cstr[i] == '/' && (result.empty() || result.top() == '/')) {
        continue;
      } else {
        result.push(cstr[i]);
      }
    }
    string str = stackToString(result);
    return str.length() == 0 ? "/" : str;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  cout << solution.simplifyPath("/../") << endl;
  return 0;
}
