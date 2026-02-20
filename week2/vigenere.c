#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int convert_latter_to_number(char latter)
{
    char k = latter;
    int number;
    if (isupper(k))
    {
        int key = 0;
        key = k - 65;
        number = key;
    }
    else if (islower(k))
    {
        int key = 0;
        key = k - 97;
        number = key;
    }
    return number;
}
char encode(int k, char letter)
{
    if (islower(letter))
    {
        char enc = ((letter - 'a') + k) % 26 + 'a';
        return enc;
    }
    else if (isupper(letter))
    {
        char enc = ((letter - 'A') + k) % 26 + 'A';
        return enc;
    }
    else
    {
        return letter;
    }
}

bool validate_imput(int argc, string argv[])
{
    bool is_valid = true;
    if (argc != 2)
    {
        is_valid = false;
        printf("Usage: ./vigenere keyword\n");
    }

    string key = argv[1];
    char key_i;
    int lenght = strlen(key);
    for (int i = 0; i < lenght; i++)
    {
        key_i = key[i];
        if (!isalpha(key_i))
        {
            is_valid = false;
            printf("Usage: ./vigenere keyword\n");
            break;
        }
    }
    return is_valid;
}

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    bool is_valid = validate_imput(argc, argv);

    if (is_valid == true)
    {
        string key = argv[1];
        string word = get_string("plaintext: ");
        printf("ciphertext:");


        int key_lenght = strlen(key);
        int word_lenght = strlen(word);

        for (int i = 0; i < word_lenght; i++)
        {
            char word_char = word[i];
            for (int j = 0; j < key_lenght; j++)
            {
                if (i == word_lenght - 1)
                {

                    char key_char = key[j];
                    int key = convert_latter_to_number(key_char);
                    char cipher_char = encode(key, word_char);
                    printf("%c", cipher_char);
                    break;
                }
                if(key[i]=='\0'){
                    break;
                }
                char key_char = key[i];
                int key = convert_latter_to_number(key_char);
                char cipher_char = encode(key, word_char);
                printf("%c", cipher_char);
                break;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}
