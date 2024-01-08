/**
 * @file reverseklist.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
 public:
  /**
   * @brief
   * 队尾指针
   * 1 -> 2 -> 3 -> 4 -> 5
   *
   * 1 <- 2 -> 3  -> 4 -> 5
   *
   * 0   队尾指针  prev        tail     temp
   * 1   head     head.next   head     prev.next
   * 2   head     
   *
   * @param head
   * @param k
   * @return ListNode*
   */
  ListNode* reverseKGroup(ListNode* head, int k) {}
};