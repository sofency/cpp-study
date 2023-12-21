/**
 * @file 07-search_insert_position.cpp
 * @author your name (you@domain.com)
 * @brief 搜索插入位置
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
    int searchInsert(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) > target) {
                return i;
            }
        }
        return nums.size();
    }
};