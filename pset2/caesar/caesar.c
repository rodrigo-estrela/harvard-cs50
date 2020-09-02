#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isInvalidKey(string key);
char shift(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || isInvalidKey(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            printf("%c", shift(text[i], key));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

//Function to validate the key as digit value only
bool isInvalidKey(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return true;
        }
    }

    return false;
}

char shift(char c, int key)
{
    if (isupper(c))
    {
        return 'A' + (c - 'A' + key) % 26;
    }

    return 'a' + (c - 'a' + key) % 26;
}
