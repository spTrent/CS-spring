#include "erase/erace.h"
#include "find/find.h"
#include "insert/insert.h"
#include "tree/btree.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    if (argc > 1) {
        in = fopen(argv[1], "r");
        if (!in) {
            return 1;
        }
    }

    BTree* tree = create_tree();
    if (!tree) {
        if (in != stdin) fclose(in);
        return 1;
    }

    int op;
    char key[7];
    double value;

    while (fscanf(in, "%d", &op) == 1) {
        if (op == 1) {
            fscanf(in, "%6s %lf", key, &value);
            insert(tree, key, value);
        } else if (op == 2) {
            fscanf(in, "%6s", key);
            erase(tree, key);
        } else if (op == 3) {
            print_tree(tree);
        } else if (op == 4) {
            fscanf(in, "%6s", key);
            double res = find(tree->root, key);
            if (!isnan(res)) {
                printf("%g\n", res);
            } else {
                printf("Not found\n");
            }
        }
    }

    free_tree(tree);

    if (in != stdin) {
        fclose(in);
    }

    return 0;
}