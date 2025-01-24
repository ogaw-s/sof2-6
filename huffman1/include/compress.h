#pragma once

typedef struct huffmanobj{
    unsigned char symbol;
    int code_length;
    unsigned char code[256];
} Huffman_obj;

void write_huffman_table(char *filename, Huffman_obj *table);

void compress(char *filename, Huffman_obj *table);
