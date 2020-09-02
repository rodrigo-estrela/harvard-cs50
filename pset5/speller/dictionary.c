// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototypes
node *insert(node *head, char *value);
void destroy(node *head);
char *lower(const char *word);

// Number of buckets in hash table
const unsigned int N = 94967295;

// Hash table
node *table[N];

// Number of words
int wordCounter;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char *lc = lower(word);
    unsigned int bucket = hash(lc);
    // a. create a traversal pointer pointing to the list's head
    for (node *traversalPointer = table[bucket]; traversalPointer != NULL; traversalPointer = traversalPointer->next)
    {
        // b. if the current node's value is what we're looking for, report success
        
        if (strcmp(traversalPointer->word, lc) == 0)
        {
            free(lc);
            return true;
        }
    }// c. if not, set the traversal pointer to the next pointer in the list and go back to step b
    free(lc);

    // d. if you've reached the end of the list, report failure
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char *word = malloc((LENGTH + 1) * sizeof(char));
    unsigned int bucket = 0;
    while (fscanf(inptr, "%s", word) != EOF)
    {
        char *lc = lower(word);
        bucket = hash(lc);
        table[bucket] = insert(table[bucket], lc);
        wordCounter++;
        free(lc);
    }

    free(word);
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(table[i]);
        }
    }

    return true;
}

// Insert a new node into the linked list
node *insert(node *head, char *value)
{
    // a. Dynamically allocate space for a new node
    node *llnode = malloc(sizeof(node));
    // b. Check to make sure we didn't run out of memory
    if (llnode == NULL)
    {
        return NULL;
    }

    // c. Populate and insert the node at the beginning of the linked list
    strcpy(llnode->word, value);
    llnode->next = head;

    // d. Return a pointer to the new head of the list
    return llnode;
}

// Delete an entire linked list
void destroy(node *head)
{
    // a. If you're reached a null pointer, stop.
    if (head->next == NULL)
    {
        free(head);
        return;
    }

    // b. Delete the rest of the list.
    destroy(head->next);

    // c. Free the current node.
    free(head);
}

char *lower(const char *word)
{
    char *lowercase = malloc((LENGTH + 1) * sizeof(char));
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        lowercase[i] = tolower(word[i]);
    }
    lowercase[n] = '\0';
    return lowercase;
}
