#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//  export DYLD_LIBRARY_PATH=/usr/local/lib

string encode(int k, string text)
{

    int length = strlen(text);

    char encoded_arr[length + 1];

    string encoded_text;

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]))
        {
            char c = text[i];
            char enc = ((c - 'a') + k) % 26 + 'a';
            encoded_arr[i] = enc;
        }
        else if (isupper(text[i]))
        {
            char c = text[i];
            char enc = ((c - 'A') + k) % 26 + 'A';
            encoded_arr[i] = enc;
        }
        else
        {
            char c = text[i];
            encoded_arr[i] = c;
        }
    }
    encoded_arr[length] = '\0';
    encoded_text = malloc(length + 1);
    strcpy(encoded_text, encoded_arr);
    return encoded_text;
}
string decode(int k, string text)
{
    int length = strlen(text);
    char decoded_arr[length + 1];
    string decoded_text;

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]))
        {
            char c = text[i];
            char dc = ((c - 'a' - k + 26) % 26) + 'a';
            decoded_arr[i] = dc;
        }
        else if (isupper(text[i]))
        {
            char c = text[i];
            char dc = ((c - 'A' - k + 26) % 26) + 'A';
            decoded_arr[i] = dc;
        }
        else
        {
            char c = text[i];
            decoded_arr[i] = c;
        }
    }
    decoded_arr[length] = '\0';
    decoded_text = malloc(length + 1);
    strcpy(decoded_text, decoded_arr);
    return decoded_text;
}
void caesar(int k, char text[100])
{

    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]))
        {
            char z = ((text[i] - 'a') + k) % 26 + 'a';
            printf("%c", z);
        }
        else if (isupper(text[i]))
        {
            char c = ((text[i] - 'A') + k) % 26 + 'A';
            printf("%c", c);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

bool validate_imput(int argc, string argv[])
{
    bool is_valid = true;
    if (argc != 2)
    {
        is_valid = false;
    }

    string key = argv[1];
    char first_in_key = key[0];
    int lenght = strlen(key);
    for (int i = 0; i < lenght; i++)
    {
        char digit = key[i];
        bool is_digit = isdigit(digit);
        if (!is_digit)
        {
            is_valid = false;
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
        int k = atoi(key);
        string plaintext = get_string("plaintext: ");
        string text = plaintext;
        string ciphertext = encode(k, text);
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}
