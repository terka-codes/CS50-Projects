#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        // Ask user for a number
        n = get_int("Enter a number between 1 and 8 including: ");
    }

    // Ask again if the number does not comply to the conditions
    while (n < 1 || n > 8);

    //
    for (int i = 0; i < n; i++)
    {
        // For loop for the spaces where the "k" is the difference between "n" and "i", but to make sure there is always less dots than the number "n"
        // I made the "k" to be bigger than 1, not 0, because computers start counting at 0, so for it to be "k > 0" I would have to count "k = (n - i - 1)
        for (int k = (n - i); k > 1; k--)
        {
            printf(" ");
        }

        // Here I add the hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Here is a line break to start a new line with one more hash
        printf("\n");
    }
}