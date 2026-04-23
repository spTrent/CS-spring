#include "pull_minus.h"

#include <stdlib.h>
#include <string.h>

static int is_unary_minus(TreeNode* node) {
    if (node == NULL) return 0;
    return strcmp(node->value, "~") == 0;
}

static int is_mul_or_div(TreeNode* node) {
    if (node == NULL) return 0;
    return strcmp(node->value, "*") == 0 || strcmp(node->value, "/") == 0;
}

TreeNode* pull_out_minus(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    root->left = pull_out_minus(root->left);
    root->right = pull_out_minus(root->right);

    if (is_mul_or_div(root)) {
        int left_has_minus = is_unary_minus(root->left);
        int right_has_minus = is_unary_minus(root->right);

        if (left_has_minus && right_has_minus) {
            TreeNode* left_minus = root->left;
            TreeNode* right_minus = root->right;
            root->left = left_minus->left;
            root->right = right_minus->left;
            free(left_minus);
            free(right_minus);

            return root;
        } else if (left_has_minus) {
            TreeNode* minus_node = root->left;
            root->left = minus_node->left;
            minus_node->left = root;

            minus_node->left = pull_out_minus(minus_node->left);

            return minus_node;
        } else if (right_has_minus) {
            TreeNode* minus_node = root->right;
            root->right = minus_node->left;
            minus_node->left = root;

            minus_node->left = pull_out_minus(minus_node->left);

            return minus_node;
        }
    }

    if (is_unary_minus(root) && is_unary_minus(root->left)) {
        TreeNode* inner_minus = root->left;
        TreeNode* val_node = inner_minus->left;
        free(root);
        free(inner_minus);

        return val_node;
    }

    return root;
}