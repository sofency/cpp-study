/**
 * @file 02-last_word_length.cpp
 * @author your name (you@domain.com)
 * @brief 最后一个单词的长度
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;
class Solution {
    // 5
    // hello world;
   public:
    int lengthOfLastWord(string s) {
        int space_index = s.find_last_not_of(' ');
        if (space_index != -1) {
            s.erase(space_index + 1, s.length());
        }

        int index = s.find_last_of(' ');
        if (index == -1) {
            return s.length();
        } else {
            return s.length() - 1 - index;
        }
    }
};

int main(int argc, char const* argv[]) {
    Solution solution;
    cout << solution.lengthOfLastWord("Hello World") << endl;
    return 0;
}
