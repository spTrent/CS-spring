#include <stdlib.h>
#include <string.h>

#include "../tree/btree.h"

int split_children(BTreeNode* parent, int i, BTreeNode* full_child) {
    BTreeNode* new_child = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (new_child == NULL) {
        return 1;
    }
    new_child->is_leaf = full_child->is_leaf;
    new_child->num_keys = T - 1;
    for (int j = 0; j < T - 1; ++j) {
        new_child->elements[j] = full_child->elements[j + T];
    }
    if (!full_child->is_leaf) {
        for (int j = 0; j < T; ++j) {
            new_child->children[j] = full_child->children[j + T];
        }
    }
    full_child->num_keys = T - 1;
    for (int j = parent->num_keys; j >= i + 1; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = new_child;
    for (int j = parent->num_keys - 1; j >= i; --j) {
        parent->elements[j + 1] = parent->elements[j];
    }
    parent->elements[i] = full_child->elements[T - 1];
    parent->num_keys++;
    return 0;
}

int insert_in_not_full(BTreeNode* node, Element element) {
    if (node == NULL) {
        return 1;
    }

    for (int j = 0; j < node->num_keys; ++j) {
        if (strcmp(element.key, node->elements[j].key) == 0) {
            node->elements[j].value = element.value;
            return 0;
        }
    }

    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && strcmp(element.key, node->elements[i].key) < 0) {
            node->elements[i + 1] = node->elements[i];
            i--;
        }

        node->elements[i + 1] = element;
        node->num_keys++;
        return 0;
    } else {
        while (i >= 0 && strcmp(element.key, node->elements[i].key) < 0) {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == 2 * T - 1) {
            if (split_children(node, i, node->children[i])) {
                return 1;
            }

            if (strcmp(element.key, node->elements[i].key) > 0) {
                i++;
            }
        }

        return insert_in_not_full(node->children[i], element);
    }
}

int insert(BTree* tree, const char* const key, double const value) {
    if (tree == NULL) return 1;
    Element element;
    strncpy(element.key, key, 6);
    element.key[6] = '\0';
    element.value = value;
    if (tree->root == NULL) {
        BTreeNode* root = (BTreeNode*)malloc(sizeof(BTreeNode));
        if (root == NULL) {
            return 1;
        }
        root->elements[0] = element;
        root->num_keys = 1;
        root->is_leaf = 1;
        tree->root = root;
        return 0;
    }

    if (tree->root->num_keys == 2 * T - 1) {
        BTreeNode* new_root = (BTreeNode*)malloc(sizeof(BTreeNode));
        if (new_root == NULL) {
            return 1;
        }

        new_root->is_leaf = 0;
        new_root->num_keys = 0;
        new_root->children[0] = tree->root;

        split_children(new_root, 0, tree->root);
        tree->root = new_root;

        return insert_in_not_full(new_root, element);
    }

    return insert_in_not_full(tree->root, element);
}
