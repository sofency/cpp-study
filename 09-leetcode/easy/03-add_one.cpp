/**
 * @file 03-add_one.cpp
 * @author your name (you@domain.com)
 * @brief 数组型的数组 + 1
 * [1,2,3] + 1 = [1,2,4]
 * [1,2,9] + 1 = [1,3,0]
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;

class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        int length = digits.size();
        int temp = 0;  // 进位位
        bool flag = true;
        for (int i = 0; i < length; i++) {
            if (flag) {
                // 第一次加1
                int sum = digits[length - i - 1] + 1;
                digits[length - i - 1] = sum % 10;
                temp = sum / 10;
                flag = false;
            } else {
                // 加上进位位
                int sum = digits[length - i - 1] + temp;
                digits[length - i - 1] = sum % 10;
                temp = sum / 10;
            }
        }
        if (temp != 0) {
            digits.insert(digits.begin(), temp);
        }
        return digits;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> list = {1, 2, 3};
    Solution solution;
    solution.plusOne(list);
    for_each(list.begin(), list.end(), [](int val) { cout << val << endl; });
    return 0;
}
