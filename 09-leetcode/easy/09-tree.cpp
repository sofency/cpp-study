/**
 * @file 09-tree.cpp
 * @author your name (you@domain.com)
 * @brief 依旧是二叉树相关的题目
 * @version 0.1
 * @date 2023-12-27
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
  /**
   * @brief 判断二叉树中是否存在根节点到叶子结点的总和为target的路径
   *
   * @param root
   * @param targetSum
   * @return true
   * @return false
   */
  bool hasPathSum(TreeNode* root, int targetSum) {
    // 如果是叶子结点且targetSum==0 返回true 如果targetSum!=0 返回false
    if (root == nullptr) {
      return false;
    };
    // 在这一步已经提前判断了 即如果root==nullptr 肯定为false
    if (root->left == nullptr && root->right == nullptr) {
      return targetSum == root->val;
    }
    // 任意一条路径满足即可
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
  }
  /**
   * @brief 反转二叉树
   *
   * @param root
   * @return TreeNode*
   */
  TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
      return;
    }
    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
  }
};