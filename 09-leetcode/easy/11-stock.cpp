/**
 * @file 11-stock.cpp
 * @author your name (you@domain.com)
 * @brief 买卖股票的最佳时机
 * @version 0.1
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
using namespace std;
class Solution {
 public:
  /**
   * @brief easy 121
   * 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
   * @param prices
   * @return int
   */
  int maxProfit(vector<int>& prices) {
    int profit = 0, cost = INT_MAX;
    for (int i = 0; i < prices.size(); i++) {
      cost = min(prices[i], cost);
      profit = max(profit, prices[i] - cost);
    }
    return profit;
  }

  /**
   * @brief 买卖股票2 middle
   * 巧妙转化成每天的利润
   * i天买入 i+3天卖出 等价于
   * prices[i+3]-prices[i] = prices[i+3] - prices[i+2] + (prices[i+2]-prices[i+1]) + (prices[i+1]-prices[i])
   * @param prices 7 1 5 10 3 6 4
   * @return int
   */
  int maxProfitVersion2(vector<int>& prices) {
    if (prices.size() == 0) {
      return 0;
    }
    for (int i = prices.size() - 1; i > 0; i--) {
      prices[i] = prices[i] - prices[i - 1];
    }
    // 删除第一个元素
    prices.erase(prices.begin());

    // 只统计正利润
    int profit = 0;
    for_each(prices.begin(), prices.end(), [&](int val) {
      if (val > 0) {
        profit += val;
      }
    });
    return profit;
  }

  /**
   * @brief 子数组最大和
   *
   * @param temp
   * @return int
   */
  int sub_sum(vector<int>& temp) {
    int profit = 0;
    int prev = 0;
    for (int i = 0; i < temp.size(); i++) {
      prev = max(prev + temp[i], temp[i]);
      profit = max(profit, prev);
    }
    return profit;
  }
};

int main(int argc, char const* argv[]) {
  Solution solution;
  vector<int> temp = {7, 1, 5, 3, 6, 4};
  cout << solution.maxProfitVersion2(temp) << endl;

  return 0;
}
