/**
 * @file 13-inter_list.cpp
 * @author your name (you@domain.com)
 * @brief 相交链表
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <stack>
using namespace std;
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  /**
   * @brief Get the Intersection Node object
   * 相交链表
   *
   * @param headA
   * @param headB
   * @return ListNode*
   */
  int get_length(ListNode* headA) {
    int count = 0;
    ListNode* prev = headA;
    while (prev) {
      count++;
      prev = prev->next;
    }
    return count;
  }

  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    int lengthA = get_length(headA);
    int lengthB = get_length(headB);
    ListNode *max, *min;
    if (lengthA > lengthB) {
      max = headA;
      min = headB;
    } else {
      max = headB;
      min = headA;
    }

    int distance = abs(lengthA - lengthB);
    for (int i = 0; i < distance; i++) {
      max = max->next;
    }

    while (max && min) {
      if (max == min) {
        return max;
      } else {
        max = max->next;
        min = min->next;
      }
    }
    return nullptr;
  }

  ListNode* getIntersectionNodeVersion2(ListNode* headA, ListNode* headB) {
    ListNode *indexA, *indexB;
    indexA = headA;
    indexB = headB;
    bool flagA = 0, flagB = 0;
    while (indexA && indexB) {
      if (indexA == indexB) {
        return indexA;
      }
      if (indexA->next == nullptr && (!flagA)) {
        indexA = headB;
        indexB = indexB->next;
        flagA = 1;
        continue;
      }
      if (indexB->next == nullptr && (!flagB)) {
        indexB = headA;
        indexA = indexA->next;
        flagB = 1;
        continue;
      }
      indexA = indexA->next;
      indexB = indexB->next;
    }
    return nullptr;
  }

  /**
   * @brief 反转链表
   *
   *              tail  prev
   *       1  <-  2 ->  3 ->  4 ->  5 ->  6
   *
   * temp.next = cur;
   * cur = temp
   *
   *
   * @param head
   * @return ListNode*
   */
  ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) {
      return head;
    }

    ListNode* tail = head;
    ListNode* prev = tail->next;
    tail->next = nullptr;  // 必须加 避免出现 因为新链表与旧链表未断离 会死循环
    while (prev) {
      ListNode* temp = prev->next;
      prev->next = tail;
      tail = prev;
      prev = temp;
    }
    return tail;
  }

  /**
   * @brief 回文链表
   * 1 2 3 4 5 6 7 8 9
   * t t t t t
   * p   p   p   p   p
   * @param head
   * @return true
   * @return false
   */
  bool isPalindrome(ListNode* head) {
    // 找到中间节点 开始节点加到栈中 中间节点后 弹栈比较大小
    stack<int> s;
    ListNode* tail = head;
    ListNode* prev = head;
    while (tail && prev) {
      if (prev->next != nullptr) {
        prev = prev->next->next;
      } else {
        break;
      }

      s.push(tail->val);
      tail = tail->next;
    }

    // 上面要么是prev为nullptr 要么prev->next 为nullptr
    if (prev) {
      tail = tail->next;
    }

    while (tail) {
      int temp = s.top();
      if (temp != tail->val) {
        return false;
      }
      tail = tail->next;
      s.pop();
    }
    return true;
  }

  bool hasCycle(ListNode* head) {
    ListNode* tail = head;
    ListNode* prev = head;
    while (tail && prev) {
      if (prev->next != nullptr) {
        prev = prev->next->next;
      } else {
        break;
      }
      tail = tail->next;

      if (tail == prev) {
        return true;
      }
    }
    return false;
  }
};

int main(int argc, char const* argv[]) {
  ListNode* node1 = new ListNode(1);
  ListNode* node2 = new ListNode(2);
  ListNode* node3 = new ListNode(2);
  ListNode* node4 = new ListNode(1);
  ListNode* node5 = new ListNode(5);
  node1->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;

  Solution solution;
  bool result = solution.isPalindrome(node1);

  return 0;
}
