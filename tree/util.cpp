#include "util.h"

void delete_tree(TreeNode* root) {
  if (!root) return;
  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
}

TreeNode* recur_build(const std::vector<int>& tree, std::size_t pos) {
  if (pos >= tree.size() || tree[pos] == -1) return nullptr;

  TreeNode* node = new TreeNode(tree[pos]);
  node->left = recur_build(tree, pos * 2 + 1);
  node->right = recur_build(tree, pos * 2 + 2);

  return node;
}

TreeNode* build_tree(const std::vector<int>& tree) {
  return recur_build(tree, 0);
}

void recur_collapse(TreeNode* node, std::vector<int>& tree, std::size_t pos) {
  if (!node) return;

  if (pos >= tree.size()) tree.resize(pos + 1, -1);
  tree[pos] = node->val;
  recur_collapse(node->left, tree, pos * 2 + 1);
  recur_collapse(node->right, tree, pos * 2 + 2);
}

std::vector<int> collapse_tree(TreeNode* root) {
  std::vector<int> repr;
  recur_collapse(root, repr, 0);
  return repr;
}
