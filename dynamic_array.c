#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 8;

// Динамічний масив цілих чисел
typedef struct
{
    // Кількість елементів масиву
    int size;
    // Покажчик на дані
    int *data;
    // Місткість масиву (розмір data)
    int capacity;
} dynamic_int_array;

// Створює новий масив
dynamic_int_array *new_dynamic_array()
{

    dynamic_int_array *arr = calloc(0, sizeof(dynamic_int_array));
    if (arr == NULL)
    {
        return NULL;
    }

    arr->size = 0;
    // (*arr).size = 0;

    arr->capacity = INITIAL_SIZE;

    arr->data = calloc(arr->capacity, sizeof(int));
    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

// Додає число в кінець масиву
// <1024 - double
// >1024 - +25%
int append(dynamic_int_array *arr, int value)
{
    if (arr->size == arr->capacity)
    {
        int new_capacity;
        if (arr->capacity < 1024)
        {
            new_capacity = arr->capacity * 2;
        }
        else {
            new_capacity = arr->capacity + (arr->capacity / 4);
        }

        // todo: realloc

        int *new_data = calloc(new_capacity, sizeof(int));
        if (new_data == NULL)
        {
            return arr->size;
        }
        // void* dest куди скопіювати
        // const void* src звітки скопіювати
        // std::size_t count скільки
        memcpy(new_data, arr->data, arr->size * sizeof(int));

        free(arr->data);
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size] = value;
    arr->size++;

    return arr->size;
}

// Видаляє елемент та зсуває решту вліво
// [1, 2, 3, 4, 5] => delete(3) => [1, 2, 3, 5]
int delete(dynamic_int_array *arr, int index)
{
    // todo: implement
    return 0;
}

void free_array(dynamic_int_array *arr)
{
    if (arr == NULL)
    {
        return;
    }

    if (arr->data != NULL)
    {
        free(arr->data);
    }

    free(arr);
}

// "[1 2 3 ]"
void print_array(const dynamic_int_array *arr)
{
    printf("[");
    for (int i = 0; i < arr->size; i++)
    {
        printf("%d ", arr->data[i]);
    }
    printf("]\n");
}

int main(void)
{
    dynamic_int_array *arr = new_dynamic_array();

    for (int i = 100; i < 1e5; i++)
    {
        append(arr, i);
    }
    // print_array(arr);

    // delete(arr, 3);
    // delete(arr, 3);
    // print_array(arr);
    free_array(arr);
    printf("done");
    return 0;
}