


#define _XOPEN_SOURCE
#include <unistd.h> // Для функції crypt
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Перевірка аргументів (має бути 1 хеш)
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    char *hash = argv[1];
    
    // Сіль (salt) — це перші два символи хешу
    char salt[3];
    salt[0] = hash[0];
    salt[1] = hash[1];
    salt[2] = '\0';

    // Алфавіт для перебору (всі малі та великі латинські літери)
    const char *letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int num_letters = 53; // 52 літери + '\0'

    char guess[6]; // Максимум 5 символів + термінатор рядка

    // ЗОВНІШНІ ТА ВНУТРІШНІ ЦИКЛИ (Брутфорс)
    // Кожен вкладений цикл відповідає за певну позицію в паролі.
    
    for (int fifth = 0; fifth < num_letters; fifth++)
    {
        for (int fourth = 0; fourth < num_letters; fourth++)
        {
            for (int third = 0; third < num_letters; third++)
            {
                for (int second = 0; second < num_letters; second++)
                {
                    // Цей цикл перебирає перший символ найшвидше
                    for (int first = 1; first < num_letters; first++)
                    {
                        guess[0] = letters[first];
                        guess[1] = letters[second];
                        guess[2] = letters[third];
                        guess[3] = letters[fourth];
                        guess[4] = letters[fifth];
                        guess[5] = '\0';

                        // Перевірка: чи збігається згенерований пароль із хешем
                        if (strcmp(crypt(guess, salt), hash) == 0)
                        {
                            printf("%s\n", guess);
                            return 0; // Пароль знайдено, вихід
                        }
                    }
                }
            }
        }
    }

    return 0;
}
