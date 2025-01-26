#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "compress.h"

void write_huffman_table(char *filename, Huffman_obj *table) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    
    char buffer[256];
    char buffer_stream[9];
    unsigned int bin;
    for (int i = 0; i < 256; i++) {
        fwrite(&(table[i].symbol), 1, 1, fp);
        fwrite(&(table[i].code_length), sizeof(int), 1, fp);

        if (table[i].code_length > 8) {
            while (strlen(buffer) >= 8) {
                memcpy(buffer, table[i].code, sizeof(buffer));
                strncpy(buffer_stream, buffer, 8);
                buffer_stream[8] = '\0';
                bin = (unsigned int) strtol(buffer_stream, NULL, 2);
                fwrite(&bin, 1, 1, fp);
                memmove(buffer, buffer + 8, strlen(buffer) - 7);
            }
        }else {
            bin = (unsigned int) strtol(table[i].code, NULL, 2);
            fwrite(&bin, 1, 1, fp);
        }
    }
    fclose(fp);
}

void compress(char *filename_input, char *filename_output, Huffman_obj *table) {
    FILE *fp_input = fopen(filename_input, "r");
    FILE *fp_output = fopen(filename_output, "a");

    char buffer[64] = "\0";
    char buffer_stream[9];
    unsigned int bin;

    if (fp_input == NULL || fp_output == NULL) {
        perror("Failed to open file");
        return;
    }

    int c = fgetc(fp_input);
    while (c != EOF) {
        strcat(buffer, table[c].code);

        while (strlen(buffer) >= 8) {
            strncpy(buffer_stream, buffer, 8);
            buffer_stream[8] = '\0';

            bin = (unsigned int) strtol(buffer_stream, NULL, 2);

            fwrite(&bin, 1, 1, fp_output);

            memmove(buffer, buffer + 8, strlen(buffer) - 7);
        }
        c = fgetc(fp_input);
    }

    if (strlen(buffer) != 0) {
        for (int i = strlen(buffer); i < 9; i++) {
            buffer[i] = '0';
        }
        buffer[8] = '\0';
        bin = (unsigned int) strtol(buffer, NULL, 2);
        fwrite(&bin, 1, 1, fp_output);
    }

    fclose(fp_input);
    fclose(fp_output);
}
