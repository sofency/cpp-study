#include <string.h>
#include <iostream>
using namespace std;

/**
 * @brief 字符串转整数
 *
 */
class Solution {
   public:
    int myAtoi(string s) {
        // 首先移除两边空格
        s.erase(0, s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ') + 1, s.length());

        // 找到第一个字符前的索引
        size_t index = s.find_first_of("0123456789");
        // 说明没有数字存在
        if (index == -1 || index > 1)
            return 0;

        // true为正数 false为负数
        bool flag = true;
        if (index == 1) {
            if (s.at(0) == '-') {
                flag = false;
            } else if (s.at(0) == '+') {
                flag = true;
            } else {
                return 0;
            }
            s.erase(0, 1);
        }

        // 移除前面的0
        s.erase(0, s.find_first_not_of('0'));
        int back = s.find_first_not_of("0123456789");
        if (back != -1) {
            s.erase(back, s.size());
        }

        int i = 0;

        int length = s.size();
        long result = 0, cur = 1;
        while (i < length) {
            int temp = s.at(length - i - 1) - '0';
            result += (temp * cur);
            cur *= 10;
            if (cur > INT32_MAX) {
                return flag ? INT32_MAX : INT32_MIN;
            }
            i++;
        }

        if (flag) {
            if (result >= INT32_MAX) {
                return INT32_MAX;
            } else {
                return result;
            }
        } else {
            if (result > INT32_MAX) {
                return INT32_MIN;
            } else {
                return -result;
            }
        }
    }
};

int main(int argc, char const* argv[]) {
    Solution solution;
    cout << solution.myAtoi("-91283472332") << endl;
    return 0;
}
