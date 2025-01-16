#include <stdio.h>
#include <stdlib.h>
#include "encode.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n",argv[0]);
        exit(1);
    }

    //symbol_count[NSYMBOL] がある

    Node *root = encode(argv[1]);
    char code[256];
    traverse_tree(0,root,code);
    
    return EXIT_SUCCESS;
}
