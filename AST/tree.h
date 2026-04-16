#pragma once
#define MAX_TOKEN_LEN 32

typedef struct TreeNode {
    char value[MAX_TOKEN_LEN];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(const char* val);

int draw_tree(TreeNode* root, int level);

void print_infix(TreeNode* root);
