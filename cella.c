#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include <assert.h>
#include <time.h>
#include <string.h>

/*
 * cella:
 * This program prints the values over time of a one - dimensional cellular
 * automata. The 1dCA update rule prints out triangle fractals.
 * This program takes 2 command line arguments, the first is the number of
 * cells in the 1dCA. The second is the number of generations to print.
 */

/* This function seeds the starting array with random 1's and 0's.
 * The first and last cell are 0's. This function takes an array and the size
 * of the array as int arguments.
 */
void seed(int array[], int cellnum)
{
    int i;

    srand(time(0));
    for (i = 1; i < cellnum - 1; i++)
    {
        array[i] = (rand() % 2);
    }
}

/* This function prints the array, printing each empty cell as a "." and each
 * full cell as an "A". It takes an array of integers and its size as
 * arguments.
 */

void printit(int array[], int cellnum)
{
    int i;
    for (i = 0; i < cellnum; i++)
    {
        if (array[i] == 0)
        {
            printf(".");
        }
        else
        {
            printf("A");
        }
    }
    printf("\n");

}

/* This function updates the 1dCA array with the following update rule:
 *  1. If the current cell is empty, and one of the adjacent cells is full
 *     (but not both), set the current cell to be full.
 *  2. Otherwise, set the current cell to be empty
 * This function then prints each generatiom.
 * The function takes an array of ints, the array size, and the number of
 * generations to update as arguments.
 */
void update(int *arr1, int cellnum, int numgen)
{
    while (numgen > 0)
    {
        int *arr2;
        int i;

        arr2 = (int *) calloc(cellnum, sizeof(int)); /* creates temp array */
        if (arr2 == NULL)
        {
            fprintf(stderr, "out of memory!\n");
            exit(1);
        }

        for (i = 1; i < cellnum - 1; i++)
        {
            if (arr1[i] == 0)
            {
                if ((arr1[i - 1] == 0 && arr1[i + 1] == 1)||\
                    (arr1[i + 1] == 0 && arr1[i - 1] == 1\
                    ))
                {
                    arr2[i] = 1; /* change arr2 based on contents of arr1 */
                }
            }
            else
            {
                arr2[i] = 0;
            }
        }

        free(arr1);
        arr1 = arr2;  /* assign arr1 to point to arr2 */
        printit(arr1, cellnum);
        numgen--;
    }

    free(arr1);
}


int main(int argc, char *argv[])
{
    int cellnum;
    int numgen;
    int *arr1;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s [cellnum] [numgen] \n", argv[0]);
        exit(1);
    }

    cellnum = atoi(argv[1]);
    numgen = atoi(argv[2]);

    arr1 = (int *) calloc(cellnum, sizeof(int));
    if (arr1 == NULL)
    {
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }

    seed(arr1, cellnum);
    printit(arr1, cellnum);
    update(arr1, cellnum, numgen);
    print_memory_leaks();

}
