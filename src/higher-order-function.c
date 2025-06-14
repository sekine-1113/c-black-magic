#include <stdio.h>
#define N 2

typedef void(*FUNC)(void);

void functionA(void) {
    printf("This is a functionA\n");
}

void functionB(void) {
    printf("This is a functionB\n");
}

void call(void (*func)(void)) {
    func();
}

void call2(FUNC func) {
    func();
}

int main(void) {
    FUNC func[N] = {
        functionA,
        functionB,
    };

    for (int i=0; i<N; i++) {
        printf("call: ");
        call(func[i]);
        printf("call2: ");
        call2(func[i]);
    }

    return 0;
}
