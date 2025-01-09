#include <stdio.h>

void foo(void);
extern int x;

int main() {
    foo();
    printf("%d\n", x);
    return 0;
}
