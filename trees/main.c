#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* init(int data);
int add_node(int data, Node** root);
int draw_tree(Node* root, int const level);
Node* remove_node(Node* root, int data);
int count_nodes(Node* root);
int count_childs(Node const* node);
void clear_tree(Node** root);

int main(void) {
    srand(time(NULL));
    Node* root = NULL;
    int operation = 0;
    int current_data = 0;
    while (1) {
        printf("Введите операцию:\n");
        printf("1. Напечатать дерево\n");
        printf("2. Добавить узел\n");
        printf("3. Удалить узел\n");
        printf("4. Посчитать количество вершин\n");
        printf("5. Закончить программу\n");
        if (scanf("%d", &operation) != 1) {
            printf("Неверный ввод");
        }
        char c;
        while (scanf("%c", &c) == 1 && c != '\n') {
        };
        if (operation == 1) {
            switch (draw_tree(root, 0)) {
                case 0:
                    printf("Ошибка отрисовки");
                    break;
                case 1:
                    break;
            }
        } else if (operation == 2) {
            printf("Введите значение нового узла:\n");
            scanf("%d", &current_data);
            add_node(current_data, &root);
        } else if (operation == 3) {
            printf("Введите значение удаляемого узла:\n");
            scanf("%d", &current_data);
            root = remove_node(root, current_data);
        } else if (operation == 4) {
            printf("Количество узлов: %d\n", count_nodes(root));
        } else if (operation == 5) {
            clear_tree(&root);
            root = NULL;
            break;
        } else {
            printf("Неверная операция\n");
        }
    }
    if (root != NULL) {
        clear_tree(&root);
    }
    return 0;
}

Node* init(int data) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int add_node(int data, Node** root) {
    if (*root == NULL) {
        Node* new_node = init(data);
        if (new_node == NULL) {
            return 0;
        }
        *root = new_node;
        return 1;
    }
    if (data > (*root)->data) {
        return add_node(data, &((*root)->right));
    } else if (data == (*root)->data) {
        return 2;
    } else {
        return add_node(data, &((*root)->left));
    }
}

int count_childs(Node const* node) {
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
            Node* min = root->right;
            while (min->left != NULL) {
                min = min->left;
            }
            root->data = min->data;
            root->right = remove_node(root->right, min->data);
        }
    }
    return root;
}

int count_nodes(Node* root) {
    return (root == NULL) ? 0 : count_childs(root->left) + count_childs(root->right);
}

int draw_tree(Node* root, int level) {
    if (root == NULL) {
        return 0;
    }
    printf("%*s", level * 4, "");
    printf("%d\n", root->data);
    draw_tree(root->left, level + 1);
    draw_tree(root->right, level + 1);
    return 1;
}

void clear_tree(Node** root) {
    if (*root == NULL) {
        return;
    }
    if ((*root)->left != NULL) {
        clear_tree(&((*root)->left));
    }
    if ((*root)->right != NULL) {
        clear_tree(&((*root)->right));
    }
    free(*root);
    *root = NULL;
}