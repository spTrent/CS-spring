#pragma once
#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 32
#include "tree.h"

void tokenize(const char* expr, char tokens[MAX_TOKENS][MAX_TOKEN_LEN], int* token_count);
