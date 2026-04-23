#include <stdlib.h>
#include <string.h>

#include "../tree/btree.h"

int erase_node(BTreeNode* node, char* key);

int erase_from_leaf(BTreeNode* leaf, char* key) {
    for (int i = 0; i < leaf->num_keys; ++i) {
        if (strcmp(leaf->elements[i].key, key) == 0) {
            for (int j = i; j < leaf->num_keys - 1; ++j) {
                leaf->elements[j] = leaf->elements[j + 1];
            }
            leaf->num_keys--;
            return 0;
        }
    }
    return 1;
}

int merge(BTreeNode* parent, int i) {
    BTreeNode* left = parent->children[i];
    BTreeNode* right = parent->children[i + 1];

    left->elements[left->num_keys] = parent->elements[i];

    for (int j = 0; j < right->num_keys; ++j) {
        left->elements[left->num_keys + 1 + j] = right->elements[j];
    }

    if (!left->is_leaf) {
        for (int j = 0; j <= right->num_keys; ++j) {
            left->children[left->num_keys + 1 + j] = right->children[j];
        }
    }

    for (int j = i; j < parent->num_keys - 1; ++j) {
        parent->elements[j] = parent->elements[j + 1];
    }

    for (int j = i + 1; j < parent->num_keys; ++j) {
        parent->children[j] = parent->children[j + 1];
    }

    left->num_keys += right->num_keys + 1;
    parent->num_keys--;
    free(right);
    return 0;
}

int erase_from_non_leaf(BTreeNode* node, char* key) {
    int i = 0;
    while (i < node->num_keys && strcmp(key, node->elements[i].key) > 0) {
        i++;
    }

    if (i < node->num_keys && strcmp(key, node->elements[i].key) == 0) {
        BTreeNode* left = node->children[i];
        BTreeNode* right = node->children[i + 1];

        if (left->num_keys >= T) {
            BTreeNode* curr = left;
            while (!curr->is_leaf) {
                curr = curr->children[curr->num_keys];
            }
            Element pred = curr->elements[curr->num_keys - 1];
            node->elements[i] = pred;
            return erase_node(left, pred.key);
        }

        if (right->num_keys >= T) {
            BTreeNode* curr = right;
            while (!curr->is_leaf) {
                curr = curr->children[0];
            }
            Element succ = curr->elements[0];
            node->elements[i] = succ;
            return erase_node(right, succ.key);
        }

        merge(node, i);
        return erase_node(left, key);
    }
    return 1;
}

void borrow_from_prev(BTreeNode* node, int i) {
    BTreeNode* child = node->children[i];
    BTreeNode* sibling = node->children[i - 1];

    for (int j = child->num_keys - 1; j >= 0; --j) {
        child->elements[j + 1] = child->elements[j];
    }

    if (!child->is_leaf) {
        for (int j = child->num_keys; j >= 0; --j) {
            child->children[j + 1] = child->children[j];
        }
    }

    child->elements[0] = node->elements[i - 1];

    if (!child->is_leaf) {
        child->children[0] = sibling->children[sibling->num_keys];
    }

    node->elements[i - 1] = sibling->elements[sibling->num_keys - 1];

    child->num_keys++;
    sibling->num_keys--;
}

void borrow_from_next(BTreeNode* node, int i) {
    BTreeNode* child = node->children[i];
    BTreeNode* sibling = node->children[i + 1];

    child->elements[child->num_keys] = node->elements[i];

    if (!child->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
    }

    node->elements[i] = sibling->elements[0];

    for (int j = 1; j < sibling->num_keys; ++j) {
        sibling->elements[j - 1] = sibling->elements[j];
    }

    if (!sibling->is_leaf) {
        for (int j = 1; j <= sibling->num_keys; ++j) {
            sibling->children[j - 1] = sibling->children[j];
        }
    }

    child->num_keys++;
    sibling->num_keys--;
}

void fill(BTreeNode* node, int i) {
    if (i != 0 && node->children[i - 1]->num_keys >= T) {
        borrow_from_prev(node, i);
    } else if (i != node->num_keys && node->children[i + 1]->num_keys >= T) {
        borrow_from_next(node, i);
    } else {
        if (i != node->num_keys) {
            merge(node, i);
        } else {
            merge(node, i - 1);
        }
    }
}

int erase_node(BTreeNode* node, char* key) {
    int i = 0;
    while (i < node->num_keys && strcmp(key, node->elements[i].key) > 0) {
        i++;
    }

    if (i < node->num_keys && strcmp(key, node->elements[i].key) == 0) {
        if (node->is_leaf) {
            return erase_from_leaf(node, key);
        } else {
            return erase_from_non_leaf(node, key);
        }
    }

    if (node->is_leaf) {
        return 1;
    }

    int is_last_child = 0;
    if (i == node->num_keys) {
        is_last_child = 1;
    }

    if (node->children[i]->num_keys < T) {
        fill(node, i);
    }

    if (is_last_child && i > node->num_keys) {
        return erase_node(node->children[i - 1], key);
    } else {
        return erase_node(node->children[i], key);
    }
}

int erase(BTree* tree, char* key) {
    if (tree == NULL || tree->root == NULL) {
        return 1;
    }

    int result = erase_node(tree->root, key);

    if (tree->root->num_keys == 0) {
        BTreeNode* tmp = tree->root;
        if (tree->root->is_leaf) {
            tree->root = NULL;
        } else {
            tree->root = tree->root->children[0];
        }
        free(tmp);
    }

    return result;
}