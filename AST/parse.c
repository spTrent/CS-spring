#include "parse.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(const char* expr, char tokens[MAX_TOKENS][MAX_TOKEN_LEN], int* token_count) {
    *token_count = 0;
    int i = 0;
    char prev_char = '\0';

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isalnum(expr[i])) {
            int j = 0;
            while (isalnum(expr[i])) {
                tokens[*token_count][j++] = expr[i++];
            }
            tokens[*token_count][j] = '\0';

            prev_char = tokens[*token_count][j - 1];
            (*token_count)++;
        } else {
            char op = expr[i];
            if (op == '-') {
                if (prev_char == '\0' || strchr("(+-*/^", prev_char) != NULL) {
                    op = '~';
                }
            }

            tokens[*token_count][0] = op;
            tokens[*token_count][1] = '\0';
            (*token_count)++;

            prev_char = op;
            i++;
        }
    }
}
