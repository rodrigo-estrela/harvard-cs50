#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int keyValidation(string key);
char cipher(char c, string key);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int inputValidation = keyValidation(argv[1]);
    switch (inputValidation)
    {
        case 1:
            printf("Key must contain 26 characters.\n");
            return 1;
        case 2:
        case 3:
            printf("Usage: ./substitution key\n");
            return 1;
        default:
            break;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            printf("%c", cipher(text[i], argv[1]));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

//Function to validate the key as digit value only
int keyValidation(string key)
{
    //Check the key size
    if (strlen(key) != 26)
    {
        return 1;
    }

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        //Check if all values in the key are alphanumericals
        if (!isalpha(key[i]))
        {
            return 2;
        }
        
        //Check for duplicated values in the key
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                if (key[j] == key[i])
                {
                    return 3;
                }
            }
        }
    }

    return 0;
}

char cipher(char c, string key)
{
    if (isupper(c))
    {
        return toupper(key[c - 'A']);
    }

    return tolower(key[c - 'a']);
}