/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"

#define modulo 128

/*** Hash function. ***/

int hash(char *s)
{
    int letter, i;
    int sum = 0;
    for(i = 0; i < strlen(s); i++)
    {
        letter = (int)s[i];
        sum += letter;
    }

    return sum % modulo;
    

}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->value = value;  /* Fill in the new node with the given value. */
    result->key = key;
    result->next = NULL;

    return result;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *n;

    while(list != NULL)
    {
        n = list;
        list = list->next;

        free(n->key);
        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    int i;
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    if (ht == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    ht->slot = malloc(sizeof(node) * NSLOTS);
    if (ht->slot == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    for(i = 0; i < NSLOTS; i ++)
    {
        ht->slot[i] = NULL;
    }

    return ht; 

}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    for(i = 0; i < NSLOTS; i++)
    {
        free_list(ht->slot[i]);
    }

    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    node * i;

    for(i = ht->slot[hash(key)]; i != NULL; i = i->next)
    {
        if(strcmp(i->key, key) == 0)
        {
            return i->value;
        }
    }

    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    node * i;
    node *list;

    int num = hash(key);

    for(i = ht->slot[num]; i != NULL; i = i->next)
    {
        if(strcmp(i->key, key) == 0)
        {
            i->value = value;
            free(key);
            break;
        }
    }

    list = create_node(key, value);
    list->next = ht->slot[num];
    ht->slot[num] = list;   

}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *n;

    for(i = 0; i < NSLOTS; i++)
    {
        for (n = ht->slot[i]; n != NULL; n = n->next)
        {
            if(n->key != NULL)
            {
                printf("%s %d\n", n->key, n->value);
            }
        }
    }

}
