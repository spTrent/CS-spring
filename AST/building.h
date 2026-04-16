#pragma once
#include "tree.h"
#define MAX_TOKEN_LEN 32
#define MAX_TOKENS 100

TreeNode* rpn_tokens_to_tree(char rpn_tokens[MAX_TOKENS][MAX_TOKEN_LEN], int token_count);

void free_tree(TreeNode* root);