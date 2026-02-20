#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // 1. Перевіряємо, чи введено рівно один аргумент
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    // 2. Перевіряємо, чи ключ складається тільки з літер
    string key = argv[1];
    int key_len = strlen(key);
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }

    // 3. Отримуємо текст від користувача
    string plaintext = get_string("plaintext: ");

    // 4. Починаємо шифрування
    printf("ciphertext: ");

    // j — індекс для ключового слова, i — для відкритого тексту
    for (int i = 0, j = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Визначаємо зсув на основі поточної літери ключа (0-25)
            int shift = tolower(key[j % key_len]) - 'a';

            // Шифруємо велику літеру
            if (isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i] - 'A' + shift) % 26 + 'A');
            }
            // Шифруємо малу літеру
            else if (islower(plaintext[i]))
            {
                printf("%c", (plaintext[i] - 'a' + shift) % 26 + 'a');
            }

            // Збільшуємо індекс ключа ТІЛЬКИ якщо була зашифрована літера
            j++;
        }
        else
        {
            // Виводимо неалфавітні символи (пробіли, розділові знаки) без змін
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
