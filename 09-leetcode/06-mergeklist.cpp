/**
 * @file 06-mergeklist.cpp
 * @author your name (you@domain.com)
 * @brief 合并k个有序链表
 * @version 0.1
 * @date 2023-12-21
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return nullptr;
        } else if (lists.size() == 1) {
            return lists.at(0);
        } else {
            ListNode* ans = nullptr;
            // 删除第一个元素
            for (auto start = lists.begin(); start != lists.end(); start++) {
                ans = mergeTwoList(*start, ans);
            }
            return ans;
        }
    }

    /**
     * @brief 合并两个有序链表
     *
     * @param first
     * @param second
     * @return ListNode*
     */
    ListNode* mergeTwoList(ListNode* first, ListNode* second) {
        if ((!first) || (!second))
            return first ? first : second;
        ListNode* dummy = new ListNode(0);  // 创建一个哑节点作为合并后链表的开头
        ListNode* prev = dummy;             // prev用于跟踪合并后链表的最后一个节点

        while (first != nullptr && second != nullptr) {
            if (first->val > second->val) {
                prev->next = second;
                prev = second;
                second = second->next;

            } else {
                prev->next = first;
                prev = first;
                first = first->next;
            }
        }
        if (first != nullptr) {
            prev->next = first;
        }

        if (second != nullptr) {
            prev->next = second;
        }
        return dummy->next;
    }
};