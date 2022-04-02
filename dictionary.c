// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
const unsigned int N = 26;

// Hash table
node *table[N];

// Total amount of words

unsigned int amount_of_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //set the variable to check if word is found
    bool is_in_dic = false;

    //find the index in the table
    unsigned int index = hash(word);

    node *cursor = table[index];

    //while word is not found continue searching
    while (is_in_dic == false)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            //change "false" to "true" if word is found
            is_in_dic = true;
            return true;
        }
        else
        {
            //if not found "cursor" points to next node
            cursor = cursor->next;

            if (cursor == NULL)
            {
                return false;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    char *buffer = malloc((sizeof(char) * 45) + 1);

    while (fscanf(file, "%s", buffer) == 1)
    {
        node *current_n = malloc(sizeof(node));

        if (current_n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(current_n->word, buffer);

            unsigned int index = hash(current_n->word);

            if (table[index] != NULL)
            {
                current_n->next = table[index]; // current_n should point to the last added element (table[index])
            }
            else
            {
                current_n->next = NULL;
            }

            table[index] = current_n; //table[index] should point to current_n

            amount_of_words++;
        }
    }

    free(buffer);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    if (amount_of_words == 0)
    {
        return 0;
    }
    return amount_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 26; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;

            cursor = cursor->next;

            free(tmp);
        }
    }
    return true;
}