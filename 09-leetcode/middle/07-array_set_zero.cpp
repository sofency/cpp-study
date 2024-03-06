#include <iostream>
#include <map>
#include <unordered_set>
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
  ListNode* detectCycle(ListNode* head) {
    if (head == NULL) {
      return NULL;
    } else {
      unordered_set<ListNode*> list;
      while (head != nullptr) {
        if (list.count(head)) {
          return head;
        } else {
          list.insert(head);
          head = head->next;
        }
      }
      return nullptr;
    }
  }
  /**
   * @brief Set the Zeroes object
   * 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。
   * 借助hash表操作
   * @param matrix
   */
  void setZeroes(vector<vector<int>>& matrix) {
    int height = matrix.size();
    if (height == 0) {
      return;
    }
    int width = matrix[0].size();
    map<int, int> hash;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (matrix[i][j] == 0 && (hash[j + i * width] == 0)) {
          // 行
          for (int k = 0; k < width; k++) {
            bool flag = matrix[i][k] == 0;
            if (!flag) {
              matrix[i][k] = 0;
              hash[k + i * width] = 1;
            }
          }
          // 列
          for (int k = 0; k < height; k++) {
            bool flag = matrix[k][j] == 0;
            if (!flag) {
              matrix[k][j] = 0;
              hash[j + k * width] = 1;
            }
          }
        }
      }
    }
  }
};