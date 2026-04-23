#include <stdint.h>
#include <stdlib.h>

int32_t append(int32_t* length, int32_t* capacity, int32_t** array, int32_t element) {
    if (length == NULL || capacity == NULL || array == NULL || *array == NULL) {
        return 1;
    }
    if (*length < 0 || *capacity <= 0 || *length > *capacity) {
        return 1;
    }
    if (*length < *capacity) {
        (*array)[(*length)++] = element;
        return 0;
    }
    int32_t* temp = (int32_t*)malloc(sizeof(int32_t) * *capacity * 2);
    if (temp == NULL) {
        return 1;
    }
    *capacity *= 2;
    for (int32_t i = 0; i < *length; ++i) {
        temp[i] = (*array)[i];
    }
    temp[(*length)++] = element;
    free(*array);
    *array = temp;
    return 0;
}

int32_t bubble_sort(int32_t const length, int32_t* array) {
    for (int32_t i = 0; i < length; ++i) {
        int8_t flag = 0;
        for (int32_t j = 0; j < length - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int32_t temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
    return 0;
}

int32_t binary_search(int32_t const length, int32_t* array, int32_t const element, int32_t* res) {
    if (length == 0 || array == NULL || res == NULL) {
        return 1;
    }
    int32_t left = 0;
    int32_t right = length - 1;
    while (left <= right) {
        int32_t mid = (left + right) / 2;
        if (array[mid] == element) {
            *res = mid;
            return 0;
        }
        if (element < array[mid]) {
            right = mid - 1;
        } else if (element > array[mid]) {
            left = mid + 1;
        }
    }
    *res = -1;
    return 1;
}