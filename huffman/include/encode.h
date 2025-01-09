#pragma once

typedef struct node Node;
   
// ファイルをエンコードし木のrootへのポインタを返す
Node *encode(const char *filename);
// Treeを走査して表示する
void traverse_tree(const int depth, const Node *root);

static void count_symbols(const char *filename);

static void reset_count(void)LS;

static Node *create_node(int symbol, int count, Node *left, Node *right);

static Node *pop_min(int *n, Node *nodep[]);

static Node *build_tree(void);

static void count_symbols(const char *filename);
static void reset_count(void);

static Node *create_node(int symbol, int count, Node *left, Node *right);

static Node *pop_min(int *n, Node *nodep[]);
static Node *build_tree(void);

void traverse_tree(const int depth, const Node *np);

Node *encode(const char *filename);