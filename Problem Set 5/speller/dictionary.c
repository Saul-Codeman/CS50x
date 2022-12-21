// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Introduce word count for size function
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    // Assign pointer to word in hash table
    node *n = table[hash_value];
    // Check if word is in dictionary by comparing strings.
    // Go through linked list
    while (n != NULL)
    {
        // Check if word is in linked list
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        // Go to next hash value of linked list
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long hash_number = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_number += tolower(word[i]);
    }
    return hash_number % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary
    FILE *dictionary_pointer = fopen(dictionary, "r");
    // Determine if file cannot be opened
    if (dictionary_pointer == NULL)
    {
        return false;
    }
    // Declare a new word
    char new_word[LENGTH + 1];
    // Read strings from dictionary file one at a time
    while (fscanf(dictionary_pointer, "%s", new_word) != EOF)
    {
        // Allocating space for new node
        node *n = malloc(sizeof(node));
        // Checking if n is pointing to null
        if (n == NULL)
        {
            return false;
        }
        // Copy the pointer to the word to the new word
        strcpy(n->word, new_word);
        // Set new pointer to null
        n->next = NULL;
        // Hash the word
        int hash_num = hash(new_word);
        // Set new pointer to the head of the table
        n->next = table[hash_num];
        // Set head to new pointer
        table[hash_num] = n;
        // Increase word count for size function
        word_count++;
    }
    fclose(dictionary_pointer);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            // Assign tmp to the pointer n
            node *tmp = n;
            // Move n to the next pointer
            n = n->next;
            // Free the initial position
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
