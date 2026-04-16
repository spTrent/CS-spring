#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TreeNode* create_node(const char* val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->value, val);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int draw_tree(TreeNode* root, int level) {
    if (root == NULL) {
        return 0;
    }
    printf("%*s", level * 4, "");
    printf("%s\n", root->value);
    draw_tree(root->left, level + 1);
    draw_tree(root->right, level + 1);
    return 1;
}

void print_infix(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    int is_leaf = (root->left == NULL && root->right == NULL);
    int is_unary = (strcmp(root->value, "~") == 0);


    if (is_leaf == 1) {
        printf("%s", root->value);
        return;
    }

    if (is_unary == 1) {
        printf("(-");
        print_infix(root->left);
        printf(")");
        return;
    }
    printf("(");
    print_infix(root->left);
    printf(" %s ", root->value);
    print_infix(root->right);
    printf(")");
}
