#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* init(int data);
void add_node(int data, Node** root);
void draw_tree(Node* root, int level);
Node* remove_node(Node* root, int data);
int count_nodes(Node* root);
int count_childs(Node* node);
Node* find_minimum_greater(Node* node);
void clean_tree(Node* root);

int main(void) {
    srand(time(NULL));
    Node* root = NULL;
    add_node(10, &root);
    for (int i = 0; i < 10; ++i) {
        add_node(rand() % 100 - 50, &root);
    }
    draw_tree(root, 0);
    clean_tree(root);
}

Node* init(int data) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void add_node(int data, Node** root) {
    if (*root == NULL) {
        Node* new_node = init(data);
        if (new_node == NULL) {
            return;
        }
        *root = new_node;
        return;
    }
    if (data > (*root)->data) {
        add_node(data, &((*root)->right));
    } else if (data == (*root)->data) {
        return;
    } else {
        add_node(data, &((*root)->left));
    }
}

int count_childs(Node* node) {
    int res = 0;
    res += node->left != NULL;
    res += node->right != NULL;
    return res;
}

Node* remove_node(Node* root, int data) {
    if (root == NULL) return NULL;

    if (data < root->data) {
        root->left = remove_node(root->left, data);
    } else if (data > root->data) {
        root->right = remove_node(root->right, data);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* min = find_minimum_greater(root->right);
            root->data = min->data;
            root->right = remove_node(root->right, min->data);
        }
    }
    return root;
}

Node* find_minimum_greater(Node* node) {
    if (node->left == NULL) {
        return node;
    } else {
        return find_minimum_greater(node->left);
    }
}

int count_nodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int res = 1;
    res += count_nodes(root->left) + count_nodes(root->right);
    return res;
}

void draw_tree(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    printf("%*s", level * 4, "");
    printf("%d\n", root->data);
    draw_tree(root->left, level + 1);
    draw_tree(root->right, level + 1);
}

void clean_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        clean_tree(root->left);
    }
    if (root->right != NULL) {
        clean_tree(root->right);
    }
    free(root);
}