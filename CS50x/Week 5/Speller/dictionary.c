// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <cs50.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // length + 1 because after each character there has to be the ending character "\0"
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200000;

// Hash table
node *table[N];

// here i will declare the varibles to use in the code
unsigned int hash_value;
int word_count = 0; // initializes counter for the words in dictionary with 0

// Returns true if word is in dictionary, else false (case insensitive)
bool check(const char *word)
{
    // TODO - DONE
    // First, we need to call the hash function and store the result in a variable called hash_value.
    hash_value = hash(word);

    // Now we need to find the place where the word might be in the hash table.
    // We can do this by looking at the linked list stored in the table at the position
    // given by the hash value.
    // We create a variable called cursor that points to the first node in the linked list.
    node *cursor = table[hash_value];

    // We need to go through the linked list to see if the word is in there.
    // We use a while loop to keep going until we've checked all the nodes in the list.
    // We start by checking if the cursor is pointing to a node (not NULL).
    while (cursor != NULL)
    {
        // Inside the loop, we need to compare the word with the word in the current node.
        // We use the strcasecmp function to do this because it ignores case.
        // If the words match, strcasecmp returns 0 and we know the word is in the list.
        if (strcasecmp(word, cursor->word) == 0)
        {
            // If we find the word, we return true to indicate that it's in the list.
            return true;
        }

        // If the words don't match, we move on to the next node in the list.
        // We do this by setting the cursor to point to the next node.
        cursor = cursor->next;
    }

    // If we get through the whole list without finding the word, it's not in the list.
    // We return false to indicate that the word is not in the list.
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Make this hash function better - DONE
    long sum = 0; // adds up the ASCII values of each character in the word
    for (int i = 0; i < strlen(word); i++) // loops through each character in the word
    {
        sum += tolower(word[i]); // takes the lowercase number value of each letter and adds it to the sum
    }
    return sum % N; // divides the sum by N to find which index it belongs to
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO - DONE
    FILE *file = fopen(dictionary, "r"); // opens the dictionary file

    if (file == NULL) // return false if the file can't be opened
    {
        printf("File cannot be opened %s\n", dictionary);
        return false;
    }

    // reads dictionary word by word (writes into the hash table nodes which contain
    // words from dictionary) until it reaches the end of the file
    char word[LENGTH + 1];

    // as long as it can reach strings from file without returning EOF it will create new node
    while (fscanf(file, "%s", word) != EOF) // EOF stans fro end of the file
    {
        // alocates a piece of memory for each new node, we can use node because its
        // previously declared (for malloc <stdlib.h> has to be included)
        node *n = malloc(sizeof(node));

        if (n == NULL) // if malloc returns NULL function returns false
        {
            return false;
        }

        strcpy(n->word, word); // copies the word into the node (for strcpy has to be <string.h> included)
        hash_value = hash(word); // get value using the hast function
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++; // adds one to keep track of the number of words
    }

    fclose(file); // after all is done closes file and returns true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO - DONE
    if (word_count > 0) // there are words retur the word_count
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO - DONE
    // it needs to free up the momeory it used while locating the memory using the malloc function
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // as it moves the cursor to the next node i can free up the memory of the previous one
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
            // if cursor is nul, it means the function has reached
            // the end of the linked list, so it can stop running
        {
            return true;
        }
    }
    return false;
}
