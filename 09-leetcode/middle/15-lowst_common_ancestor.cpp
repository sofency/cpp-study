#include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  /**
   * @brief 二叉搜索树下进行处理
   *
   * @param root
   * @param p
   * @param q
   * @return TreeNode*
   */
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ancestor = root;
    while (true) {
      if (p->val < ancestor->val && q->val < ancestor->val) {
        ancestor = ancestor->left;
      } else if (p->val > ancestor->val && q->val > ancestor->val) {
        ancestor = ancestor->right;
      } else {
        break;
      }
    }
    return ancestor;
  }

  /**
   * @brief 二叉树
   *
   * @param root
   * @param p
   * @param q
   * @return TreeNode*
   */
  TreeNode* lowestCommonBinaryAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ancestor = root;

    return ancestor;
  }
  TreeNode* ans;
  bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr)
      return false;
    bool lson = dfs(root->left, p, q);
    bool rson = dfs(root->right, p, q);
    if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) {
      ans = root;
    }
    return lson || rson || (root->val == p->val || root->val == q->val);
  }
};