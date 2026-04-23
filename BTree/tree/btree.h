#pragma once
#define T 2

typedef struct {
    char key[7];
    double value;
} Element;

typedef struct BTreeNode {
    int num_keys;
    int is_leaf;
    struct BTreeNode* children[2 * T];
    Element elements[2 * T - 1];
} BTreeNode;

typedef struct {
    BTreeNode *root;
    int t;
} BTree;

BTree* create_tree();

void free_node(BTreeNode* node);

void free_tree(BTree* tree);

void print_node(BTreeNode* node, int level);

void print_tree(BTree* tree);
