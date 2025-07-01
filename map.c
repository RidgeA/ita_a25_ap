#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Проста хеш-функція, яка обчислює суму ASCII-кодів символів
int simple_hash(char *input, int n) {
    int sum = 0;

    // Підсумовуємо всі байти рядка
    for (int i = 0; input[i] != '\0'; i++ ) {
        sum += (unsigned char)input[i];
    }

    // Повертаємо остачу від ділення на розмір таблиці
    return sum % n;
}

// Структура для зберігання пари ключ-значення
typedef struct item {
    char* key;      // Ключ (рядок)
    int value;      // Значення (ціле число)
} item;

// Структура для представлення кошика (bucket) в хеш-таблиці
typedef struct bucket {
    int len;        // поточний розмір
    int size;       // максимальний pозмір кошика
    item* items;    // Масив елементів у кошику
} bucket;

// Структура хеш-карти
typedef struct hash_map {
    bucket* buckets;    // Масив кошиків
} hash_map;

// Функція для створення нової хеш-карти
hash_map* create_hashmap() {
    // Виділяємо пам'ять для структури хеш-карти
    hash_map * hm = calloc(1, sizeof(hash_map));
    if (hm == NULL) {  // Перевіряємо чи виділення пам'яті пройшло успішно
        return NULL;
    }

    // Виділяємо пам'ять для масиву кошиків
    hm->buckets = calloc(TABLE_SIZE, sizeof(bucket));
    if (hm->buckets == NULL) {  // Перевіряємо чи виділення пам'яті пройшло успішно
        free(hm);
        return NULL;
    }

    // Ініціалізуємо кожен кошик
    for (int i = 0; i < TABLE_SIZE; i++) {
        hm->buckets[i].len = 0;
        hm->buckets[i].size = 10;   // Встановлюємо розмір кошика
        hm->buckets[i].items = calloc(hm->buckets[i].size, sizeof(item));
        if (hm->buckets[i].items == NULL) {  // Перевіряємо виділення пам'яті
            // Очищуємо попередньо виділені кошики у випадку помилки
            for (int j = 0; j < i; j++) {
                free(hm->buckets[j].items);
            }
            free(hm->buckets);
            free(hm);
            return NULL;
        }
    }

    return hm;
}

// Функція для додавання або оновлення пари ключ-значення
void put(hash_map* map, char* key, int value) {
    int hash = simple_hash(key, TABLE_SIZE);

    bucket* cur_bucket = &map->buckets[hash];

    for (int i = 0; i < cur_bucket->len; i++)
    {
        if(strcmp(cur_bucket->items[i].key, key) == 0){
            cur_bucket->items[i].value = value;
            return;
        }
    }
    
    item* new_item = calloc(1, sizeof(item));
    new_item->key = calloc(strlen(key)+1, sizeof(char));
    strcpy(new_item->key, key);
    new_item->value = value;

    cur_bucket->items[cur_bucket->len] = *new_item;
    cur_bucket->len++;
}

// Функція для збільшення розміру конкретного кошика
int resize_bucket(bucket* b, int new_size) {
    if (b == NULL || new_size <= b->size) {
        return 0;  // Помилка: невалідні параметри
    }
    
    // Використовуємо realloc для збільшення масиву елементів
    item* new_items = realloc(b->items, new_size * sizeof(item));
    if (new_items == NULL) {
        return 0;  // Помилка виділення пам'яті, старі дані залишаються незмінними
    }
    
    // Ініціалізуємо нові елементи нулями
    for (int i = b->size; i < new_size; i++) {
        new_items[i].key = NULL;
        new_items[i].value = 0;
    }
    
    // Оновлюємо кошик
    b->items = new_items;
    b->size = new_size;
    
    return 1;  // Успішне збільшення
}

// Функція для отримання значення за ключем
int get(hash_map* map, char* key) {
}

// Функція для виведення всіх елементів хеш-карти
void print_hashmap(hash_map* map) {
    if (map == NULL) {
        return;
    }
    
    // Проходимо по всіх кошиках
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (map->buckets[i].items != NULL) {
            // Проходимо по всіх елементах у кошику
            for (int j = 0; j < map->buckets[i].size; j++) {
                // Виводимо тільки елементи з непустими ключами
                if (map->buckets[i].items[j].key != NULL) {
                    printf("%s -> %d\n", map->buckets[i].items[j].key, map->buckets[i].items[j].value);
                }
            }
        }
    }
}

// Функція для звільнення пам'яті, виділеної під хеш-карту
void free_hashmap(hash_map* map) {
    if (map == NULL) return;
    
    if (map->buckets != NULL) {
        // Проходимо по всіх кошиках
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (map->buckets[i].items != NULL) {
                // Звільняємо пам'ять для всіх рядків-ключів
                for (int j = 0; j < map->buckets[i].size; j++) {
                    if (map->buckets[i].items[j].key != NULL) {
                        free(map->buckets[i].items[j].key);
                    }
                }
                // Звільняємо масив елементів
                free(map->buckets[i].items);
            }
        }
        // Звільняємо масив кошиків
        free(map->buckets);
    }
    
    // Звільняємо саму структуру хеш-карти
    free(map);
}

int main() {
    // Створюємо нову хеш-карту
    hash_map* map = create_hashmap();
    
    if (map == NULL) {
        printf("failed to create\n");
        return 1;
    }
    
    // Додаємо елементи до хеш-карти
    put(map, "apple", 5);
    put(map, "banana", 8);
    put(map, "orange", 3);
    put(map, "grape", 2);
    
    // Додаємо більше елементів для тестування збільшення кошика
    // put(map, "watermelon", 10);
    // put(map, "strawberry", 7);
    // put(map, "pineapple", 9);
    // put(map, "kiwi", 4);
    put(map, "mango", 6);
    // put(map, "peach", 5);
    // put(map, "cherry", 3);
    // put(map, "plum", 2);
    
    // put(map, "apple", 6);  // Оновлюємо існуюче значення
    
    // Виводимо значення за ключами
    // printf("apple: %d\n", get(map, "apple"));    // Має вивести 6
    // printf("banana: %d\n", get(map, "banana"));  // Має вивести 8
    // printf("orange: %d\n", get(map, "orange"));  // Має вивести 3
    // printf("grape: %d\n", get(map, "grape"));    // Має вивести 2
    // printf("mango: %d\n", get(map, "mango"));    // Має вивести -1 (не знайдено)
    
    printf("Hashmap \n");
    print_hashmap(map);
    
    // Звільняємо пам'ять
    free_hashmap(map);
    
    return 0;
}