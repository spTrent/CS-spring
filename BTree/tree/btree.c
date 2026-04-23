#include "btree.h"
#include <stdlib.h>
#include <stdio.h>


BTree* create_tree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    tree->t = T;
    return tree;
}

void free_node(BTreeNode* node) {
    if (node != NULL) {
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; ++i) {
                free_node(node->children[i]);
            }
        }
        free(node);
    }
}

void free_tree(BTree* tree) {
    if (tree != NULL) {
        free_node(tree->root);
        free(tree);
    }
}

void print_node(BTreeNode* node, int level) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < level; ++i) {
        printf("    ");
    }

    printf("[");
    for (int i = 0; i < node->num_keys; ++i) {
        printf("%s", node->elements[i].key);
        if (i < node->num_keys - 1) {
            printf(" | ");
        }
    }
    printf("]\n");

    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; ++i) {
            print_node(node->children[i], level + 1);
        }
    }
}

void print_tree(BTree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    print_node(tree->root, 0);
}