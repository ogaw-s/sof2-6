#include <stdio.h>
#include "encode.h"
#include "compress.h"

void compress(char code[256][256], char filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int c;
    int line_count = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            line_count++; // 行末をカウント
        }
    }
}