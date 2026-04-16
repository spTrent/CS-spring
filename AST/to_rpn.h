#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 32

int get_precedence(const char* op);

int is_right_associative(const char* op);

void infix_to_rpn(char infix[MAX_TOKENS][MAX_TOKEN_LEN], int in_count,
                  char rpn[MAX_TOKENS][MAX_TOKEN_LEN], int* rpn_count);