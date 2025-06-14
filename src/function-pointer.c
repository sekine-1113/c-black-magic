#include <stdio.h>
#define N 2

typedef void(*FUNC)(void);

void functionA(void) {
    printf("This is a functionA\n");
}

void functionB(void) {
    printf("This is a functionB\n");
}

int main(void) {
    void (*funcA)(void) = functionA;
    FUNC funcB = functionB;

    funcA();
    funcB();

    return 0;
}
