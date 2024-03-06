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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildOneNode(preorder, 0, preorder.size() - 1, 0, preorder.size() - 1);
  }

  /**
   * @brief 无重复元素
   *
   * @param preorder
   * @param k
   * @param inorder
   * @param left
   * @param right
   * @return TreeNode*
   */
  TreeNode* buildOneNode(vector<int>& preorder,
                         int pre_left,
                         int pre_right,
                         vector<int>& inorder,
                         int in_left,
                         int in_right) {
    if (pre_left > pre_right) {
      return nullptr;
    }
    // 当前首节点元素
    int data = preorder[pre_left];
    // 创建根节点
    TreeNode* root = new TreeNode(data);

    vector<int>::iterator res = find(inorder.begin(), inorder.end(), data);
    if (res != inorder.end()) {
      // 获取索引位置
      int index = distance(inorder.begin(), res);
      int num_left = index - in_left;
      root->left = buildOneNode(preorder, pre_left + 1, pre_left + num_left, inorder, in_left, index - 1);
      root->right = buildOneNode(preorder, pre_left + num_left + 1, pre_right, inorder, index + 1, in_right);
    }
    return root;
  }
};