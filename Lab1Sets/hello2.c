#include <stdio.h> /* declaration of printf() and scanf() function */

int main(void) /* declaration of printf() and scanf() */
{
    char str[100]; /* max size of string = 100 */

    printf("Enter your name: ");
    scanf("%99s", str);
    printf("hello, %s!\n", str);
    return 0;
}
