/*
 * This program computes the specified number of generations
 * for a randomly generated 'array' of 1's and 0's using the
 * given update rule: 
 *
 * if empty, if one of the adjacent cells (but not both) is
 * full, current cell is full.
 * else, current cell is empty.
 *
 * This uses pointer arithmetic to update the board.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memcheck.h"

/* function prototypes */

void computeNextGenP(int size, int* array, int* newArray);
void printGeneration(int size, int* array);


int main(int argc, char *argv[])
{
    int numberCells;
    int generations;
    int *cells;
    int *nextGen;
    int i, x = 0;

    if(argc != 3)
    {
        fprintf(stderr, "usage: %s numCells numGens\n", argv[0]);
        exit(1);
    }

    numberCells = atoi(argv[1]);
    generations = atoi(argv[2]);

    srand((unsigned) time(0));  
    cells = (int *) calloc(numberCells, sizeof(int));
    nextGen = (int *) calloc(numberCells, sizeof(int));

    if(cells == NULL || nextGen == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }

    for(i = 1; i < numberCells - 1; i++)
    {
        *(cells + i) = rand() % 2;
    }

    printGeneration(numberCells, cells);

    while(x < generations)
    {
        computeNextGenP(numberCells, cells, nextGen);
        printGeneration(numberCells, nextGen);
        x++;
    }

    free(cells);
    free(nextGen);  
    print_memory_leaks();

    return 0;
}

/* 
 * This function uses pointer arithmetic to compute the 
 * next generation based on the update rule.
 *
 * @param: size = size of the array, array = the starting
 * generation, newArray = the final generation.
 *
 */

/* Pointer to the newArray should be in the same fashion as the
 * pointer to before, current and after. Instead of doing
 * *(newArray + i) each time, we can have a poitner to the new
 * array and increment that.
 */
void computeNextGenP(int size, int* array, int* newArray)
{
    int i;
    int *before, *current, *after;

    before = array;
    current = (array + 1);
    after = (array + 2);

    for(i = 1; i < size - 1; i++)
    {

        if(*current == 0)
        {
            if(*before == 1 && *after == 0)
            {
                *(newArray + i) = 1;
            }

            else if(*before == 0 && *after == 1)
            {
                *(newArray + i) = 1;
            }

            else
            {
                *(newArray + i) = 0;
            }
        }

        else
        {
            *(newArray + i) = 0;
        }

        before++;
        current++;
        after++;
    }

    for(i = 1; i < size - 1; i++)
    {
        *(array + i) = *(newArray + i);
    }
}

/* 
 * This function prints out the generation. It prints a 
 * '.' for a 0 and a '*' for a 1.
 *
 * @param: size = size of the array, array = the array to 
 * be printed.
 *
 */
 
void printGeneration(int size, int* array)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(*array == 0)
        {
            printf(".");
        }
        else
        {
            printf("*");
        }

        array++;
    }
    printf("\n");
}
