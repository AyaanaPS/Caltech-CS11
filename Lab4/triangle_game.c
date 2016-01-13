#include <stdio.h>
#include "triangle_routines.h"

#define NMOVES 36

/* All of the possible moves: */

int moves[NMOVES][3] =
{
    {0, 1, 3}, {0, 2, 5},
    {1, 3, 6}, {1, 4, 8},
    {2, 4, 7}, {2, 5, 9},
    {3, 1, 0}, {3, 4, 5}, { 3, 6, 10}, {3, 7, 12},
    {4, 7, 11}, {4, 8, 13},
    {5, 2, 0}, {5, 4, 3}, {5, 8, 12}, {5, 9, 14},
    {6, 3, 1}, {6, 7, 8},
    {7, 4, 2}, {7, 8, 9},
    {8, 4, 1}, {8, 7, 6},
    {9, 5, 2}, {9, 8, 7},
    {10, 6, 3}, {10, 11, 12},
    {11, 7, 4}, {11, 12, 13},
    {12, 11, 10}, {12, 13, 14}, {12, 7, 3}, {12, 8, 5},
    {13, 12, 11}, {13, 8, 4},
    {14, 13, 12}, {14, 9, 5}
};

/* 
 * Computes and returns the number of pegs on the board.
 *
 * @param = array integer board representing the board.
 *
 * @return = integer representation of the number of pegs.
 *
 */

int npegs(int board[])
{
    int index, numPegs = 0;
    for (index = 0; index <= 14; index ++)
    {
        if(board[index] != 0)
        {
            numPegs ++;
        }
    }

    return numPegs;
}

/*
 * Ensures that the move is valid.
 * This means the first two spaces have pegs and the third doesn't.
 *
 * @param: integer array representing the board.
 *          integer array representing the move.
 *
 * @return: 1 if the move is valid. 0 if it is not.
 *
 */

int valid_move(int board[], int move[])
{
    if(board[move[0]] == 1 && board[move[1]] == 1)
    {
        if(board[move[2]] == 0)
        {
            return 1;
        }
    }

    return 0;
}

/*
 * This both makes and unmakes the move.
 *
 * @param: integer array representing the board.
 *          integer array representing the move.
 *
 * void return
 */

void do_move(int board[], int move[])
{
    board[move[0]] = !board[move[0]];
    board[move[1]] = !board[move[1]];
    board[move[2]] = !board[move[2]];
}

/*
 * This solves the board and prints the solution in reverse order.
 *
 * @param: integer array representing the board.
 *
 * @return: 1 if the board is solvable. 0 if it is not.
 *
 */

int solve(int board[])
{
    int pegs = npegs(board);
    int index;
    if(pegs == 1) 
    {
        triangle_print(board);
        return 1;
    }
    else
    {
        for(index = 0; index < NMOVES; index ++)
        {
            if(valid_move(board, moves[index]) == 1)
            {
                do_move(board, moves[index]);
                if(solve(board) == 1)
                {
                    do_move(board, moves[index]);
                    triangle_print(board);
                    return 1;
                }

                do_move(board, moves[index]);
            }
        }
    }

    return 0;
}

int main(void)
{
    int board[15];
    triangle_input(board);
    if(solve(board) == 1)
    {
        printf("It can be solved!\n");
    }
    else
    {
        printf("It cannot be solved!\n");
    }
}
