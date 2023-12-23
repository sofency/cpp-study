/**
 * @file 04-binary_two_num_sum.cpp
 * @author your name (you@domain.com)
 * @brief 二进制求和
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
using namespace std;
class Solution {
   public:
    string addBinary(string a, string b) {
        if (a.length() < b.length()) {
            string temp = b;
            b = a;
            a = temp;
        }
        int alength = a.length();
        int blength = b.length();

        // 设置进位位
        int one = 0;
        string result = "";
        for (int i = 0; i < blength; i++) {
            int sum = (b.at(blength - i - 1) - '0') + (a.at(alength - i - 1) - '0') + one;
            int current = sum % 2;
            one = sum / 2;
            result.insert(0, to_string(current));
        }
        for (int i = blength; i < alength; i++) {
            int sum = (a.at(alength - i - 1) - '0') + one;
            int current = sum % 2;
            one = sum / 2;
            result.insert(0, to_string(current));
        }
        if (one != 0) {
            result.insert(0, to_string(one));
        }
        return result;
    }
};
int main(int argc, char const* argv[]) {
    Solution solution;
    cout << solution.addBinary("1010", "1011") << endl;
    return 0;
}
