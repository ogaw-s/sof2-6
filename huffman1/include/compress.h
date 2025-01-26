#pragma once

typedef struct huffmanobj{
    int symbol;
    int code_length;
    char code[256];
} Huffman_obj;

void write_huffman_table(char *filename, Huffman_obj *table);

void compress(char *filename_input, char *filename_output, Huffman_obj *table);
