#include <iostream>
#include <vector>

#include "util.h"

void diag_traverse(TreeNode* root) {
  if (!root) return;

  std::vector<TreeNode*> this_row;
  std::vector<TreeNode*> next_row;
  this_row.push_back(root);

  while (this_row.size()) {
    next_row.clear();
    for (TreeNode* node : this_row) {
      while (node) {
        std::cout << node->val << ' ';
        if (node->left) {
          next_row.push_back(node->left);
        }
        node = node->right;
      }
    }
    std::cout << '\n';
    std::swap(this_row, next_row);
  }
}

int main() {
  /*       0
   *    1     2
   *  3     4   5
   *         6 7 8
   */
  std::vector<int> tree =
    {0, 1, 2, 3, -1, 4, 5, -1, -1, -1, -1, -1, 6, 7, 8};
  TreeNode* root = build_tree(tree);

  diag_traverse(root);

  delete_tree(root);
  return 0;
}
