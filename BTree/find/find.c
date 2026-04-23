#include "find.h"

#include <math.h>
#include <string.h>

#include "../tree/btree.h"

double find(BTreeNode* node, char* key) {
    if (node == NULL) {
        return NAN;
    }

    int i = 0;
    while (i < node->num_keys && strcmp(key, node->elements[i].key) > 0) {
        i++;
    }
    if (i < node->num_keys && strcmp(key, node->elements[i].key) == 0) {
        return node->elements[i].value;
    }
    if (node->is_leaf) {
        return NAN;
    }
    return find(node->children[i], key);
}
