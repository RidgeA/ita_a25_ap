#include <stdio.h>
#include <stdlib.h>
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

/*
 * Створює новий порожній зв'язний список
 *
 * Повертає:
 * - Вказівник на структуру linked_list
 * - NULL у випадку помилки виділення пам'яті
 *
 * Приклад використання:
 * struct linked_list* list = create_list();
 * if (list == NULL) {
 *     // обробка помилки
 * }
 */
linked_list *create_list()
{
    linked_list *list = calloc(1, sizeof(linked_list));
    if (list == NULL)
    {
        return NULL;
    }
    return list;
}

/*
 * Додає новий елемент на вказану позицію
 *
 * Параметри:
 * list: вказівник на список
 * value: значення що додається до списку
 * position: позиція для вставки (0-based)
 *
 * Особливості:
 * - Якщо position <= 0, додає на початок
 * - Якщо position >= розмір списку, додає в кінець
 *
 * Приклад:
 * // list: null
 * insert(list, 1, 0); // 1 (next:null)
 * insert(list, 2, 0); // 2 (next:1) -> 1 (next:null)
 * // list: 10 -> 20 -> 30
 * insert(list, 25, 1);    // 10 -> 25 -> 20 -> 30
 * insert(list, 5, 0);     // 5 -> 10 -> 25 -> 20 -> 30
 * insert(list, 40, 999);  // додасть в кінець: 5 -> 10 -> 25 -> 20 -> 30 -> 40
 */
void insert(linked_list *list, int data, int position)
{
    node *new_node = calloc(1, sizeof(node));
    if (new_node == NULL)
    {
        return;
    }
    new_node->data = data;

    if (list->head == NULL || position == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }

    node *current = list->head;
    int temp = 1;
    while (current->next != NULL && temp != position)
    {
        temp++;
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

/*
 * Видаляє елемент з вказаної позиції
 *
 * Параметри:
 * list: вказівник на список
 * position: позиція елемента для видалення (0-based)
 *
 * Приклад:
 * // list: 10 -> 20 -> 30 -> 40
 * del(list, 1);  // 10 -> 30 -> 40
 * del(list, 0);  // 30 -> 40
 */
void del(linked_list *list, int position)
{
    if (list->head == NULL || position < 0)
    {
        return;
    }

    if (position == 0)
    {
        node *previous_head = list->head;
        list->head = list->head->next;
        free(previous_head);
        return;
    }

    int i = 0;
    node *current = list->head;
    while (current != NULL && i < position - 1)
    {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL)
    {
        return; // Позиція поза межами списку
    }

    node *deleted_node = current->next;
    current->next = deleted_node->next;
    free(deleted_node);
}

/*
 * Шукає елемент у списку
 *
 * Параметри:
 * list: вказівник на список
 * value: значення для пошуку
 * index: вказівник на змінну, куди буде записана позиція знайденого елемента
 *
 * Повертає:
 * - true: якщо елемент знайдено
 * - false: якщо елемент не знайдено
 */
bool search(linked_list *list, int value, int *index)
{
}

/*
 * Виводить на екран всі елементи списку
 *
 * Параметри:
 * list: вказівник на список
 *
 * Формат виводу:
 * List: value1 -> value2 -> ... -> NULL
 */
void print_list(linked_list *list)
{
    if (list == NULL)
    {
        printf("NULL\n");
        return;
    }
    node *current = list->head;
    while (current != NULL)
    {

        printf("%d->", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

/*
 * Звільняє пам'ять, виділену під список
 *
 * Параметри:
 * list: вказівник на список
 */
void free_list(linked_list *list)
{

    if (list == NULL)
    {
        return;
    }
    node *current = list->head;
    while (current != NULL)
    {
        // Wrong:
        // free(current);
        // current = current->next;

        node *temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}

/*
 * Приклад використання всіх функцій зв'язного списку
 */
int main()
{
    linked_list *list = create_list();

    // insert(list, 42, 0);
    insert(list, 10, 88);
    print_list(list);
    insert(list, 20, 88);
    print_list(list);
    insert(list, 30, 88);
    print_list(list);
    insert(list, 15, 1);
    print_list(list);
    insert(list, 5, 0);
    print_list(list);

    del(list, 1);
    print_list(list);

    del(list, 0);
    print_list(list);

    del(list, 5);
    print_list(list);

    free_list(list);

    // insert(list, 4, 0);
    // insert(list, 5, 2);
    // insert(list, 6, 999);
    // delete(list, 6);
    // delete(list, 1);
    // delete(list, 0);
    return 0;
}