#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

// Структура що описує окремий вузол зв'язаного списку
typedef struct node
{
    // Дані, що зберігаються у зв'язному списку
    int data;

    // Покажчик на "наступний" вузол
    struct node *next;
} node;

// Структура, що описує власне зв'язний список
typedef struct
{
    // Покажчик на перший вузол зв'язного списку
    node *head;
} linked_list;

// Function declarations
linked_list *create_list(void);
void insert(linked_list *list, int data, int position);
void del(linked_list *list, int position);
bool search(linked_list *list, int value, int *index);
void print_list(linked_list *list);
void free_list(linked_list *list);

#endif // LINKED_LIST_H