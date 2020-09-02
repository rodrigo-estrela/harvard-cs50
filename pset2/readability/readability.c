//Includes
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Functions declaration
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
bool isSentence(char c);
int colemanLiauIndex(string s);

int main(void)
{
    string text = get_string("Text: ");
    int index = colemanLiauIndex(text);

    if (index <= 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %i\n", index);
}

int count_letters(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalnum(s[i]))
        {
            counter++;
        }
    }
    return counter;
}

int count_words(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalnum(s[i]))
        {
            counter++;
            do
            {
                i++;
            }
            while (isgraph(s[i]) && s[i] != '\0');
        }
    }

    return counter;
}

int count_sentences(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalnum(s[i]))
        {
            counter++;
            do
            {
                i++;
            }
            while (isSentence(s[i]) && s[i] != '\0');
        }
    }

    return counter;
}

//Function to identify end of sentences characters '.' '?' '!' only
bool isSentence(char c)
{
    if (c == '.' || c == '?' || c == '!')
    {
        return false;
    }

    return true;
}

int colemanLiauIndex(string s)
{
    float letters = (float) count_letters(s);
    float words = (float) count_words(s);
    float sentences = (float) count_sentences(s);

    double L = (letters * 100.0) / words;
    double S = (sentences * 100.0) / words;

    return round(0.0588 * L - 0.296 * S - 15.8);
}