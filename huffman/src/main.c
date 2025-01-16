#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "tree_display.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n",argv[0]);
        exit(1);
    }

    Node *root = encode(argv[1]);
    char code[256];
    traverse_tree(0,root,code);
    int d = print_tree(0, root, code);
    printf("%d",d);
    return EXIT_SUCCESS;
}
