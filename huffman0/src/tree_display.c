#include <stdio.h>
#include "encode.h"
#include "tree_display.h"

#include <stdio.h>
#include "encode.h"
#include "tree_display.h"

void print_tree(const int depth, const Node *node, char codes[256][256]) {
    if (node == NULL) return;

    // 葉ノード（シンボルを持つ）
    if (node->left == NULL && node->right == NULL) {
        if (depth)
        for (int i = 0; i < depth - 2; i++) {
            printf("    ");
        }
        printf("+----");
        // シンボルの表示（改行文字を特別扱い）
        if (node->symbol == 10) {
            printf("\\n:%s\n", codes[node->symbol]);
        } else {
            printf("%c:%s, d=%d\n", (char)node->symbol, codes[node->symbol],depth);
        }
        return;
    }
    

    // 再帰的に子ノードを処理
    
    print_tree(depth + 1, node->right, codes);
    print_tree(depth + 1, node->left, codes);
}
