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
};