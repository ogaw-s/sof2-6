#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "compress.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    unsigned char current_code[256] = {0};
    Huffman_obj huffman_table[256];
    
    for (int i = 0; i < 256; i++) {
        huffman_table[i].symbol = i;
        huffman_table[i].code_length = 0;
        huffman_table[i].code[0] = '0';
    }
    Node *root = encode(argv[1]);
    traverse_tree(0, root, huffman_table, current_code);
    for (int i = 0; i < 256; i++) {
        printf("%c:%s\n", huffman_table[i].symbol, huffman_table[i].code);
    }
    return EXIT_SUCCESS;
}
