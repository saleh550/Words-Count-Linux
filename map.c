#include <stdio.h>
#include <stdlib.h>

/* A statically allocated variable */
int foo;
float bar = 3.0;

/* A recursive function */
int recur(int i, float j) {
    /* A stack allocated variable within a recursive function */
    int localInt = i;
    float localFloat = j;

    /* TODO 1: Fix this so it prints the address of localInt */
    printf("recur call %d: stack int@ %p\n", i, &localInt);
    /* TODO 2: Fix this so it prints the address of localFloat */
    printf("recur call %d: stack float@ %p\n", i, &localFloat);

    if (i > 0) {
        return recur(i - 1, j - 1.0);
    }

    return 0;
}

/* A statically allocated, pre-initialized variable */
double stuff = 7;

int main(int argc, char *argv[]) {
    /* A stack allocated variable */
    int i;

    /* Dynamically allocate some stuff */
    char *buf1 = malloc(150);
    /* ... and some more stuff */
    char *buf2 = malloc(150);

    printf("_main @ %p\n", &main);
    printf("recur @ %p\n", &recur);

    /* TODO 2: Fix to get the address of the stack variable */
    printf("_main stack: %p\n", &i);

    /* TODO 3: Fix and expand to get the address of the static variables (stuff, foo, bar) */
    printf("static data stuff: %p\n", &stuff);
   printf("static data foo: %p\n", &foo);
   printf("static data bar: %p\n", &bar);
    printf("Heap: malloc 1: %p\n", &buf1);
    printf("Heap: malloc 2: %p\n", &buf2);
    recur(3, bar);
    return 0;
}
