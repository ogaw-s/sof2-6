#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "encode.h"


#define NSYMBOLS 256
#define MAX_LEN 256
static int symbol_count[NSYMBOLS];

// 以下このソースで有効なstatic関数のプロトタイプ宣言

// ファイルを読み込み、static配列の値を更新する関数
static void count_symbols(const char *filename);

// symbol_count をリセットする関数
static void reset_count(void);

// 与えられた引数でNode構造体を作成し、そのアドレスを返す関数
static Node *create_node(int symbol, int count, Node *left, Node *right);

// Node構造体へのポインタが並んだ配列から、最小カウントを持つ構造体をポップしてくる関数
// n は 配列の実効的な長さを格納する変数を指している（popするたびに更新される）
static Node *pop_min(int *n, Node *nodep[]);

// ハフマン木を構成する関数
static Node *build_tree(void);


// 以下 static関数の実装
static void count_symbols(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open %s\n", filename);
        exit(1);
    }
    int c;
    while( ( c = fgetc(fp)) != EOF ){
        symbol_count[c]++;
    }

    fclose(fp);
}

static void reset_count(void) {
    for (int i = 0 ; i < NSYMBOLS ; i++) symbol_count[i] = 0;
}

static Node *create_node(int symbol, int count, Node *left, Node *right) {
    Node *ret = (Node *)malloc(sizeof(Node));
    *ret = (Node){ .symbol = symbol, .count = count, .left = left, .right = right};
    return ret;
}

static Node *pop_min(int *n, Node *nodep[]) {
    // Find the node with the smallest count
    // カウントが最小のノードを見つけてくる
    int argmin = 0;
    for (int i = 0; i < *n; i++) {
        if (nodep[i]->count < nodep[argmin]->count) {
            argmin = i;
        }
    }
    
    Node *node_min = nodep[argmin];
    
    // Remove the node pointer from nodep[]
    // 見つかったノード以降の配列を前につめていく
    for (int i = argmin; i < (*n) - 1; i++) {
        nodep[i] = nodep[i + 1];
    }
    // 合計ノード数を一つ減らす
    (*n)--;
    
    return node_min;
}

static Node *build_tree(void) {
    int n = 0;
    Node *nodep[NSYMBOLS];
    
    for (int i = 0; i < NSYMBOLS; i++) {
        // カウントの存在しなかったシンボルには何もしない
        if (symbol_count[i] == 0) continue;
        nodep[n++] = create_node(i, symbol_count[i], NULL, NULL);
    }

    const int dummy = -1; // ダミー用のsymbol を用意しておく
    while (n >= 2) {
        Node *node1 = pop_min(&n, nodep);
        Node *node2 = pop_min(&n, nodep);

        // Create a new node
        // pop_min によりnはnodep終端を変更しているので、終端に突っ込んで一つ増やす
        nodep[n++] = create_node(dummy, node1->count + node2->count, node1, node2);
    }
    // なぜ以下のコードで木を返したことになるか少し考えてみよう
    return (n==0)?NULL:nodep[0];
}

// Perform depth-first traversal of the tree
// 深さ優先で木を走査する
// 現状は何もしていない（再帰してたどっているだけ）
void traverse_tree(const int depth, const Node *np, char codes[256][256], char *current_code) {			  
    if (np == NULL) return;
    // 葉ノード（シンボルを持つ）で処理
    if (np->left == NULL && np->right == NULL) {
        current_code[depth] = '\0'; // 符号語を終了
        strcpy(codes[np->symbol], current_code); // 符号語をcodes配列に保存

        // シンボルの表示（改行文字を特別扱い）
        if (np->symbol == 10) {
            printf("symbol: \\n, codeword: %s\n", current_code);
        } else {
            printf("symbol: %c, codeword: %s\n", (char)np->symbol, current_code);
        }
        
        return;
    }

    // 左の子ノードに進む
    current_code[depth] = '0';
    traverse_tree(depth + 1, np->left, codes, current_code);

    // 右の子ノードに進む
    current_code[depth] = '1';
    traverse_tree(depth + 1, np->right, codes, current_code);
}


// この関数は外部 (main) で使用される (staticがついていない)
Node *encode(const char *filename) {
    reset_count();
    count_symbols(filename);
    Node *root = build_tree();
    
    if (root == NULL){
        fprintf(stderr,"A tree has not been constructed.\n");
    }

    return root;
}
