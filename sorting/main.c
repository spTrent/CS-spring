#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_matrix.h"

int32_t main() {
    int32_t* array = (int32_t*)malloc(sizeof(int32_t) * 11);
    int32_t length = 0;
    int32_t capacity = 11;
    int32_t curr;

    while (scanf("%d", &curr) != EOF) {
        append(&length, &capacity, &array, curr);
    }

    for (int32_t i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    bubble_sort(length, array);
    for (int32_t i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    freopen("/dev/tty", "r", stdin);

    printf("Введите число для поиска: ");
    int32_t res = -1;
    int32_t input = 0;
    if (scanf("%d", &input) != 1) {
        return 1;
    }
    if (binary_search(length, array, input, &res) == 1) {
        return 1;
    }
    printf("Элемент %d на позиции %d\n", input, res);

    free(array);
    return 0;
}
