#include "building.h"

#include <stdlib.h>
#include <string.h>

TreeNode* rpn_tokens_to_tree(char rpn_tokens[MAX_TOKENS][MAX_TOKEN_LEN], int token_count) {
    TreeNode* stack[256];
    int top = -1;

    for (int i = 0; i < token_count; i++) {
        char* token = rpn_tokens[i];
        if (strlen(token) == 1 && strchr("+-*/^~", token[0]) != NULL) {
            TreeNode* opNode = create_node(token);

            if (token[0] == '~') {
                opNode->left = stack[top--];
            } else {
                TreeNode* rightChild = stack[top--];
                TreeNode* leftChild = stack[top--];
                opNode->right = rightChild;
                opNode->left = leftChild;
            }
            stack[++top] = opNode;
        } else {
            stack[++top] = create_node(token);
        }
    }
    return stack[top];
}

void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}