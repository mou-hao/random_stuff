#include <iostream>
#include <vector>

#include "util.h"

void iter_inorder(TreeNode* root) {
  std::vector<TreeNode*> st;
  TreeNode* cur = root;

  while (cur || st.size()) {
    while (cur) {
      st.push_back(cur);
      cur = cur->left;
    }

    root = st.back();
    st.pop_back();
    std::cout << root->val << ' ';
    cur = root->right;
  }

  std::cout << '\n';
}

void iter_preorder(TreeNode* root) {
  std::vector<TreeNode*> st;
  st.push_back(root);

  while (st.size()) {
    root = st.back();
    st.pop_back();
    if (!root) continue;

    std::cout << root->val << ' ';
    st.push_back(root->right);
    st.push_back(root->left);
  }

  std::cout << '\n';
}

void iter_postorder(TreeNode* root) {
  if (!root) return;

  std::vector<TreeNode*> left_st;
  std::vector<TreeNode*> st;
  left_st.push_back(root);

  while (left_st.size()) {
    root = left_st.back();
    left_st.pop_back();
    st.push_back(root);
    if (root->left) {
      left_st.push_back(root->left);
    }
    if (root->right) {
      left_st.push_back(root->right);
    }
  }

  while (st.size()) {
    root = st.back();
    st.pop_back();
    std::cout << root->val << ' ';
  }

  std::cout << '\n';
}

void morris_inorder(TreeNode* root) {
  TreeNode* cur = root;
  TreeNode* tmp;
  while (cur) {
    if (!cur->left) {
      std::cout << cur->val << ' ';
      cur = cur->right;
    } else {
      tmp = cur->left;
      while (tmp) {
        if (!tmp->right || tmp->right == cur) {
          break;
        }
        tmp = tmp->right;
      }
      if (!tmp->right) {
        tmp->right = cur;
        cur = cur->left;
        continue;
      }
      if (tmp->right == cur) {
        tmp->right = nullptr;
        std::cout << cur->val << ' ';
        cur = cur->right;
        continue;
      }
    }
  }
  std::cout << '\n';
}

void morris_preorder(TreeNode* root) {
  TreeNode* cur = root;
  TreeNode* tmp;
  while (cur) {
    if (!cur->left) {
      std::cout << cur->val << ' ';
      cur = cur->right;
    } else {
      tmp = cur->left;
      while (tmp) {
        if (!tmp->right || tmp->right == cur) {
          break;
        }
        tmp = tmp->right;
      }
      if (!tmp->right) {
        tmp->right = cur;
        std::cout << cur->val << ' ';
        cur = cur->left;
        continue;
      }
      if (tmp->right == cur) {
        tmp->right = nullptr;
        cur = cur->right;
        continue;
      }
    }
  }
  std::cout << '\n';
}

int main() {
  /*       0
   *    1     2
   *  3     4   5
   *             6
   */
  std::vector<int> tree =
    {0, 1, 2, 3, -1, 4, 5, -1, -1, -1, -1, -1, -1, -1, 6};
  TreeNode* root = build_tree(tree);

  std::cout << "Iterative inorder:\n";
  iter_inorder(root);

  std::cout << "Iterative preorder:\n";
  iter_preorder(root);

  std::cout << "Iterative postorder:\n";
  iter_postorder(root);

  std::cout << "Morris inorder:\n";
  morris_inorder(root);

  std::cout << "Morris preorder:\n";
  morris_preorder(root);

  delete_tree(root);
  return 0;
}
