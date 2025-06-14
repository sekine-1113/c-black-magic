#include <stdio.h>
#define TOSTR(x) #x
#define CONCAT(x,y) x##y
#define print_string(value) printf("%s\n", value)
#define print(type, value) CONCAT(print_, type)(value)

int main(void) {
    char* string001 = "Hello, World!";
    printf("%s\n", TOSTR(token));
    printf("%s\n", CONCAT(string, 001));
    print(string, "This is string.");
    return 0;
}
