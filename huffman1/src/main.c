#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "tree_display.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    int max_depth = 0;
    char codes[256][256] = {0};
    char current_code[256] = {0};

    Node *root = encode(argv[1]);
    traverse_tree(0, root, codes, current_code);

    printf("\nTree Structure:\n");
    print_tree(0, root, codes);
    return EXIT_SUCCESS;
}
