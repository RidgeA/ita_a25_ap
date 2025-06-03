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
 * index: позиція для вставки (0-based)
 *
 * Особливості:
 * - Якщо index <= 0, додає на початок
 * - Якщо index >= розмір списку, додає в кінець
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
void insert(linked_list *list, int data, int index)
{
    node *new_node = calloc(1, sizeof(node));
    if (new_node == NULL)
    {
        return;
    }
    new_node->data = data;

    if (list->head==NULL){
        list->head=new_node;
        return;
    }
    node* current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    } 
    current->next = new_node;
}

/*
 * Видаляє елемент з вказаної позиції
 *
 * Параметри:
 * list: вказівник на список
 * index: позиція елемента для видалення (0-based)
 *
 * Приклад:
 * // list: 10 -> 20 -> 30 -> 40
 * delete(list, 1);  // 10 -> 30 -> 40
 * delete(list, 0);  // 30 -> 40
 */
void delete(linked_list *list, int index)
{
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
    if (list == NULL || list->head == NULL)
    {
        printf("NULL\n");
        return;
    }

    printf("%d", list->head->data);

    printf("\n");
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
    free(list);
}

/*
 * Приклад використання всіх функцій зв'язного списку
 */
int main()
{
    linked_list *list = create_list();

    // insert(list, 42, 0);
    insert(list, 1, 0);
    insert(list, 2, 0);
    insert(list, 3, 0);
    // insert(list, 4, 0);
    // insert(list, 5, 2);
    // insert(list, 6, 999);
    // delete(list, 6);
    // delete(list, 1);
    // delete(list, 0);
    print_list(list);
    free_list(list);
    return 0;
}