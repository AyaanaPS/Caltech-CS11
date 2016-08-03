/* This program reads a name and finds a random integer, n. It then
prints out a greeting based on whether the n is odd or even. The greeting
The greeting is printed out n times. */

#include <stdio.h> /* declaration of printf() and scanf() */
#include <stdlib.h> /* declaration of srand() */
#include <time.h> /* declaration of time() */

int main(void)
{
    char str[100]; /* max size of string = 100 */
    int number, i;
    srand(time(0));

    printf("Enter your name: ");
    scanf("%99s", str);

    number = rand() % 10 + 1; /* generates a random number between 1 & 10 */

    printf("The number is: %d\n", number);

    for(i = 0; i < number; i++)
    {
        if(number % 2 == 0) /* if the number is even */
        {
            printf("%d: hello, %s!\n", number, str);
        }
        else /* if the number is odd */
        {
            printf("%d: hi there, %s!\n", number, str);
        }
    }
    return 0;
}
