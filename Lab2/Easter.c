/* This program includes a function that computes the date of easter
 * for a given year. 
 * The function is used in the main function to read various integers
 * from a file and print out their date (onto another file). The file
 * handling is done using redirection in the terminal. If the easter date
 * is 0, the program prints an error to the terminal.
 */

#include <stdio.h>

/*
 * This function computes the date of easter for an inputted year.
 * 
 * @param: This function takes in an integer that represents the year.
 * The integer should be within the acceptable range (greater than 1582
 * and less than 39999.)
 *
 * @return: This function returns an integer N that represents the date.
 * A negative number indicates that easter was on March N. A positive 
 * number indicates that easter was on April N. If the number equals 0,
 * it means that the year was out of range.
 *
 */

int calculate_easter_date(int year)
{
    int date, goldenY, century, skippedLeap;
    int correction, sunday, epact, fullMoon;

    if (year < 1582 || year > 39999) /* check date range */
    {
        return 0;
    }

    /* Compute the year of the Metonic Cycle */
    goldenY = (year % 19) + 1; 

    /* Compute what century the year is in */
    century = (year / 100) + 1; 

    /* Compute number of skipped leap years */
    skippedLeap = ((3 * century) / 4) - 12; 

    /* Synchronize Easter with the moon's orbit */
    correction = ((8 * century) + 5) / 25 - 5; 

    /* Find the Sunday */
    sunday = (5 * year / 4) - skippedLeap - 10; 

    /* Specify when a full moon occurs */
    epact = (11 * goldenY + 20 + correction - skippedLeap) % 30; 

    if ((epact == 25 && goldenY > 11) || epact == 24)
    {
        epact += 1; 
    }

    /* Finding the full moon. Easter is the first Sunday following it */
    fullMoon = 44 - epact; 

    if (fullMoon < 21)
    {
        fullMoon += 30;
    }

    /* Advancing to Sunday */
    fullMoon = fullMoon + 7- ((sunday + fullMoon) % 7); 
    
    if (fullMoon > 31) /* Fixing the return syntax for usability */
    {
        date = fullMoon - 31; /* Positive number means April */
    }
    else
    {
        date = 0 - fullMoon; /* Negative number means March */
    }

    return date;
}

int main(void)
{
    int year, returnVal, date;
    while(1) /* infinite while loop */
    {
        returnVal = scanf("%d", &year); /* save the int in year */
        if (returnVal == EOF) /* if the line is empty, break */
        {
            break;
        }

        date = calculate_easter_date(year);
        if (date > 0) /* if positive, easter is in April */
        {
            printf("%d - April %d\n", year, date);
        }
        else if (date < 0) /* if negative, easter is in March */
        {
            printf("%d - March %d\n", year, 0 - date);
        }
        else /* date = 0, so the date was out of range */
        {
            fprintf(stderr, "date out of range!\n");
        }
    }

    return 0;
}
