#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "building.h"
#include "parse.h"
#include "pull_minus.h"
#include "to_rpn.h"
#include "tree.h"

int main() {
    char input[256];

    printf("Введите математическое выражение: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Ошибка чтения ввода.\n");
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Выражение пустое.\n");
        return 0;
    }

    char infix_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int infix_count = 0;

    char rpn_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int rpn_count = 0;

    tokenize(input, infix_tokens, &infix_count);

    infix_to_rpn(infix_tokens, infix_count, rpn_tokens, &rpn_count);

    TreeNode* root = rpn_tokens_to_tree(rpn_tokens, rpn_count);

    if (root == NULL) {
        printf("\nОшибка: Некорректное выражение (невозможно построить дерево).\n");
        return 1;
    }

    printf("\nДерево до вынесения унарных минусов:\n");
    draw_tree(root, 0);

    root = pull_out_minus(root);

    printf("\nДерево после вынесения унарных минусов:\n");
    draw_tree(root, 0);

    printf("\nИтоговое выражение:\n");
    print_infix(root);
    printf("\n");

    free_tree(root);

    return 0;
}