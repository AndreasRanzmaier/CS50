// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

uint32_t dictSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    uint16_t hashvalue = hash(word);

    // search through
    node *nextnode = table[hashvalue];
    if(nextnode == NULL)
    {
        return false;
    }
    while(nextnode != NULL)
    {
        if(strcasecmp(nextnode->word, word) == 0)
        {
            return true;
        }
        else
        {
            nextnode = nextnode->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    uint16_t tmp1 = (toupper(word[0]) - 'A');
    uint16_t tmp2 = 0;
    uint16_t tmp3 = 0;

    if((word[1] != '\000') && (word[1] != '\''))
    {
        tmp2 = (toupper(word[1]) - 'A') * 10;
    }
    if((word[2] != '\000') && (word[2] != '\''))
    {
        tmp2 = (toupper(word[2]) - 'A') * 100;
    }

    return tmp1 + tmp2 + tmp3;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dict file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // read all words from dict
    char word[LENGTH + 1];
    while(fscanf(file, "%s", word) != EOF)
    {
        // allocate a node for each word and pass in the word
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        uint16_t hashvalue = hash(word);

        // hash where to put that node in our hash table
        n->next = table[hashvalue];
        table[hashvalue] = n;

        dictSize++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp;

        while(cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
