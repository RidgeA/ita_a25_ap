#include <stdio.h>

void set42(int* v) {
    *v = 42;
}

int main(void) {
    
    int a = 5;
    int b = a + 5;

    int* pointer = &a;
    
    printf("a - %d, pa - %p\n", a, pointer);
    printf("*pa - %d\n", *pointer);

    set42(pointer);

    printf("a - %d, *pa - %d\n", a, *pointer);
    printf("sizeof(pa) - %d\n", sizeof(pointer));

    pointer = &b;
    set42(pointer);
    printf("a - %d, *pa - %d\n", a, *pointer);

    // &a - int*
    // c - float*
    float* c = (float*) &a;
    printf("float %.10f, &a - %p, c - %p\n", *c, &a, c);
    *c = 1.0;
    printf("float %.10f, &a - %p, c - %p, a - %d\n", *c, &a, c, a);


    // int array[5];
    int array[] = {1, 1, 2, 3, 5};

    printf("first array element - int[0]\n", array[3]);
    printf("&array - %p, &array[0] - %p\n", array, &array[0]);
    printf("sizeof(array)- %d\n", sizeof(array));

    int *arrayPointer = array;

    printf("array[3] - %d\n", *(arrayPointer + 3));

    printf("array[0] - %p, array[1] - %p, array[2] - %p\n", &array[0], &array[1], &array[2]);

    // ---------------------------

    int *dynamic_array = malloc(sizeof(int) * 10);
    if (dynamic_array != NULL) {
        return 1;
    }

    dynamic_array[0] = 1;

    int *dynamic_array_2 = calloc(sizeof(int) * 10);
    if (dynamic_array_2 != NULL) {
        return 1;
    }

    free(dynamic_array);
    free(dynamic_array_2);

    return 0;
}