#pragma once
#include "compress.h"
typedef struct node Node;
   
// ファイルをエンコードし木のrootへのポインタを返す
Node *encode(const char *filename);

// 構造体定義
struct node{
    int symbol;
    int count;
    Node *left;
    Node *right;
};

// Treeを走査して表示する
void traverse_tree(const int depth, const Node *np, Huffman_obj *table, unsigned char *current_code);