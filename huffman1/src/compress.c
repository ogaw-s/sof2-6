#include <stdio.h>
#include "encode.h"
#include "compress.h"


void write_huffman_table(char *filename, Huffman_obj *table) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < 256; i++) {
        if (!strcmp(table[i].code,'0')){
            fwrite(&(table[i]), sizeof(Huffman_obj), 1, fp);
        }
    }
}
