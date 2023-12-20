#include <iostream>
using namespace std;
#include <algorithm>

/**
 * @brief 寻找两个正序数组中的中位数
 *
 */
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int num1_length = nums1.size();
        int num2_length = nums2.size();
        vector<int> result;
        // 扩容
        result.resize(num1_length + num2_length);
        // 合并
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), result.begin());
        // 排序
        sort(result.begin(), result.end());
        int length = result.size();
        int middle = (length - 1) / 2;

        if (length % 2 == 0) {
            return (result.at(middle) + result.at(middle + 1)) * 1.0 / 2;
        } else {
            return result.at(middle);
        }
    }
};