#include <stdio.h>


int main() {
    int x = 10;
    int* p = &x;
    *p = 20;

    printf("Valor de x : %d\n", x);
    printf("Endereço de x: %p\n", &x);
    printf("Conteúdo de p (o endereço): %p\n", p);
    printf("Valor apontado por p: %d\n", *p);

    return 0;
}
