/*
 * This program sorts a list of integers inputted into 
 * the command line at runtime using the quicksort method. 
 * The numbers are stored in a linked list. The optional command
 * is '-q', which suppresses the output.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "memcheck.h"

/* Function Prototypes */

node* quicksort(node *list);

int main(int argc, char *argv[])
{
    int i, data, q;
    node *list, *temp, *sorted_list;
    list = NULL;
    q = 0;

    /* filling up the list */
    for(i = 1; i < argc; i++)
    {
        /* checking if argument is an optional command */
        if(strcmp(argv[i], "-q") != 0)
        {
            data = atoi(argv[i]);
            temp = create_node(data, list);

            list = temp;
        }

        else
        {
            q = 1;

        } 

    }

    /* ensuring that the list is not empty */
    if(list == NULL)
    {
        fprintf(stderr, "usage: %s [-q] number 1 [number 2... ] "
            "\n", argv[0]);
        exit(1);
    }
    
    /* sorting the list */
    sorted_list = quicksort(list);
    free_list(list);
    list = sorted_list;

    /* printing the sorted list, if not suppressed */
    if(q == 0)
    {
        print_list(list);
    }

    /* freeing the memory */
    free_list(sorted_list);

    print_memory_leaks();
    return 0;
}

/* 
 * This function sorts the linked list of integers inputted.
 * It does not alter the list.
 *
 * @param: This function takes in one parameter: A linked list
 * representing the integers to be sorted.
 *
 * @return: A linked list containing the sorted integers.
 *
 */


node* quicksort(node *list)
{
    node *larger, *smaller;
    node *sortedL, *sortedS;
    node *temp1, *temp2;
    node *copy, *result1, *result2;
    node *i = list;

    copy = list;
    larger = NULL;
    smaller = NULL;

    /* checking the base case */
    if(list == NULL)
    {
        result2 = copy_list(list);
        return result2;
    }

    copy = create_node(list->data, NULL);
    i = i->next;

    /* filling the larger and smaller nodes */
    while(i != NULL)
    {
        /* checking for malloc failures */
        if (temp1 == NULL || temp2 == NULL)
        {
            fprintf(stderr, "Error: malloc() failed.\n");
            exit(1);
        }

        if(i->data >= copy->data)
        {
            temp1 = create_node(i->data, larger);
            larger = temp1;
        }
        else
        {
            temp2 = create_node(i->data, smaller);
            smaller = temp2;
        }

        i = i->next;
    }

    /* sorting the smaller and larger nodes */
    sortedS = quicksort(smaller);
    free_list(smaller);
    smaller = sortedS;

    sortedL = quicksort(larger);
    free_list(larger);
    larger = sortedL;

    /* combining the result */
    result1 = append_lists(sortedS, copy);
    result2 = append_lists(result1, sortedL);


    /* freeing the memory */
    free_list(result1);
    free_list(copy);
    free_list(sortedL);
    free_list(sortedS);

    assert(is_sorted(result2));
    return result2;

} 
