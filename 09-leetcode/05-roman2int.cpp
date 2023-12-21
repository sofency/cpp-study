/**
 * @file 05-roman2int.cpp
 * @author your name (you@domain.com)
 * @brief 罗马数字转整数 & 整数转罗马
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

class Solution {
   public:
    /**
     * @brief 罗马转整数
     *
     * @param s
     * @return int
     */
    int romanToInt(string s) {
        unordered_map<string, int> result = {{"I", 1},   {"V", 5},    {"X", 10},   {"L", 50},   {"C", 100},
                                             {"D", 500}, {"M", 1000}, {"CM", 900}, {"CD", 400}, {"XC", 90},
                                             {"XL", 40}, {"IX", 9},   {"IV", 4}};
        int sum = 0;
        while (s.length() != 0) {
            string p = s.substr(0, 2);
            if (result[p] != 0) {
                sum += result[p];
                s.erase(0, 2);
            } else {
                string temp = s.substr(0, 1);
                sum += result[temp];
                s.erase(0, 1);
            }
        }
        return sum;
    }

    void get_result(string str, int num, string& result) {
        for (int i = 0; i < num; i++) {
            result.append(str);
        }
    }

    /**
     * @brief 整数转罗马
     *
     * @param num
     * @return string
     */
    string intToRoman(int num) {
        // 从大到小依次除以罗马数代表的整数，并记录有多少个
        map<string, int> result = {{"I", 1},   {"V", 5},    {"X", 10},   {"L", 50},   {"C", 100},
                                   {"D", 500}, {"M", 1000}, {"CM", 900}, {"CD", 400}, {"XC", 90},
                                   {"XL", 40}, {"IX", 9},   {"IV", 4}};
        // 定义一个自定义的比较函数，用于按照值进行排序
        auto compareByValue = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        };
        vector<pair<string, int>> sortedMap(result.begin(), result.end());
        sort(sortedMap.begin(), sortedMap.end(), compareByValue);
        vector<pair<string, int>> list;
        while (num != 0) {
            if (num >= 1000) {
                int temp = num / 1000;
                list.push_back(pair<string, int>("M", temp));
                num %= 1000;
            } else if (num >= 900) {
                int temp = num / 900;
                list.push_back(pair<string, int>("CM", temp));
                num %= 900;
            } else if (num >= 500) {
                int temp = num / 500;
                list.push_back(pair<string, int>("D", temp));
                num %= 500;
            } else if (num >= 400) {
                int temp = num / 400;
                list.push_back(pair<string, int>("CD", temp));
                num %= 400;
            } else if (num >= 100) {
                int temp = num / 100;
                list.push_back(pair<string, int>("C", temp));
                num %= 100;
            } else if (num >= 90) {
                int temp = num / 90;
                list.push_back(pair<string, int>("XC", temp));
                num %= 90;
            } else if (num >= 50) {
                int temp = num / 50;
                list.push_back(pair<string, int>("L", temp));
                num %= 50;
            } else if (num >= 40) {
                int temp = num / 40;
                list.push_back(pair<string, int>("XL", temp));
                num %= 40;
            } else if (num >= 10) {
                int temp = num / 10;
                list.push_back(pair<string, int>("X", temp));
                num %= 10;
            } else if (num >= 9) {
                int temp = num / 9;
                list.push_back(pair<string, int>("IX", temp));
                num %= 9;
            } else if (num >= 5) {
                int temp = num / 5;
                list.push_back(pair<string, int>("V", temp));
                num %= 5;
            } else if (num >= 4) {
                int temp = num / 4;
                list.push_back(pair<string, int>("IV", temp));
                num %= 4;
            } else if (num >= 1) {
                int temp = num / 1;
                list.push_back(pair<string, int>("I", temp));
                num %= 1;
            }
        }
        string roman_result = "";
        for (auto it = list.begin(); it != list.end(); it++) {
            get_result(it->first, it->second, roman_result);
        }
        return roman_result;
    }

    /**
     * @brief 简化版转化数字
     *
     * @param num
     * @return string
     */
    string intToRoman_simple(int num) {
        // 从大到小依次除以罗马数代表的整数，并记录有多少个
        pair<string, int> array[] = {{"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100},
                                     {"XC", 90},  {"L", 50},   {"XL", 40}, {"X", 10},   {"IX", 9},
                                     {"V", 5},    {"IV", 4},   {"I", 1}};

        string result = "";
        for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
            while (num >= array[i].second) {
                result.append(array[i].first);
                num -= array[i].second;
            }
            if (num == 0) {
                break;
            }
        }
        return result;
    }
};

int main(int argc, char const* argv[]) {
    Solution soultion;
    cout << soultion.intToRoman_simple(1994) << endl;
    return 0;
}
