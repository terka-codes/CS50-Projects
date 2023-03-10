#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Get a text from a user
    string text = get_string("Text: ");

    // Establishing variables
    float letters = 0;
    float words = 1; // word variable starts at 1 not 0, because there is no space after the last word
    float sentences = 0;

    // Looping through every character or the text to check what it is
    for (int i = 0; i < strlen(text); i++)
    {
        // Checking if a character is a letter to count letters
        if (isalpha(text[i]))
        {
            letters++;
        }
        else
        {
            // Checking for spaces to count words
            if (isspace(text[i]))
            {
                words++;
            }
            // Checking if a character is a "."(46) or "!"(33) or "?"(63)
            else if (text[i] == 46 || text[i] == 33 || text[i] == 63)
            {
                sentences++;
            }
        }
    }

    // Calculating the L and S varibles to insert into the equation
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    // Calculating the Coleman-Liau index to know the grade of the text
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Rounding the "index" to be a whole number
    int grade = round(index);

    // If the "grade" number is smaller than 1 or bigger than 15 pringing different messages
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else // Printing a message with the "grade" number
    {
        printf("Grade %i\n", grade);
    }
}