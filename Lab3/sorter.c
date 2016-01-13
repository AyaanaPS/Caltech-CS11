/*
 * This program sorts a list of integers inputted into 
 * the command line at runtime using either the minimum
 * element sorting method or the bubble sort method. The
 * maximum number of integers is 32. The optional commands
 * are '-b', which switches the sorting method to bubble sort,
 * and '-q', which suppresses the output.
 * The default sorting method is the minimum element sorter.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX   32 /* max number of integers */

/* function prototypes */

void min_element_sort(int num_elements, int array[]);
void bubble_sort(int num_elements, int array[]);

int main(int argc, char *argv[])
{
    int i, number, index = 0;
    int num_elements = argc - 1;
    int myArray[MAX];
    int bubbleSort = 0, suppress = 0;

    /* finding the true number of integers */

    for (i = 1; i < argc; i++)
    {
        /* checking if we need to bubble sort */
        if(strcmp(argv[i], "-b") == 0)
        {
            num_elements --;
            bubbleSort = 1;
        } 

        /* checking if we need to suppress the output */
        else if(strcmp(argv[i], "-q") == 0)
        {
            num_elements --;
            suppress = 1;
        }
    }

    /* ensuring that the number of elements is within the accepted range */

    if(num_elements == 0 || num_elements > MAX)
    {
        fprintf(stderr, "usage: %s [-b] [-q] number 1 [number 2 ... ] "
            "(maximum 32 numbers)\n", argv[0]);
        exit(1);
    }

    /* adding the numbers to the array */

    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-b") != 0 && strcmp(argv[i], "-q") != 0)
        {
            number = atoi(argv[i]);
            myArray[index] = number;
            index ++;
        }
    }

    /* sorting the list */

    if(bubbleSort == 1)
    {
        bubble_sort(num_elements, myArray);
    }
    else
    {
        min_element_sort(num_elements, myArray);
    }
    
    /* outputting the list */
    
    if(suppress != 1)
    {
        for(i = 0; i < num_elements; i++)
        {
            printf("%d\n", myArray[i]);
        }
    }

    return 0;
}

/* 
 * This function sorts the array of integers inputted
 * using the minimum element sorting algorithm.
 *
 * @param: This function takes in two parameters. The first
 * parameter represents the number of elements in the array.
 * The second element is the integer array itself.
 *
 * @return: This function does not return anything.
 *
 */

void min_element_sort(int num_elements, int array[])
{
    int start = 0, index, smallest, temp;
    while(start < num_elements)
    {
        smallest = start;

        /* finding the index of the smallest element */

        for(index = start; index < num_elements; index ++)
        {
            if (array[index] < array[smallest])
            {
                smallest = index;
            }
        }

        /* swapping the start and the smallest element */

        temp = array[smallest];
        array[smallest] = array[start];
        array[start] = temp;

        start ++;
    }

    /* checking that the list is sorted */

    for(index = 1; index < num_elements; index++)
    {
        assert(array[index] >= array[index - 1]);
    }
}

/* 
 * This function sorts the array of integers inputted
 * using the bubble sort algorithm.
 *
 * @param: This function takes in two parameters. The first
 * parameter represents the number of elements in the array.
 * The second element is the integer array itself.
 *
 * @return: This function does not return anything.
 *
 */

void bubble_sort(int num_elements, int array[])
{
    int i, last, temp;
    int remaining = num_elements - 1;

    while(remaining > 0)
    {
        last = 0;
        for (i = 0; i < remaining; i++)
        {
            if(array[i] > array[i + 1])
            {
                /* swapping the two consecutive elements */
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                last = i;
            }
        }

        remaining = last;
    }

    /* checking that the list is sorted */

    for(i = 1; i < num_elements; i++)
    {
        assert(array[i] >= array[i - 1]);
    }
}
