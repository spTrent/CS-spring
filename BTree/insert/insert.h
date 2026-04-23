#pragma once
#include "../tree/btree.h"

int split_children(BTreeNode* parent, int i, BTreeNode* full_child);

int insert_in_not_full(BTreeNode* node, Element element);

int insert(BTree* tree, const char* const key, double const value);
