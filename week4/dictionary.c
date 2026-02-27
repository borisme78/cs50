// Implements a dictionary's functionality
// Реалізує функціональність словника

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
// Представляє кількість сегментів у хеш-таблиці
#define N 26

// Represents a node in a hash table
// Представляє вузол у хеш-таблиці
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents a hash table
// Представляє хеш-таблицю
node *hashtable[N];

// Лічильник кількості слів
unsigned int word_count = 0;


// Hashes word to a number between 0 and 25 safely
// Перетворює слово в число від 0 до 25 безпечно
unsigned int hash(const char *word)
{
    // якщо перший символ не літера (наприклад апостроф)
    // повертаємо 0 щоб уникнути від'ємного індексу
    if (!isalpha(word[0]))
    {
        return 0;
    }

    return tolower(word[0]) - 'a';
}


// Loads dictionary into memory, returning true if successful else false
// Завантажує словник у пам'ять, повертаючи true у разі успіху, інакше false
bool load(const char *dictionary)
{
    // обнуляємо лічильник слів
    word_count = 0;

    // Ініціалізуємо хеш-таблицю
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Відкриваємо словник
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Буфер для слова
    char word[LENGTH + 1];

    // Вставляємо слова в хеш-таблицю
    while (fscanf(file, "%45s", word) != EOF)
    {
        // створюємо новий вузол
        node *new_node = malloc(sizeof(node));

        // якщо пам’ять не виділилась — закриваємо файл і повертаємо false
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // копіюємо слово у вузол
        strcpy(new_node->word, word);

        // визначаємо індекс за допомогою hash
        int index = hash(word);

        // додаємо вузол на початок списку (метод "вішалки")
        new_node->next = hashtable[index];
        hashtable[index] = new_node;

        // збільшуємо кількість слів
        word_count++;
    }

    // Закриваємо словник
    fclose(file);

    return true;
}


// Returns number of words in dictionary
// Повертає кількість слів у словнику
unsigned int size(void)
{
    return word_count;
}


// Returns true if word is in dictionary else false
// Повертає true, якщо слово є в словнику, інакше false
bool check(const char *word)
{
    // визначаємо індекс
    int index = hash(word);

    // проходимо по зв’язаному списку
    node *cursor = hashtable[index];

    while (cursor != NULL)
    {
        // порівнюємо без врахування регістру
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}


// Unloads dictionary from memory
// Вивантажує словник з пам’яті
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        hashtable[i] = NULL;
    }

    return true;
}