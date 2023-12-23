/**
 * @file 06-delete_duplicate_in_sort_list.cpp
 * @author your name (you@domain.com)
 * @brief 删除排序链表中的重复元素
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
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
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) {
      return head;
    }
    ListNode* prev = head;
    ListNode* next = prev->next;
    while (next) {
      if (next->val == prev->val) {
        next = next->next;
        // 断掉后面的链
        prev->next = nullptr;
      } else {
        prev->next = next;
        prev = next;
        next = next->next;
      }
    }

    return head;
  }
};

int main(int argc, char const* argv[]) {
  /* code */
  return 0;
}
