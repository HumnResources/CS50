// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void init_table(void);
void free_list(node *head);
bool search_list(node *head, const char *word);
node *create_node(void);

// Number of buckets in hash table
const unsigned int N = 26 * 26;

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);

    if (table[h] != NULL)
    {
        return search_list(table[h], word);
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Set return variable
    unsigned int ret = 0;

    // Hash each character of the word
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        ret += tolower(word[i]) * N;
    }

    // Double check we're greater than zero before applying modulous
    if (ret > 0)
    {
        // Using modulous to garuntee a valid range of values
        ret = ret % LENGTH;
    }

    return ret;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Set file pointer to look at dictionary
    FILE *dict_fp = fopen(dictionary, "r");
    if (dict_fp == NULL)
    {
        return false;
    }

    // Set table to NULL pointers for safety
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    int h = 0;
    // Loop through until we hit EOF
    while (!feof(dict_fp))
    {
        // Create new node for word
        node *n = create_node();
        if (n == NULL)
        {
            free(dict_fp);
            return false;
        }

        // Copy next word into new node
        fscanf(dict_fp, "%s", n->word);

        // Make sure we have a valid word
        if (!isalpha(n->word[0]))
        {
            free(n);
            continue;
        }

        // Get dictionary index
        h = hash(n->word);

        // Check if index is available, adding to head of list if necessary
        // Using head insertion for speed
        if (table[h] == NULL)
        {
            table[h] = n;
        }
        else
        {
            node *tmp = table[h];
            table[h] = n;
            n->next = tmp;
        }

        word_count++;
    }

    // If we got this far the whole dictionary was successfully parsed into memory
    fclose(dict_fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return (unsigned int) word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Check if we found a valid node
        if (table[i] != NULL)
        {
            // If at leaf node, free now
            // Otherwise free list of nodes
            if (table[i]->next == NULL)
            {
                free(table[i]);
            }
            else
            {
                free_list(table[i]);
            }
        }
    }
    return true;
}

void free_list(node *head)
{
    // Base Case
    if (head == NULL)
    {
        return;
    }
    // Recursively call until we hit the end node
    free_list(head->next);

    // Free the leaf node(s)
    free(head);
}

bool search_list(node *head, const char *word)
{
    // do...while to ensure first check of head
    do
    {
        // If we have a match, return
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }

        // Update pointer to next in list
        head = head->next;
    }
    while (head != NULL);

    return false;
}

node *create_node(void)
{
    // Allocate memory for new node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    // Set initial values
    n->next = NULL;

    // We do this to ensure no memory errors, otherwise we may end
    // up with garbage values causing issues
    for (int i = 0; i < LENGTH; i++)
    {
        n->word[i] = 0;
    }

    return n;
}