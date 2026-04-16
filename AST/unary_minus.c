#include <ctype.h>

int is_operator_or_open_bracket(char c) {
    return c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void replace_unary_minus(const char* src, char* dest) {
    int j = 0;
    char prev_char = '\0';

    for (int i = 0; src[i] != '\0'; i++) {
        char current = src[i];

        if (isspace(current)) {
            continue;
        }

        if (current == '-') {
            if (prev_char == '\0' || is_operator_or_open_bracket(prev_char)) {
                dest[j] = '~';
            } else {
                dest[j] = '-';
            }
        }
        else {
            dest[j] = current;
        }
        prev_char = dest[j];
        j++;
    }
    dest[j] = '\0';
}
