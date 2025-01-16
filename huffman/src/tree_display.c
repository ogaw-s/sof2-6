#include <stdio.h>
#include "encode.h"
#include "tree_display.h"

int print_tree(const int depth, const Node *node, char *code) {
    if (node == NULL) return -1;
    //printf("a %d\n",depth);
    if (node->left == NULL && node->right == NULL) {
        for (int i = 0; i < depth-1; i++) {
            printf("    ");
        }
        printf("+----");
        printf("symbol: %c, codeword: %s\n", (char)node->symbol, code);
        return depth;
    }
    //printf("b %d\n",depth);

    int left_depth = print_tree(depth + 1, node->left, code);
    int right_depth = print_tree(depth + 1, node->right, code);

    if (left_depth > right_depth) {
        code[depth] = '0';
        return left_depth;
    }else {
        code[depth] = '1';
        
        return right_depth;
    }
}

