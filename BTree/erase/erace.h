#pragma once
#include "../tree/btree.h"

int erase_from_leaf(BTreeNode* leaf, char* key);

int merge(BTreeNode* parent, int i);

int erase_from_non_leaf(BTreeNode* node, char* key);

void borrow_from_prev(BTreeNode* node, int i);

void borrow_from_next(BTreeNode* node, int i);

void fill(BTreeNode* node, int i);

int erase_node(BTreeNode* node, char* key);

int erase(BTree* tree, char* key);
