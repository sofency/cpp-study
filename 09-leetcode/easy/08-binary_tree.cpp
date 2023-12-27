/**
 * @file 08-binary_tree.cpp
 * @author your name (you@domain.com)
 * @brief 二叉树的简单算法题
 * 1. 中序遍历
 * 2. 判断两个树是否相同
 * 3. 判断是否是对称二叉树
 * 4. 二叉树的最大深度
 * @version 0.1
 * @date 2023-12-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    tree(root, result);
    return result;
  }

  void tree(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
      return;
    }
    tree(root->left, result);
    result.push_back(root->val);
    tree(root->right, result);
  }

  /**
   * @brief
   * 判断两棵树是否一样
   * @param p
   * @param q
   * @return true
   * @return false
   */
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if (q == nullptr || p == nullptr) {
      if ((p != nullptr && q == nullptr) || (p == nullptr && q != nullptr)) {
        return false;
      } else {
        return true;
      }
    } else {
      if (p->val != q->val) {
        return false;
      }
      return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
  }

  /**
   * @brief 对称二叉树
   *
   * @param root
   * @return true
   * @return false
   */
  bool isSymmetric(TreeNode* root) { return isSameSymmetricTree(root->left, root->right); }

  bool isSameSymmetricTree(TreeNode* p, TreeNode* q) {
    if (q == nullptr || p == nullptr) {
      if ((p != nullptr && q == nullptr) || (p == nullptr && q != nullptr)) {
        return false;
      } else {
        return true;
      }
    } else {
      if (p->val != q->val) {
        return false;
      }
      return isSameSymmetricTree(p->left, q->right) && isSameSymmetricTree(p->right, q->left);
    }
  }
  /**
   * @brief 二叉树的最大深度
   *
   * @param root
   * @return int
   */
  int maxDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
  }

  /**
   * @brief 有序数组转换为二叉搜索树
   *
   * @param nums
   * @return TreeNode*
   */
  TreeNode* sortedArrayToBST(vector<int>& nums) { return buildNode(nums, 0, nums.size() - 1); }
  TreeNode* buildNode(vector<int>& nums, int left, int right) {
    if (left > right) {
      return nullptr;
    }
    int middle = (left + right) / 2;
    TreeNode* root = new TreeNode();
    root->val = nums[middle];
    root->left = buildNode(nums, left, middle - 1);
    root->right = buildNode(nums, middle + 1, right);
    return root;
  }

  /**
   * @brief 是否为平衡二叉树
   *
   * @param root
   * @return true
   * @return false
   */
  bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
      return true;
    }
    // 计算每个节点的高度
    if (abs(depth(root->left) - depth(root->right)) > 1) {
      return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
  }

  int depth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    int left = depth(root->left);
    int right = depth(root->right);
    return max(left, right) + 1;
  }

  /**
   * @brief 二叉树最小深度
   * 利用队列使用广度优先遍历 进行查询 如果队列中第一个出现左右孩子都为nullptr 则返回对应的深度
   * @param root
   * @return int
   */
  int minDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    } else {
      queue<TreeNode> list;
      list.push(*root);
      int depth = 1;

      while (!list.empty()) {
        // 全部弹出 并添加下一层节点信息
        int size = list.size();
        for (int i = 0; i < size; i++) {
          TreeNode node = list.front();
          if (node.left == nullptr && node.right == nullptr) {
            return depth;
          } else {
            if (node.left != nullptr) {
              list.push(*(node.left));
            }
            if (node.right != nullptr) {
              list.push(*(node.right));
            }
          }
          list.pop();
        }
        depth++;
      }
      return depth;
    }
  }
};

int main(int argc, char const* argv[]) {
  return 0;
}
