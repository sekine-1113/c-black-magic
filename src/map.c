#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5
#define CALC(obj, type) (sizeof(obj)/sizeof(type))

typedef int (*FUNC)(int);

int* map(int *arr, size_t len, FUNC func) {
    int *new_arr = (int*)malloc(len);

    for (int i=0; i<len; i++) {
        *(new_arr+i) = func(*(arr+i));
    }

    return new_arr;
}

int my_pow(int a) {
    return a * a;
}

int main(void) {
    int arr[N] = {0};
    for (int i=0; i<N; i++) {
        arr[i] = i+1;
    }

    for (int i=0; i<N; i++) {
        printf("%d ", arr[i]);
    }

    int *new_arr = map(arr, CALC(arr, int), my_pow);

    for (int i=0; i<N; i++) {
        printf("%d ", new_arr[i]);
    }

    return 0;
}
