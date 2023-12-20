#include <iostream>
using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
  vector<int> twoSum(vector<int> &nums, int target)
  {
    // 获取长度
    int length = nums.size();
    for (int i = 0; i < length; i++)
    {
      vector<int>::iterator it = find(nums.begin(), nums.end(), (target - nums[i]));
      if (it != nums.end())
      {
        int index = distance(nums.begin(), it);
        if (index != i)
        {
          return vector<int>{i, index};
        }
      }
    }
    return vector<int>{};
  }

  /**
   * @brief 两数之和 hash
   *
   * @param nums
   * @param target
   * @return vector<int>
   */
  vector<int> twoSumByHash(vector<int> &nums, int target)
  {
    // 获取长度
    int length = nums.size();
    unordered_map<int, int> keymap;
    for (int i = 0; i < length; i++)
    {
      auto it = keymap.find((target - nums.at(i)));
      if (it != keymap.end())
      {
        return vector<int>{it->second, i};
      }
      keymap[nums[i]] = i;
    }
    return vector<int>{};
  }

  /**
   * @brief 两数相加
   * 内存的释放则需要借助智能指针来做
   * @param l1
   * @param l2
   * @return ListNode*
   */
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
  {
    // 进位位
    int temp = 0;
    ListNode *result = new ListNode(0, nullptr);
    ListNode *head = result;
    while (l1 != nullptr && l2 != nullptr)
    {
      ListNode *node = new ListNode();
      int sum = l1->val + l2->val + temp;
      node->val = sum % 10;
      temp = sum / 10;
      head->next = node;
      head = node;

      l1 = l1->next;
      l2 = l2->next;
    }

    while (l1 != nullptr)
    {
      ListNode *node = new ListNode();
      int sum = l1->val + temp;
      node->val = sum % 10;
      temp = sum / 10;
      head->next = node;
      head = node;

      l1 = l1->next;
    }

    while (l2 != nullptr)
    {
      ListNode *node = new ListNode();
      int sum = l2->val + temp;
      node->val = sum % 10;
      temp = sum / 10;
      head->next = node;
      head = node;

      l2 = l2->next;
    }
    if (temp != 0)
    {
      ListNode *node = new ListNode();
      node->val = temp;
      head->next = node;
      head = node;
    }
    return result->next;
  }
};

int main(int argc, char const *argv[])
{
  Solution solution;
  return 0;
}
