#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 32

int get_precedence(const char* op) {
    if (strcmp(op, "~") == 0) return 4;
    if (strcmp(op, "^") == 0) return 3;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    return 0;
}

int is_right_associative(const char* op) {
    return strcmp(op, "~") == 0 || strcmp(op, "^") == 0;
}

void infix_to_rpn(char infix[MAX_TOKENS][MAX_TOKEN_LEN], int in_count,
                  char rpn[MAX_TOKENS][MAX_TOKEN_LEN], int* rpn_count) {

    char stack[MAX_TOKENS][MAX_TOKEN_LEN];
    int top = -1;
    *rpn_count = 0;

    for (int i = 0; i < in_count; i++) {
        char* token = infix[i];

        if (isalnum(token[0])) {
            strcpy(rpn[(*rpn_count)++], token);
        }
        else if (strcmp(token, "(") == 0) {
            strcpy(stack[++top], token);
        }
        else if (strcmp(token, ")") == 0) {
            while (top != -1 && strcmp(stack[top], "(") != 0) {
                strcpy(rpn[(*rpn_count)++], stack[top--]);
            }
            if (top != -1) top--;
        }
        else {
            while (top != -1 && strcmp(stack[top], "(") != 0) {
                int p1 = get_precedence(token);
                int p2 = get_precedence(stack[top]);

                if ((!is_right_associative(token) && p1 <= p2) ||
                    (is_right_associative(token) && p1 < p2)) {
                    strcpy(rpn[(*rpn_count)++], stack[top--]);
                } else {
                    break;
                }
            }
            strcpy(stack[++top], token);
        }
    }

    while (top != -1) {
        strcpy(rpn[(*rpn_count)++], stack[top--]);
    }
}